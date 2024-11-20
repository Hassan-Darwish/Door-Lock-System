/*------------------------------------------------------------------------------
 *  Module      : Main Application
 *  File        : main.c
 *  Description : Main program for password entry and verification system
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

/* TIMER configuration structure - currently incomplete */
TIMER_ConfigType TIMER_configuration = {0, 0, TIMER_TIMER2, TIMER_PRESCALER_64, TIMER_OVERFLOW_MODE};

/* Flags to manage password entry states */
volatile boolean g_password_phase_one = TRUE;
volatile boolean g_password_reenter = FALSE;
volatile boolean g_password_phase_two = FALSE;
volatile uint16 overflow_counter = 0;
volatile boolean g_open_door_flag = 0;

/*------------------------------------------------------------------------------
 *  Functions
 *----------------------------------------------------------------------------*/

/* Function prototypes */
void getPasswordSend(void);
uint8 awaitPasswordResponse(void);
void openDoorCallBack(void);
void deInitAll(void);

/*------------------------------------------------------------------------------
 *  Main Function
 *----------------------------------------------------------------------------*/
int main(void)
{
    /* Enable global interrupts */
    SET_BIT(SREG, 7);

    /* Initialize modules */
    LCD_init();
    UART_init(&UART_configurations);

    /* Display initial message */
    LCD_displayString("Door Lock System");
    _delay_ms(50);
    LCD_clearScreen();

    /* Infinite loop */
    for (;;)
    {
        /* Password entry phase */
        while (g_password_phase_one)
        {
            getPasswordSend();

            /* Re-enter password if required */
            if (g_password_reenter == TRUE)
            {
                getPasswordSend();
            }

            /* Handle response once */
            uint8 password_response = awaitPasswordResponse();
            if (password_response == RECIEVE_FALSE)
            {
                g_password_phase_one = TRUE;
                g_password_reenter = FALSE;
            }
            else if (password_response == RECIEVE_TRUE)
            {
                g_password_phase_one = FALSE;
                g_password_phase_two = TRUE;
            }
        }

        /* Variables for operation state */
        boolean in_operation_flag = 0;
        uint8 attempts_on_open_door = 1;
        uint8 attempts_on_change_password = 1;
        uint8 key_response = 0;

        /* Password verification and door operation phase */
        while (g_password_phase_two)
        {
            while (in_operation_flag == 0)
            {
                LCD_clearScreen();
                /* Display options once password is correct */
                LCD_displayString("+ : Open Door");
                LCD_displayStringRowColumn(1, 0, "- : Change Pass");

                while (key_response != '+' && key_response != '-')
                {
                    _delay_ms(500);
                    key_response = KEYPAD_getPressedKey();
                }
                in_operation_flag = 1;
            }

            /* Handle selected option */
            if (key_response == '+')
            {
                /* Door opening sequence */
                UART_flush();
                UART_sendByte(START_PHASE_TWO_DOOR);
                _delay_ms(10);
                LCD_clearScreen();
                g_password_reenter = START_PHASE_TWO;
                getPasswordSend();

                if (awaitPasswordResponse() == RECIEVE_TRUE)
                {
                    UART_sendByte(START_MOTOR);
                    LCD_clearScreen();
                    LCD_displayString("Opening Door");
                    LCD_displayStringRowColumn(1, 0, "Please Wait...");

                    TIMER_init(&TIMER_configuration);
                    TIMER_setCallBack(openDoorCallBack, TIMER_TIMER2);

                    /* Wait for door to open */
                    while (g_open_door_flag == 0);

                    LCD_clearScreen();
                    LCD_displayString("Wait for people");
                    LCD_displayStringRowColumn(1, 0, "to enter...");

                    while (UART_recieveByte() != CLEAR);
                    LCD_clearScreen();

                    TIMER_deInit(TIMER_TIMER2);
                    g_open_door_flag = 0;
                    _delay_ms(50);

                    TIMER_init(&TIMER_configuration);
                    TIMER_setCallBack(openDoorCallBack, TIMER_TIMER2);

                    LCD_displayString("Door Closing");
                    LCD_displayStringRowColumn(1, 0, "Please Wait...");

                    /* Wait for door to close */
                    while (g_open_door_flag == 0);

                    LCD_clearScreen();
                    TIMER_deInit(TIMER_TIMER2);

                    attempts_on_open_door = 1;
                    in_operation_flag = 0;
                    break; // Exit loop if password is correct
                }
                else if (attempts_on_open_door < MAXIMUM_PASSWORD_ATTEMPTS)
                {
                    attempts_on_open_door++;
                    UART_sendByte(PASSWORD_INCORRECT);
                    in_operation_flag = 1;
                }
                else
                {
                    /* Max attempts reached */
                    LCD_clearScreen();
                    LCD_displayString("MAX ATTEMPTS");
                    LCD_displayStringRowColumn(1, 0, "REACHED");

                    UART_sendByte(SYSTEM_LOCK_SEQUENCE);
                    while (UART_recieveByte() != CLEAR);
                    attempts_on_open_door = 0;
                    break;
                }
            }
            else if (key_response == '-')
            {
                /* Password change sequence */
                UART_sendByte(START_PHASE_TWO_CHANGE);
                g_password_reenter = START_PHASE_TWO;
                getPasswordSend();
                g_password_phase_one = TRUE;

                /* Handle re-entry of password to change it */
                if (awaitPasswordResponse() == RECIEVE_TRUE)
                {
                    UART_sendByte(RESET_PASSWORD);
                    g_password_phase_one = TRUE;
                    g_password_reenter = FALSE;
                    g_password_phase_two = FALSE;
                    attempts_on_change_password = 1;
                    in_operation_flag = 0;
                    break;
                }
                else if (attempts_on_change_password < MAXIMUM_PASSWORD_ATTEMPTS)
                {
                    attempts_on_change_password++;
                    UART_sendByte(PASSWORD_INCORRECT);
                    in_operation_flag = 1;
                }
                else
                {
                    /* Max attempts reached */
                    LCD_clearScreen();
                    LCD_displayString("MAX ATTEMPTS");
                    LCD_displayStringRowColumn(1, 0, "REACHED");

                    UART_sendByte(SYSTEM_LOCK_SEQUENCE);
                    while (UART_recieveByte() != CLEAR);
                    attempts_on_change_password = 0;
                    break;
                }
            }
        }
    }
}

/*------------------------------------------------------------------------------
 *  Helper Functions
 *----------------------------------------------------------------------------*/

/* Function to prompt the user to enter or re-enter password and send it over UART */
void getPasswordSend(void)
{
    LCD_clearScreen();
    uint8 user_password[KEYPAD_PASSWORD_SIZE];

    /* Display appropriate message based on password entry phase */
    if (g_password_reenter == FALSE)
    {
        LCD_displayStringRowColumn(0, 0, "Plz enter pass:");
        LCD_moveCursor(1, 0);
        g_password_reenter = TRUE;
    }
    else if (g_password_reenter == TRUE)
    {
        LCD_displayString("Plz re-enter the");
        LCD_displayStringRowColumn(1, 0, "same pass:");
    }
    else if (g_password_reenter == START_PHASE_TWO)
    {
        LCD_displayString("Plz enter old");
        LCD_displayStringRowColumn(1, 0, "pass:");
    }

    /* Gather and mask password input from user */
    for (uint8 key_input_idx = 0; key_input_idx < KEYPAD_PASSWORD_SIZE; key_input_idx++)
    {
        user_password[key_input_idx] = KEYPAD_getPressedKey();

        /* Check if the input is a valid number */
        if (user_password[key_input_idx] >= KEYPAD_MINIMUM_NUMBER &&
            user_password[key_input_idx] <= KEYPAD_MAXIMUM_NUMBER)
        {
            LCD_displayCharacter('*');
        }
        else
        {
            key_input_idx--; /* Invalid input, repeat the same index */
        }

        _delay_ms(500);
    }

    /* Wait for the user to press the Enter button */
    while (KEYPAD_getPressedKey() != KEYPAD_ENTER_BUTTON);

    /* Send start password signal */
    UART_sendByte(SEND_START_PASSWORD);

    /* Transmit the password over UART */
    for (uint8 loop_idx = 0; loop_idx < KEYPAD_PASSWORD_SIZE; loop_idx++)
    {
        _delay_ms(50);
        UART_sendByte(user_password[loop_idx]);
    }

    LCD_clearScreen();
    return;
}

/* Function to await response indicating password validity */
uint8 awaitPasswordResponse(void)
{
    uint8 response_byte = 0;

    /* Wait until a valid response (true or false) is received */
    while (response_byte != RECIEVE_TRUE && response_byte != RECIEVE_FALSE)
    {
        response_byte = UART_recieveByte();
    }

    return response_byte;
}

/* Callback function to manage door timing */
void openDoorCallBack(void)
{
    overflow_counter++;
    if (overflow_counter == TARGET_OVERFLOWS)
    {
        g_open_door_flag = 1; /* Set flag when target time is reached */
        overflow_counter = 0; /* Reset tick counter */
    }
    else
    {
        g_open_door_flag = 0;
    }
}

/* Deinitialize all global variables */
void deInitAll(void)
{
    g_password_phase_one = TRUE;
    g_password_reenter = FALSE;
    g_password_phase_two = FALSE;
    overflow_counter = 0;
    g_open_door_flag = 0;
    UART_flush();
}
