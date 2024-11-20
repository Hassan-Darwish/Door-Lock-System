/*------------------------------------------------------------------------------
 *  Module      : Control Constants
 *  File        : control_constants.h
 *  Description : Header file containing constants for control module operations
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef CONTROL_CONSTANTS_H_
#define CONTROL_CONSTANTS_H_


/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

#define KEYPAD_PASSWORD_SIZE        5

#define RECIEVE_START_PASSWORD      0x5A
#define SEND_TRUE                   0x5B
#define SEND_FALSE                  0x5C

#define TWI_ADDRESS                 0x65
#define TWI_BITRATE                 2

#define EEPROM_STARTBYTE            0x0310

#define START_PHASE_TWO_CHANGE      0x4A
#define START_PHASE_TWO_DOOR        0x4B
#define PASSWORD_RETRY              0x33
#define PASSWORD_SUCCESS            0x34
#define START_MOTOR                 0x3A
#define TARGET_OVERFLOWS            7324
#define CLEAR                       0x3B
#define SYSTEM_LOCK_SEQUENCE        0x3C
#define LOCK_DOWN_TIME              29296
#define RESET_PASSWORD              0x4C
#define PASSWORD_INCORRECT          0x4D


#endif /* CONTROL_CONSTANTS_H_ */
