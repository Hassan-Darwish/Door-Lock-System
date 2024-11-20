/*------------------------------------------------------------------------------
 *  Module      : GPIO Driver
 *  File        : gpio.c
 *  Description : Source file for the ATmega32 microcontroller GPIO driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
 *  INCLUDES
 *----------------------------------------------------------------------------*/


#include "gpio.h"
#include "bit_manipulation.h"
#include "avr/io.h"


/*------------------------------------------------------------------------------
 *  Functions and ISR Definitions
 *----------------------------------------------------------------------------*/


void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Setup the pin direction */
        switch(port_num)
        {
        case GPIO_PORTA:
            if(direction == GPIO_PIN_OUTPUT)
            {
                SET_BIT(DDRA,pin_num);
            }
            else
            {
                CLEAR_BIT(DDRA,pin_num);
            }
            break;
        case GPIO_PORTB:
            if(direction == GPIO_PIN_OUTPUT)
            {
                SET_BIT(DDRB,pin_num);
            }
            else
            {
                CLEAR_BIT(DDRB,pin_num);
            }
            break;
        case GPIO_PORTC:
            if(direction == GPIO_PIN_OUTPUT)
            {
                SET_BIT(DDRC,pin_num);
            }
            else
            {
                CLEAR_BIT(DDRC,pin_num);
            }
            break;
        case GPIO_PORTD:
            if(direction == GPIO_PIN_OUTPUT)
            {
                SET_BIT(DDRD,pin_num);
            }
            else
            {
                CLEAR_BIT(DDRD,pin_num);
            }
            break;
        }
    }
}

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Write the pin value */
        switch(port_num)
        {
        case GPIO_PORTA:
            if(value == LOGIC_HIGH)
            {
                SET_BIT(PORTA, pin_num);
            }
            else
            {
                CLEAR_BIT(PORTA, pin_num);
            }
            break;
        case GPIO_PORTB:
            if(value == LOGIC_HIGH)
            {
                SET_BIT(PORTB, pin_num);
            }
            else
            {
                CLEAR_BIT(PORTB, pin_num);
            }
            break;
        case GPIO_PORTC:
            if(value == LOGIC_HIGH)
            {
                SET_BIT(PORTC, pin_num);
            }
            else
            {
                CLEAR_BIT(PORTC, pin_num);
            }
            break;
        case GPIO_PORTD:
            if(value == LOGIC_HIGH)
            {
                SET_BIT(PORTD, pin_num);
            }
            else
            {
                CLEAR_BIT(PORTD, pin_num);
            }
            break;
        }
    }
}

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    uint8 pin_value = LOGIC_LOW;

    if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Read the pin value */
        switch(port_num)
        {
        case GPIO_PORTA:
            if(IS_BIT_SET(PINA, pin_num))
            {
                pin_value = LOGIC_HIGH;
            }
            break;
        case GPIO_PORTB:
            if(IS_BIT_SET(PINB, pin_num))
            {
                pin_value = LOGIC_HIGH;
            }
            break;
        case GPIO_PORTC:
            if(IS_BIT_SET(PINC, pin_num))
            {
                pin_value = LOGIC_HIGH;
            }
            break;
        case GPIO_PORTD:
            if(IS_BIT_SET(PIND, pin_num))
            {
                pin_value = LOGIC_HIGH;
            }
            break;
        }
    }

    return pin_value;
}

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
    if(port_num >= NUM_OF_PORTS)
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Setup the port direction */
        switch(port_num)
        {
        case GPIO_PORTA:
            DDRA = direction;
            break;
        case GPIO_PORTB:
            DDRB = direction;
            break;
        case GPIO_PORTC:
            DDRC = direction;
            break;
        case GPIO_PORTD:
            DDRD = direction;
            break;
        }
    }
}

void GPIO_writePort(uint8 port_num, uint8 value)
{
    if(port_num >= NUM_OF_PORTS)
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Write the port value */
        switch(port_num)
        {
        case GPIO_PORTA:
            PORTA = value;
            break;
        case GPIO_PORTB:
            PORTB = value;
            break;
        case GPIO_PORTC:
            PORTC = value;
            break;
        case GPIO_PORTD:
            PORTD = value;
            break;
        }
    }
}

uint8 GPIO_readPort(uint8 port_num)
{
    uint8 value = LOGIC_LOW;

    if(port_num >= NUM_OF_PORTS)
    {
        /* Ignore invalid input */
    }
    else
    {
        /* Read the port value */
        switch(port_num)
        {
        case GPIO_PORTA:
            value = PINA;
            break;
        case GPIO_PORTB:
            value = PINB;
            break;
        case GPIO_PORTC:
            value = PINC;
            break;
        case GPIO_PORTD:
            value = PIND;
            break;
        }
    }

    return value;
}
