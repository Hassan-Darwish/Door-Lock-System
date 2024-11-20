/*------------------------------------------------------------------------------
 *  Module      : DC MOTOR Driver
 *  File        : dc_motor.h
 *  Description : Header file for the DC MOTOR driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* Include standard data types */
#include "stdtypes.h"

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

/* Define the port where the DC motor is connected */
#define DC_MOTOR_EN_ID									GPIO_PORTB
#define DC_MOTOR_IN_ID									GPIO_PORTD

/* Define the pins used to control the motor's input and enable */
#define DC_MOTOR_IN1_ID									GPIO_PIN6
#define DC_MOTOR_IN2_ID									GPIO_PIN7
#define DC_MOTOR_EN1_ID									GPIO_PIN4

/*------------------------------------------------------------------------------
 *  Data Types Declarations
 *----------------------------------------------------------------------------*/

/* Enum to represent the motor's rotation states: clockwise, counterclockwise, or stopped */
typedef enum
{
	CLOCKWISE,     /* Rotate the motor clockwise */
	ANTI_CLOCKWISE,/* Rotate the motor counterclockwise */
	STOP           /* Stop the motor */
} DC_MOTOR_State;

/*------------------------------------------------------------------------------
 *  Function Declarations
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * [Function Name] DC_MOTOR_init
 * [Description]   Initializes the pins connected to the DC motor.
 *----------------------------------------------------------------------------*/
void DC_MOTOR_init(void);

/*------------------------------------------------------------------------------
 * [Function Name] DC_MOTOR_rotate
 * [Description]   Controls the motor's direction and speed.
 *----------------------------------------------------------------------------*/
void DC_MOTOR_rotate(DC_MOTOR_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
