/*------------------------------------------------------------------------------
 *  Module      : Control Constants
 *  File        : control_constants.h
 *  Description : Header file containing constants for control module operations
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef HMI_CONSTANTS_H_
#define HMI_CONSTANTS_H_

/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

/* Keypad Constants */
#define KEYPAD_PASSWORD_SIZE                5
#define KEYPAD_MINIMUM_NUMBER               0
#define KEYPAD_MAXIMUM_NUMBER               9
#define KEYPAD_ENTER_BUTTON                 13

/* UART Communication */
#define RECIEVE_TRUE                        0x5B
#define RECIEVE_FALSE                       0x5C
#define SEND_START_PASSWORD                 0x5A

/* Password Verification */
#define MAXIMUM_PASSWORD_ATTEMPTS           3
#define START_PHASE_TWO_CHANGE              0x4A
#define START_PHASE_TWO_DOOR                0x4B
#define PASSWORD_RETRY                      0x33
#define PASSWORD_SUCCESS                    0x34
#define PASSWORD_INCORRECT                  0x4D

/* Motor and Door Control */
#define START_MOTOR                         0x3A
#define START_PHASE_TWO                     0x4C
#define TARGET_OVERFLOWS                    7324
#define CLEAR                               0x3B

/* System Lockdown */
#define SYSTEM_LOCK_SEQUENCE                0x3C
#define LOCK_DOWN_TIME                      29296
#define RESET_PASSWORD                      0x4C

#endif /* HMI_CONSTANTS_H_ */
