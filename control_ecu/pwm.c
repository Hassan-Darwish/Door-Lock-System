/*------------------------------------------------------------------------------
 *  Module      : PWM Driver
 *  File        : pwm.c
 *  Description : Source file for the ATmega32 microcontroller PWM driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

#include "pwm.h"                // Include the PWM header file for function declarations
#include "avr/io.h"             // Include AVR I/O library for register definitions
#include "bit_manipulation.h"   // Include custom bit manipulation macros


/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/

/*
 * Function: PWM_Timer0_Start
 * Description: Initializes Timer0 for Fast PWM mode and sets the duty cycle.
 * Parameters:
 *   - duty_cycle: The duty cycle for PWM signal (0-255).
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
    SET_BIT(PWM_OC0_DDR_ID, PWM_OC0_PIN_ID);  // Set the OC0 pin as output

    /*  Set Timer0 to Fast PWM mode: WGM00 and WGM01 bits are set  */
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    /*  Set the compare output mode to non-inverting mode: COM00 is cleared, COM01 is set  */
    CLEAR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

    /*  Set the timer prescaler to F_CPU/64: CS00 and CS01 are set, CS02 is cleared  */
    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLEAR_BIT(TCCR0, CS02);

    /*  Load the duty cycle value into the Output Compare Register (OCR0)  */
    OCR0 = duty_cycle;
}
