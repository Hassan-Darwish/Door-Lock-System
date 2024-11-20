/*------------------------------------------------------------------------------
 *  Module      : TIMERs Driver
 *  File        : TIMER.h
 *  Description : Header file for the ATmega32 microcontroller TIMER driver
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

#include "stdtypes.h"

/*------------------------------------------------------------------------------
 *  Data Types Declarations
 *----------------------------------------------------------------------------*/

/**
 * Enum: TIMER_ID_Type
 * Description: Identifies the available timers (Timer0, Timer1, and Timer2).
 */
typedef enum
{
    TIMER_TIMER0,  // Timer 0
    TIMER_TIMER1,  // Timer 1
    TIMER_TIMER2   // Timer 2
} TIMER_ID_Type;

/**
 * Enum: TIMER_ClockType
 * Description: Represents the clock source and prescaler settings for timers.
 * Note: `TIMER_PRESCALER_32` and `TIMER_PRESCALER_128` are applicable only for `TIMER2`.
 */
typedef enum
{
    TIMER_NO_CLOCK_SOURCE,  // Timer disabled
    TIMER_NO_PRESCALING,    // No prescaler
    TIMER_PRESCALER_8,      // Prescaler of 8
    TIMER_PRESCALER_32,     // Prescaler of 32 (TIMER2 only)
    TIMER_PRESCALER_64,     // Prescaler of 64
    TIMER_PRESCALER_128,    // Prescaler of 128 (TIMER2 only)
    TIMER_PRESCALER_256,    // Prescaler of 256
    TIMER_PRESCALER_1024    // Prescaler of 1024
} TIMER_ClockType;

/**
 * Enum: TIMER_ModeType
 * Description: Defines the operational mode for the timer (Overflow or Compare Mode).
 */
typedef enum
{
    TIMER_OVERFLOW_MODE,    // Timer overflow mode
    TIMER_COMPARE_MODE      // Timer compare match mode
} TIMER_ModeType;

/**
 * Struct: TIMER_ConfigType
 * Description: Configuration structure for timer initialization.
 * Fields:
 *   - TIMER_InitialValue: Initial count value for the timer.
 *   - TIMER_compare_MatchValue: Compare match value (used in compare mode).
 *   - TIMER_ID: Specifies the timer to configure (TIMER_TIMER0, TIMER_TIMER1, TIMER_TIMER2).
 *   - TIMER_clock: Clock source and prescaler for the timer.
 *   - TIMER_mode: Operational mode (overflow or compare mode).
 */
typedef struct
{
    uint16 TIMER_InitialValue;          // Timer starting count value
    uint16 TIMER_compare_MatchValue;    // Compare match value for match-based interrupt
    TIMER_ID_Type TIMER_ID;             // Specifies timer ID (0, 1, or 2)
    TIMER_ClockType TIMER_clock;        // Clock/prescaler selection for the timer
    TIMER_ModeType TIMER_mode;          // Mode selection (Overflow or Compare)
} TIMER_ConfigType;

/*------------------------------------------------------------------------------
 *  Function Declarations
 *----------------------------------------------------------------------------*/

/**
 * Function: TIMER_init
 * Description: Initializes the specified timer with settings from the provided
 *              configuration structure.
 * Parameters:
 *   - Config_Ptr: Pointer to configuration structure (TIMER_ConfigType).
 */
void TIMER_init(const TIMER_ConfigType * Config_Ptr);

/**
 * Function: TIMER_setCallBack
 * Description: Registers a callback function to be executed in the timer's ISR.
 * Parameters:
 *   - a_ptr: Pointer to the callback function.
 *   - a_TIMER_ID: Timer identifier to assign the callback.
 */
void TIMER_setCallBack(void (*a_ptr)(void), TIMER_ID_Type a_TIMER_ID);

/**
 * Function: TIMER_deInit
 * Description: Deinitializes the specified timer, resetting its settings and
 *              disabling interrupts.
 * Parameters:
 *   - TIMER_type: Timer identifier to be deinitialized.
 */
void TIMER_deInit(TIMER_ID_Type TIMER_type);

#endif /* TIMER_H_ */
