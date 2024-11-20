/*------------------------------------------------------------------------------
 *  Module      : Main Application
 *  File        : main.c
 *  Description : Main program for password verification and storage
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

#include "modules.h"

/*------------------------------------------------------------------------------
 *  Global Variables
 *----------------------------------------------------------------------------*/

/* UART configuration structure */
UART_ConfigType UART_configurations = {UART_8_BIT_DATA, UART_NO_PARITY, UART_1_STOP_BIT, 9600};

/* TWI configuration structure */
TWI_ConfigType TWI_configurations = {TWI_ADDRESS, TWI_BITRATE};

/* TIMER configuration structure */
TIMER_ConfigType TIMER_configuration = {0, 0, TIMER_TIMER2, TIMER_PRESCALER_64, TIMER_OVERFLOW_MODE};

/* Array to store the accepted password */
uint8 accepted_password[KEYPAD_PASSWORD_SIZE] = {-1};

/* Array to store the extracted password from EEPROM */
uint8 extracted_password[KEYPAD_PASSWORD_SIZE] = {-1};

/* Flags and counters */
volatile boolean first_password_phase = TRUE;
volatile boolean second_password_phase = FALSE;
volatile uint16 overflow_counter = 0;
volatile uint8 g_open_door_flag = 0;
volatile uint8 g_phase_two_operation = 0;

/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/
uint8 isPasswordCorrect(void);
void savePassword(void);
void extractPassword(void);
void openDoorCallBack(void);
void systemLockDown(void);
void systemLockDownCallBack(void);
void deInitAll(void);

/** Main function **/
int main(void)
{
    /* Enable global interrupts */
    SET_BIT(SREG, 7);

    /* Initialize UART, TWI, and other modules */
    UART_init(&UART_configurations);
    TWI_init(&TWI_configurations);
    BUZZER_init();
    DC_MOTOR_init();
    PIR_init();

    /* Infinite loop */
    for (;;)
    {
        /* First phase: Initial password setup */
        while (first_password_phase)
        {
            uint8 password_correct = isPasswordCorrect();
            UART_sendByte(password_correct);

            /* If the password is incorrect, reset */
            if (password_correct == SEND_FALSE)
            {
                UART_flush();
                continue;
            }

            /* Password is correct, save it to EEPROM */
            savePassword();
            first_password_phase = FALSE;
            second_password_phase = TRUE;
        }

        /* Second phase: Verify and allow password change */
        while (second_password_phase)
        {
            uint8 phase_two = UART_recieveByte();
            while (phase_two != START_PHASE_TWO_DOOR && phase_two != START_PHASE_TWO_CHANGE);

            if (phase_two == START_PHASE_TWO_DOOR)
            {
                UART_flush();
                extractPassword();
                UART_sendByte(isPasswordCorrect());
                uint8 lock_down_on_one = UART_recieveByte();

                /* Wait for start motor or system lock sequence */
                while (lock_down_on_one != START_MOTOR && lock_down_on_one != SYSTEM_LOCK_SEQUENCE &&
                       lock_down_on_one != PASSWORD_INCORRECT) {}

                if (lock_down_on_one == START_MOTOR)
                {
                    /* Open door process */
                    TIMER_init(&TIMER_configuration);
                    TIMER_setCallBack(openDoorCallBack, TIMER_TIMER2);
                    DC_MOTOR_rotate(CLOCKWISE, 255);

                    while (g_open_door_flag == 0) {}

                    /* Stop motor and wait for door close signal */
                    DC_MOTOR_rotate(STOP, 0);

                    /* Wait for PIR sensor */
                    while (PIR_getState());

                    UART_sendByte(CLEAR);

                    /* Close door process */
                    TIMER_deInit(TIMER_TIMER2);
                    g_open_door_flag = 0;
                    overflow_counter = 0;
                    _delay_ms(50);

                    TIMER_init(&TIMER_configuration);
                    TIMER_setCallBack(openDoorCallBack, TIMER_TIMER2);
                    DC_MOTOR_rotate(ANTI_CLOCKWISE, 255);

                    while (g_open_door_flag == 0) {}

                    /* Stop motor */
                    DC_MOTOR_rotate(STOP, 0);
                    TIMER_deInit(TIMER_TIMER2);
                    g_open_door_flag = 0;
                    overflow_counter = 0;
                }
                else if (lock_down_on_one == SYSTEM_LOCK_SEQUENCE)
                {
                    /* Initiate system lock down */
                    systemLockDown();
                }
                else
                {
                    continue;
                }
            }
            else if (phase_two == START_PHASE_TWO_CHANGE)
            {
                /* Handle password change request */
                extractPassword();
                UART_sendByte(isPasswordCorrect());

                uint8 lock_down_on_two = UART_recieveByte();
                while (lock_down_on_two != RESET_PASSWORD && lock_down_on_two != SYSTEM_LOCK_SEQUENCE &&
                       lock_down_on_two != PASSWORD_INCORRECT) {}

                if (lock_down_on_two == RESET_PASSWORD)
                {
                    /* Password matches, allow a new password to be set */
                    deInitAll();
                }
                else if (lock_down_on_two == SYSTEM_LOCK_SEQUENCE)
                {
                    /* Initiate system lock down */
                    systemLockDown();
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

/** Function to check if the entered password is correct **/
uint8 isPasswordCorrect(void)
{
    uint8 first_received_password[KEYPAD_PASSWORD_SIZE];
    uint8 second_received_password[KEYPAD_PASSWORD_SIZE];

    /* Wait for the first password entry start signal */
    while (UART_recieveByte() != RECIEVE_START_PASSWORD);

    /* Receive the first password entry */
    for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
    {
        _delay_ms(50);
        first_received_password[loop_idx] = UART_recieveByte();
    }

    if (first_password_phase && !second_password_phase)
    {
        /* Wait for the second password entry start signal */
        while (UART_recieveByte() != RECIEVE_START_PASSWORD) {}

        /* Receive the second password entry */
        for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
        {
            _delay_ms(50);
            second_received_password[loop_idx] = UART_recieveByte();
        }

        /* Compare both password entries */
        for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
        {
            if (first_received_password[loop_idx] != second_received_password[loop_idx])
            {
                UART_flush();
                return SEND_FALSE; /* Passwords do not match */
            }
        }

        /* Store the correct password */
        for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
        {
            accepted_password[loop_idx] = first_received_password[loop_idx];
        }

        UART_flush();
        return SEND_TRUE; /* Passwords match */
    }
    else if (!first_password_phase && second_password_phase)
    {
        /* Compare with extracted password */
        for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
        {
            if (first_received_password[loop_idx] != extracted_password[loop_idx])
            {
                UART_flush();
                return SEND_FALSE; /* Passwords do not match */
            }
        }
        UART_flush();
        return SEND_TRUE;
    }
}

/** Function to save the accepted password to EEPROM **/
void savePassword(void)
{
    for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
    {
        EEPROM_writeByte(EEPROM_STARTBYTE + loop_idx, accepted_password[loop_idx]);
        _delay_ms(20); /* Add a delay to ensure EEPROM write completes */
    }
}

/** Function to extract the saved password from EEPROM **/
void extractPassword(void)
{
    for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
    {
        uint8 eeprom_value = 0;
        EEPROM_readByte(EEPROM_STARTBYTE + loop_idx, &eeprom_value);
        extracted_password[loop_idx] = eeprom_value;
        _delay_ms(20);
    }
}

/** Timer callback function for door opening/closing control **/
void openDoorCallBack(void)
{
    overflow_counter++;
    if (overflow_counter == TARGET_OVERFLOWS)
    {
        g_open_door_flag = 1;  // Set flag when target time is reached
        overflow_counter = 0;  // Reset tick counter
    }
}

/** Timer callback function for system lock down control **/
void systemLockDownCallBack(void)
{
    overflow_counter++;
    if (overflow_counter == LOCK_DOWN_TIME)
    {
        g_open_door_flag = 1;  // Set flag when target time is reached
        overflow_counter = 0;  // Reset tick counter
    }
}

/** Function to initiate system lock down **/
void systemLockDown(void)
{
    TIMER_init(&TIMER_configuration);
    TIMER_setCallBack(systemLockDownCallBack, TIMER_TIMER2);
    BUZZER_on();
    while (g_open_door_flag == 0) {}

    UART_sendByte(CLEAR);
    g_open_door_flag = 1;
    overflow_counter = 0;

    BUZZER_off();
    TIMER_deInit(TIMER_TIMER2);
}

/** Function to deinitialize all modules and reset flags **/
void deInitAll(void)
{
    first_password_phase = TRUE;
    second_password_phase = FALSE;
    overflow_counter = 0;
    g_open_door_flag = 0;
    g_phase_two_operation = 0;
    UART_flush();
}
