/*------------------------------------------------------------------------------
 *  Module      : ALL MODULES
 *  File        : modules.h
 *  Description : Header file for all the drivers in the Control ECU
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef MODULES_H_
#define MODULES_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* MCAL */
#include "gpio.h"
#include "pwm.h"
#include "uart.h"
#include "timer.h"
#include "twi.h"

/* HCAL */
#include "pir_sensor.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "external_eeprom.h"

/* Utility */
#include "stdtypes.h"
#include "bit_manipulation.h"

/* AVR Libraries */
#include <util/delay.h>
#include <avr/io.h>

/* Control Constants */
#include "control_constants.h"

#endif /* MODULES_H_ */
