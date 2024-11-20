/*------------------------------------------------------------------------------
 *  Module      : PIR SENSOR Driver
 *  File        : pir_sensor.c
 *  Description : Source file for the ATmega32 microcontroller PIR SENSOR driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

#include "pir_sensor.h"
#include "gpio.h"

/*------------------------------------------------------------------------------
 *  Functions
 *----------------------------------------------------------------------------*/

void PIR_init(void)
{
	GPIO_setupPinDirection(PIR_OUTPUT_PORT_ID,PIR_OUTPUT_PIN_ID,GPIO_PIN_INPUT);

}
uint8 PIR_getState(void)
{
	return GPIO_readPin(PIR_OUTPUT_PORT_ID,PIR_OUTPUT_PIN_ID);

}
