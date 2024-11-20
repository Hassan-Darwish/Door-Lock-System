/*------------------------------------------------------------------------------
 *  Module      : Buzzer Driver
 *  File        : buzzer.c
 *  Description : Source file for the ATmega32 microcontroller Buzzer driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* Include the Buzzer header file and necessary modules for GPIO and bit manipulation */
#include "buzzer.h"
#include "gpio.h"
#include "bit_manipulation.h"

/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_init
 * [Description]   This function initializes the buzzer by setting up the
 *                 corresponding GPIO pin direction as output and turning
 *                 the buzzer off initially.
 *----------------------------------------------------------------------------*/
void BUZZER_init(void)
{
	/* Set the direction of the buzzer pin as output */
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,GPIO_PIN_OUTPUT);

	/* Ensure the buzzer is turned off initially */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_on
 * [Description]   This function turns the buzzer on by writing a high value
 *                 to the GPIO pin connected to the buzzer.
 *----------------------------------------------------------------------------*/
void BUZZER_on(void)
{
	/* Write a logic high value to the buzzer pin to turn it on */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*------------------------------------------------------------------------------
 * [Function Name] BUZZER_off
 * [Description]   This function turns the buzzer off by writing a low value
 *                 to the GPIO pin connected to the buzzer.
 *----------------------------------------------------------------------------*/
void BUZZER_off(void)
{
	/* Write a logic low value to the buzzer pin to turn it off */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
