/*------------------------------------------------------------------------------
 *  Module      : DC MOTOR Driver
 *  File        : dc_motor.c
 *  Description : Source file for the DC MOTOR driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/

/* Include the DC motor, GPIO, and PWM header files */
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 * [Function Name] DC_MOTOR_init
 * [Description]   Initializes the DC motor by configuring the control pins as
 *                 output and setting the initial state to low (off).
 *----------------------------------------------------------------------------*/
void DC_MOTOR_init(void)
{
    /* Set the EN1, IN1, and IN2 pins as output for motor control */
	GPIO_setupPinDirection(DC_MOTOR_EN_ID,DC_MOTOR_EN1_ID,GPIO_PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN_ID,DC_MOTOR_IN1_ID,GPIO_PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN_ID,DC_MOTOR_IN2_ID,GPIO_PIN_OUTPUT);

    /* Initialize all motor control pins to low, effectively turning the motor off */
	GPIO_writePin(DC_MOTOR_EN_ID,DC_MOTOR_EN1_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN1_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN2_ID,LOGIC_LOW);
}

/*------------------------------------------------------------------------------
 * [Function Name] DC_MOTOR_rotate
 * [Description]   Controls the direction and speed of the DC motor.
 *                 It rotates the motor clockwise, counterclockwise, or stops it.
 *----------------------------------------------------------------------------*/
void DC_MOTOR_rotate(DC_MOTOR_State state, uint8 speed)
{
    /* Enable the motor by setting EN1 to high */
	GPIO_writePin(DC_MOTOR_EN_ID,DC_MOTOR_EN1_ID,LOGIC_HIGH);

    /* Control motor direction based on the state provided */
	switch (state)
	{
	    case CLOCKWISE:
	        /* Set IN1 high and IN2 low to rotate the motor clockwise */
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN1_ID,LOGIC_HIGH);
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN2_ID,LOGIC_LOW);
	        break;

	    case ANTI_CLOCKWISE:
	        /* Set IN1 low and IN2 high to rotate the motor counterclockwise */
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN1_ID,LOGIC_LOW);
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN2_ID,LOGIC_HIGH);
	        break;

	    case STOP:
	        /* Set both IN1 and IN2 low to stop the motor */
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN1_ID,LOGIC_LOW);
	        GPIO_writePin(DC_MOTOR_IN_ID,DC_MOTOR_IN2_ID,LOGIC_LOW);
	        break;
	}

    /* Start the PWM signal to control the motor speed */
	PWM_Timer0_Start(speed);
}
