/*------------------------------------------------------------------------------
 *  Module      : Buzzer Driver
 *  File        : buzzer.h
 *  Description : Header file for the ATmega32 microcontroller Buzzer driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef BUZZER_H_
#define BUZZER_H_


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* Include the GPIO header file for controlling the buzzer pin */
#include "gpio.h"

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * [Constant Name] BUZZER_PORT_ID
 * [Description]   The port where the buzzer is connected (Port C in this case).
 *----------------------------------------------------------------------------*/
#define BUZZER_PORT_ID								GPIO_PORTC

/*------------------------------------------------------------------------------
 * [Constant Name] BUZZER_PIN_ID
 * [Description]   The pin number where the buzzer is connected (Pin 6 in this case).
 *----------------------------------------------------------------------------*/
#define BUZZER_PIN_ID								GPIO_PIN7

/*------------------------------------------------------------------------------
 *  Function Declarations
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_init
 * [Description]   Function to initialize the buzzer by setting the corresponding
 *                 GPIO pin direction as output and ensuring it is off initially.
 *----------------------------------------------------------------------------*/
void BUZZER_init(void);

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_on
 * [Description]   Function to turn on the buzzer by setting the pin to logic high.
 *----------------------------------------------------------------------------*/
void BUZZER_on(void);

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_off
 * [Description]   Function to turn off the buzzer by setting the pin to logic low.
 *----------------------------------------------------------------------------*/
void BUZZER_off(void);

#endif /* BUZZER_H_ */
