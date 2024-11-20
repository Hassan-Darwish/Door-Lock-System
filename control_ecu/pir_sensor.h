/*------------------------------------------------------------------------------
 *  Module      : PIR SENSOR Driver
 *  File        : pir_sensor.h
 *  Description : Header file for the ATmega32 microcontroller PIR SENSOR driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

#include "stdtypes.h"

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/
#define PIR_OUTPUT_PORT_ID								GPIO_PORTC
#define PIR_OUTPUT_PIN_ID								GPIO_PIN2

void PIR_init(void);
uint8 PIR_getState(void);
#endif /* PIR_SENSOR_H_ */
