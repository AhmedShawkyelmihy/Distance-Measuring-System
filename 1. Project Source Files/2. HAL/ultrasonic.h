/*
 ============================================================================
 Name        : ultrasonic.h
 Author      : Ahmed Shawky
 Description : Header File for Ultrasonic Driver
 Date        : 04/09/2023
 ============================================================================
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include <util/delay.h>
#include "gpio.h"
#include "icu.h"

/****************************************************************************
 * 								 Definitions								*
 ****************************************************************************/
#define ULTRASONIC_TRIGGER_INPUT_PORT 		PORTB_ID
#define ULTRASONIC_TRIGGER_INPUT_PIN 		PIN5_ID

/****************************************************************************
 * 							Functions Prototypes						    *
 ****************************************************************************/

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	1. Initialize the ICU driver as required.
 *	2. Setup the ICU call back function.
 *	3. Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void);

/* Inputs: void.
 *
 * Return Value: The measured distance in Centimeter.
 *
 * Description:
 *	1. Send the trigger pulse by using Ultrasonic_Trigger function.
 *	2. Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void);

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	1. This is the call back function called by the ICU driver.
 *	2. This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */