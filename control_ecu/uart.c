 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "bit_manipulation.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(const UART_ConfigType * Config_Ptr)
{
    uint16 ubrr_value = 0;

    /* U2X = 1 for double transmission speed */
    UCSRA = (1<<U2X);

    /* Enable Receiver and Transmitter */
    UCSRB = (1<<RXEN) | (1<<TXEN);

    /* UCSRC settings - URSEL must be 1 to write to UCSRC */
    UCSRC = (1<<URSEL);

    /* Set the number of data bits */
    switch(Config_Ptr->bit_data)
    {
        case UART_5_BIT_DATA:
        	CLEAR_BIT(UCSRC,UCSZ0);
        	CLEAR_BIT(UCSRC,UCSZ1);
            break;
        case UART_6_BIT_DATA:
        	SET_BIT(UCSRC,UCSZ0);
        	CLEAR_BIT(UCSRC,UCSZ1);
            break;
        case UART_7_BIT_DATA:
        	CLEAR_BIT(UCSRC,UCSZ0);
        	SET_BIT(UCSRC,UCSZ1);
            break;
        case UART_8_BIT_DATA:
        	SET_BIT(UCSRC,UCSZ0);
        	SET_BIT(UCSRC,UCSZ1);
            break;
        case UART_9_BIT_DATA:
        	SET_BIT(UCSRB,UCSZ2); /* Enable UCSZ2 for 9-bit mode */
        	SET_BIT(UCSRC,UCSZ0);
        	SET_BIT(UCSRC,UCSZ1);
            break;
    }

    /* Set parity mode */
    switch(Config_Ptr->parity)
    {
        case UART_NO_PARITY:
        	CLEAR_BIT(UCSRC,UPM0);
        	CLEAR_BIT(UCSRC,UPM1);
            break;
        case UART_EVEN_PARITY:
        	CLEAR_BIT(UCSRC,UPM0);
        	SET_BIT(UCSRC,UPM1);
            break;
        case UART_ODD_PARITY:
        	SET_BIT(UCSRC,UPM0);
        	SET_BIT(UCSRC,UPM1);
            break;
    }

    /* Set stop bit(s) */
    if(Config_Ptr->stop_bit == UART_2_STOP_BITS)
    {
    	SET_BIT(UCSRC,USBS);
    }
    else
    {
        CLEAR_BIT(UCSRC,USBS);
    }

    /* Calculate the UBRR value for the given baud rate */
    ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

    /* Set the baud rate */
    UBRRH = ubrr_value >> 8;
    UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(IS_BIT_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(IS_BIT_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
    return UDR;		
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

/*
 * Description :
 * Flushes all the data stored in the UART
 */
void UART_flush(void)
{
    uint8 dummy;
    while (UCSRA & (1<<RXC))  // Check if data is in the buffer
    {
        dummy = UDR;  // Read and discard data
    }
}
