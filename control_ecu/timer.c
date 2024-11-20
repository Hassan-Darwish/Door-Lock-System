/*------------------------------------------------------------------------------
 *  Module      : TIMERs Driver
 *  File        : TIMER.c
 *  Description : Source file for the ATmega32 microcontroller TIMER driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

#include "timer.h"
#include "bit_manipulation.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*------------------------------------------------------------------------------
 *  Functions
 *----------------------------------------------------------------------------*/

static void (*g_TIMER0_CallBackPtr)(void) = NULL;
static void (*g_TIMER1_CallBackPtr)(void) = NULL;
static void (*g_TIMER2_CallBackPtr)(void) = NULL;

/**
 * Function: TIMER_init
 * Description: Initializes the specified timer with settings from the provided
 *              configuration structure.
 * Parameters:
 *   - Config_Ptr: Pointer to configuration structure (TIMER_ConfigType).
 */
void TIMER_init(const TIMER_ConfigType * Config_Ptr)
{
    // Set initial TIMER value
    switch (Config_Ptr->TIMER_ID)
    {
        case TIMER_TIMER0:
            // Set the initial count value for TIMER0
            TCNT0 = Config_Ptr->TIMER_InitialValue;

            // Configure the mode for TIMER0
            switch (Config_Ptr->TIMER_mode)
            {
                case TIMER_OVERFLOW_MODE:
                    SET_BIT(TIMSK, TOIE0);  // Enable overflow interrupt for TIMER0
                    SET_BIT(TCCR0, FOC0);   // Force Output Compare for non-PWM mode
                    CLEAR_BIT(TCCR0, WGM00); // Normal Mode
                    CLEAR_BIT(TCCR0, WGM01);

                    break;

                case TIMER_COMPARE_MODE:
                    OCR0 = Config_Ptr->TIMER_compare_MatchValue; // Compare match value
                    SET_BIT(TIMSK, OCIE0);  // Enable compare match interrupt for TIMER0
                    SET_BIT(TCCR0, FOC0);   // Force Output Compare for non-PWM mode
                    CLEAR_BIT(TCCR0, WGM00); // CTC Mode
                    SET_BIT(TCCR0, WGM01);

                    break;
            }

            // Configure prescaler for TIMER0
            switch (Config_Ptr->TIMER_clock)
            {
                case TIMER_NO_CLOCK_SOURCE:
                    CLEAR_BIT(TCCR0, CS00);
                    CLEAR_BIT(TCCR0, CS01);
                    CLEAR_BIT(TCCR0, CS02);

                    break;
                case TIMER_NO_PRESCALING:
                    SET_BIT(TCCR0, CS00);
                    CLEAR_BIT(TCCR0, CS01);
                    CLEAR_BIT(TCCR0, CS02);

                    break;
                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR0, CS00);
                    SET_BIT(TCCR0, CS01);
                    CLEAR_BIT(TCCR0, CS02);

                    break;
                case TIMER_PRESCALER_64:
                    SET_BIT(TCCR0, CS00);
                    SET_BIT(TCCR0, CS01);
                    CLEAR_BIT(TCCR0, CS02);

                    break;
                case TIMER_PRESCALER_256:
                    CLEAR_BIT(TCCR0, CS00);
                    CLEAR_BIT(TCCR0, CS01);
                    SET_BIT(TCCR0, CS02);

                    break;
                case TIMER_PRESCALER_1024:
                    SET_BIT(TCCR0, CS00);
                    CLEAR_BIT(TCCR0, CS01);
                    SET_BIT(TCCR0, CS02);

                    break;
            }

            break;

        case TIMER_TIMER1:
            // Set the initial count value for TIMER1
            TCNT1 = Config_Ptr->TIMER_InitialValue;

            // Configure the mode for TIMER1
            switch (Config_Ptr->TIMER_mode)
            {
                case TIMER_OVERFLOW_MODE:
                    SET_BIT(TIMSK, TOIE1);  // Enable overflow interrupt for TIMER1
                    CLEAR_BIT(TCCR1A, WGM10); // Normal Mode
                    CLEAR_BIT(TCCR1A, WGM11);
                    CLEAR_BIT(TCCR1B, WGM12);
                    CLEAR_BIT(TCCR1B, WGM13);

                    break;

                case TIMER_COMPARE_MODE:
                    OCR1A = Config_Ptr->TIMER_compare_MatchValue; // Compare match value
                    SET_BIT(TIMSK, OCIE1A); // Enable compare match interrupt for TIMER1
                    CLEAR_BIT(TCCR1A, WGM10); // CTC Mode
                    CLEAR_BIT(TCCR1A, WGM11);
                    SET_BIT(TCCR1B, WGM12);
                    CLEAR_BIT(TCCR1B, WGM13);

                    break;
            }

            // Configure prescaler for TIMER1
            switch (Config_Ptr->TIMER_clock)
            {
                case TIMER_NO_CLOCK_SOURCE:
                    CLEAR_BIT(TCCR1B, CS10);
                    CLEAR_BIT(TCCR1B, CS11);
                    CLEAR_BIT(TCCR1B, CS12);

                    break;
                case TIMER_NO_PRESCALING:
                    SET_BIT(TCCR1B, CS10);
                    CLEAR_BIT(TCCR1B, CS11);
                    CLEAR_BIT(TCCR1B, CS12);

                    break;
                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR1B, CS10);
                    SET_BIT(TCCR1B, CS11);
                    CLEAR_BIT(TCCR1B, CS12);

                    break;
                case TIMER_PRESCALER_64:
                    SET_BIT(TCCR1B, CS10);
                    SET_BIT(TCCR1B, CS11);
                    CLEAR_BIT(TCCR1B, CS12);

                    break;
                case TIMER_PRESCALER_256:
                    CLEAR_BIT(TCCR1B, CS10);
                    CLEAR_BIT(TCCR1B, CS11);
                    SET_BIT(TCCR1B, CS12);

                    break;
                case TIMER_PRESCALER_1024:
                    SET_BIT(TCCR1B, CS10);
                    CLEAR_BIT(TCCR1B, CS11);
                    SET_BIT(TCCR1B, CS12);

                    break;
            }

            break;

        case TIMER_TIMER2:
            // Set the initial count value for TIMER2
            TCNT2 = Config_Ptr->TIMER_InitialValue;

            // Configure the mode for TIMER2
            switch (Config_Ptr->TIMER_mode)
            {
                case TIMER_OVERFLOW_MODE:
                    SET_BIT(TIMSK, TOIE2);  // Enable overflow interrupt for TIMER2
                    CLEAR_BIT(TCCR2, WGM20); // Normal Mode
                    CLEAR_BIT(TCCR2, WGM21);

                    break;

                case TIMER_COMPARE_MODE:
                    OCR2 = Config_Ptr->TIMER_compare_MatchValue; // Compare match value
                    SET_BIT(TIMSK, OCIE2);  // Enable compare match interrupt for TIMER2
                    CLEAR_BIT(TCCR2, WGM20); // CTC Mode
                    SET_BIT(TCCR2, WGM21);

                    break;
            }

            // Configure prescaler for TIMER2
            switch (Config_Ptr->TIMER_clock)
            {
                case TIMER_NO_CLOCK_SOURCE:
                    CLEAR_BIT(TCCR2, CS20);
                    CLEAR_BIT(TCCR2, CS21);
                    CLEAR_BIT(TCCR2, CS22);

                    break;
                case TIMER_NO_PRESCALING:
                    SET_BIT(TCCR2, CS20);
                    CLEAR_BIT(TCCR2, CS21);
                    CLEAR_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_8:
                    CLEAR_BIT(TCCR2, CS20);
                    SET_BIT(TCCR2, CS21);
                    CLEAR_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_32:
                    SET_BIT(TCCR2, CS20);
                    SET_BIT(TCCR2, CS21);
                    CLEAR_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_64:
                    CLEAR_BIT(TCCR2, CS20);
                    CLEAR_BIT(TCCR2, CS21);
                    SET_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_128:
                    SET_BIT(TCCR2, CS20);
                    CLEAR_BIT(TCCR2, CS21);
                    SET_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_256:
                    CLEAR_BIT(TCCR2, CS20);
                    SET_BIT(TCCR2, CS21);
                    SET_BIT(TCCR2, CS22);

                    break;
                case TIMER_PRESCALER_1024:
                    SET_BIT(TCCR2, CS20);
                    SET_BIT(TCCR2, CS21);
                    SET_BIT(TCCR2, CS22);

                    break;
            }
            break;
    }
}

/*  Callback Function Registration
 *  Function: TIMER_setCallBack
 *  Description: Sets the callback function for the specified timer.
 *               This callback will be called within the corresponding ISR.
 */

void TIMER_setCallBack(void (*a_ptr)(void), TIMER_ID_Type a_TIMER_ID)
{
    switch (a_TIMER_ID) {
        case TIMER_TIMER0: g_TIMER0_CallBackPtr = a_ptr; break;  // Register callback for TIMER0
        case TIMER_TIMER1: g_TIMER1_CallBackPtr = a_ptr; break;  // Register callback for TIMER1
        case TIMER_TIMER2: g_TIMER2_CallBackPtr = a_ptr; break;  // Register callback for TIMER2
    }
}

/*
 *  Timer Deinitialization
 *  Function: TIMER_deInit
 *  Description: Resets timer settings, stops the timer, and clears the callback
 *               pointer to fully disable the specified timer and avoid unexpected behavior.
 */
void TIMER_deInit(TIMER_ID_Type TIMER_type)
{
    switch(TIMER_type)
    {
        case TIMER_TIMER0:
            TCCR0 = 0;           // Clear control register
            TCNT0 = 0;           // Reset counter register
            OCR0 = 0;            // Reset compare register
            CLEAR_BIT(TIMSK,TOIE0);  // Disable overflow interrupt
            CLEAR_BIT(TIMSK,OCIE0);  // Disable compare match interrupt
            g_TIMER0_CallBackPtr = NULL;  // Clear callback pointer

            break;

        case TIMER_TIMER1:
            TCCR1A = 0;
            TCCR1B = 0;
            TCNT1 = 0;
            CLEAR_BIT(TIMSK,TOIE1);  // Disable overflow interrupt
            CLEAR_BIT(TIMSK,OCIE1A); // Disable compare match interrupt
            g_TIMER1_CallBackPtr = NULL; // Clear callback pointer

            break;

        case TIMER_TIMER2:
            TCCR2 = 0;
            TCNT2 = 0;
            OCR2 = 0;
            CLEAR_BIT(TIMSK,TOIE2);  // Disable overflow interrupt
            CLEAR_BIT(TIMSK,OCIE2);  // Disable compare match interrupt
            g_TIMER2_CallBackPtr = NULL; // Clear callback pointer

            break;
    }
}

/*------------------------------------------------------------------------------
 *  Interrupt Service Routines
 *----------------------------------------------------------------------------*/

ISR(TIMER0_OVF_vect)   // ISR for Timer0 overflow
{
    if (g_TIMER0_CallBackPtr)
    {
        g_TIMER0_CallBackPtr();  // Execute callback if set
    }
}

ISR(TIMER0_COMP_vect)  // ISR for Timer0 compare match
{
    if (g_TIMER0_CallBackPtr)
    {
        g_TIMER0_CallBackPtr();  // Execute callback if set
    }
}

ISR(TIMER1_OVF_vect)   // ISR for Timer1 overflow
{
    if (g_TIMER1_CallBackPtr)
    {
        g_TIMER1_CallBackPtr();  // Execute callback if set
    }
}

ISR(TIMER1_COMPA_vect) // ISR for Timer1 compare match
{
    if (g_TIMER1_CallBackPtr)
    {
        g_TIMER1_CallBackPtr();  // Execute callback if set
    }
}

ISR(TIMER2_OVF_vect)   // ISR for Timer2 overflow
{
    if (g_TIMER2_CallBackPtr)
    {
        g_TIMER2_CallBackPtr();  // Execute callback if set
    }
}

ISR(TIMER2_COMP_vect)  // ISR for Timer2 compare match
{
    if (g_TIMER2_CallBackPtr)
    {
        g_TIMER2_CallBackPtr();  // Execute callback if set
    }
}

