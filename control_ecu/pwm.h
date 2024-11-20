/*------------------------------------------------------------------------------
 *  Module      : PWM Driver
 *  File        : pwm.h
 *  Description : Header file for the ATmega32 microcontroller PWM driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/


#ifndef PWM_H_
#define PWM_H_


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/


#include "stdtypes.h"  // Include the standard types header for uint8 definition


/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/


#define PWM_OC0_DDR_ID   DDRB         // Data Direction Register for OC0 pin
#define PWM_OC0_PIN_ID   PB3           // OC0 pin number (PB3) for PWM output


/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/


/*
 * Function: PWM_Timer0_Start
 * Description: Initializes Timer0 for Fast PWM mode and sets the duty cycle.
 * Parameters:
 *   - duty_cycle: The duty cycle for PWM signal (0-255).
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
