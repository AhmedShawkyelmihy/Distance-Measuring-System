/*
 ============================================================================
 Name        : icu.h
 Author      : Ahmed Shawky
 Description : Header File for ICU Driver
 Date        : 03/09/2023
 ============================================================================
 */

#ifndef ICU_H_
#define ICU_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <avr/interrupt.h>
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define ICU_INPUT_PORT 		PORTD_ID
#define ICU_INPUT_PIN 		PIN6_ID

/****************************************************************************
 * 					          Types Declaration						        *
 ****************************************************************************/
typedef enum
{
	FALLING_EDGE ,
	RISING_EDGE
}ICU_EdgeType;

typedef enum
{
	NO_CLOCK ,
	F_CPU_CLOCK ,
	F_CPU_8 ,
	F_CPU_64 ,
	F_CPU_256 ,
	F_CPU_1024
}ICU_Clock;

typedef struct
{
	ICU_EdgeType edge ;
	ICU_Clock clock ;
}ICU_ConfigType;

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs:
 * 	1. Pointer to the configuration structure with type ICU_ConfigType.
 *
 * Return Value: void.
 *
 * Description:
 * 	Function to initialize the ICU driver
 * 		1. Set the required edge detection.
 * 		2. Set the required clock.
 * 		3. Enable the Input Capture Interrupt.
 * 		4. Initialize Timer1 Registers.
 */
void ICU_init(const ICU_ConfigType * Config_Ptr);

/* Inputs:
 * 	1. Pointer to function has a parameter void and return void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/* Inputs:
 * 	1. The required edge detection.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/* Inputs: void.
 *
 * Return Value: Input Capture Register ICR1 value.
 *
 * Description:
 *	Function to get the Timer1 Value when the input is captured.
 *	The value stored at Input Capture Register ICR1.
 */
uint16 ICU_getInputCaptureValue(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to clear the Timer1 Value to start count from ZERO.
 */
void ICU_clearTimerValue(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to disable the Timer1 to stop the ICU Driver.
 */
void ICU_DeInit(void);



#endif /* ICU_H_ */
