/*------------------------------------------------------------------------------
 *  Module      : Standard Types
 *  File        : stdtypes.h
 *  Description : Header file for the constant types and shortcuts
 *  Author      : Hassan Darwish
 *----------------------------------------------------------------------------*/

#ifndef STDTYPES_H_
#define STDTYPES_H_


/*------------------------------------------------------------------------------
 *  Pre-Processor Constants and Configurations
 *----------------------------------------------------------------------------*/

#define LOGIC_HIGH            1u       // Logic high value
#define LOGIC_LOW             0u       // Logic low value

#define NULL				  ((void*)0) // NULL POINTER

/* Boolean Values */
#ifndef FALSE
#define FALSE       		(0u)
#endif
#ifndef TRUE
#define TRUE        		(1u)
#endif

/*------------------------------------------------------------------------------
 *  Data Types Declarations
 *----------------------------------------------------------------------------*/


/*  FIXED-WIDTH INTEGER TYPES  */
typedef char                    int8;   // 8-bit signed integer
typedef unsigned char           uint8;  // 8-bit unsigned integer
typedef short                   int16;  // 16-bit signed integer
typedef unsigned short          uint16; // 16-bit unsigned integer
typedef long                    int32;  // 32-bit signed integer
typedef unsigned long           uint32; // 32-bit unsigned integer
typedef long long               int64;  // 64-bit signed integer
typedef unsigned long long      uint64; // 64-bit unsigned integer
typedef float                   float32; // 32-bit floating point
typedef double                  float64; // 64-bit floating point

/* Boolean Data Type */
typedef unsigned char boolean;

#endif /* STDTYPES_H_ */
