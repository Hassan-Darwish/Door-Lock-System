/*------------------------------------------------------------------------------
 *  Module      : bit manipulation methods
 *  File        : bit_manipulation.c
 *  Description : Header file for bit manipulation methods
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/


#define NULL 											((void*)0)

/*
 * SET_BIT:
 * Sets a specific bit (BIT) in a register (REG) by using bitwise OR.
 *
 * Example: SET_BIT(PORTA, 2); // Sets bit 2 in PORTA.
 */
#define SET_BIT(REG,BIT)                                (REG|=(1<<BIT))

/*
 * CLEAR_BIT:
 * Clears a specific bit (BIT) in a register (REG) by using bitwise AND with negation.
 *
 * Example: CLEAR_BIT(PORTA, 2); // Clears bit 2 in PORTA.
 */
#define CLEAR_BIT(REG,BIT)                              (REG&=~(1<<BIT))

/*
 * TOGGLE_BIT:
 * Toggles (inverts) a specific bit (BIT) in a register (REG) by using bitwise XOR.
 *
 * Example: TOGGLE_BIT(PORTA, 2); // Toggles bit 2 in PORTA.
 */
#define TOGGLE_BIT(REG,BIT)                             (REG^=(1<<BIT))

/*
 * GET_BIT:
 * Gets the value of a specific bit (BIT) in a register (REG).
 * Returns 1 if the bit is set, otherwise returns 0.
 *
 * Example: GET_BIT(PINA, 2); // Returns the value of bit 2 in PINA.
 */
#define GET_BIT(REG,BIT)                                ((REG&(1<<BIT))>>BIT)

/*
 * IS_BIT_SET:
 * Checks if a specific bit (BIT) in a register (REG) is set (1).
 *
 * Example: IS_BIT_SET(PINA, 2); // Returns true if bit 2 in PINA is set.
 */
#define IS_BIT_SET(REG,BIT)                             (REG&(1<<BIT))

/*
 * IS_BIT_CLEAR:
 * Checks if a specific bit (BIT) in a register (REG) is clear (0).
 *
 * Example: IS_BIT_CLEAR(PINA, 2); // Returns true if bit 2 in PINA is clear.
 */
#define IS_BIT_CLEAR(REG,BIT)                           (!(REG&(1<<BIT)))

#endif /* BIT_MANIPULATION_H_ */
