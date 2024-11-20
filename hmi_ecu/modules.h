/*------------------------------------------------------------------------------
 *  Module      : ALL MODULES
 *  File        : modules.h
 *  Description : Header file for all the drivers in the HMI ECU
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef MODULES_H_
#define MODULES_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* MCAL */
#include "gpio.h"
#include "uart.h"
#include "timer.h"

/* HCAL */
#include "keypad.h"
#include "lcd.h"

/* Utility */
#include "bit_manipulation.h"
#include "stdtypes.h"

/* AVR Libraries */
#include <util/delay.h>
#include <avr/io.h>

/* HMI Constants */
#include "hmi_constants.h"

#endif /* MODULES_H_ */
