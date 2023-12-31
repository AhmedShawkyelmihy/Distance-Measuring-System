/*
 ============================================================================
 Name        : ultrasonic.c
 Author      : Ahmed Shawky
 Description : Source File for Ultrasonic Driver
 Date        : 04/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "ultrasonic.h"

/****************************************************************************
 * 						   Static Global Variables						    *
 ****************************************************************************/
static uint8 g_counter ;
static uint8 g_flag ;
static uint16 g_HighTime ;

/****************************************************************************
 * 							Functions Definitions						    *
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
void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_ConfigStruct ;
	ICU_ConfigStruct.clock = F_CPU_8 ;
	ICU_ConfigStruct.edge = RISING_EDGE ;
	ICU_init(&ICU_ConfigStruct);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_INPUT_PORT, ULTRASONIC_TRIGGER_INPUT_PIN, PIN_OUTPUT);
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_INPUT_PORT, ULTRASONIC_TRIGGER_INPUT_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_INPUT_PORT, ULTRASONIC_TRIGGER_INPUT_PIN, LOGIC_LOW);
}

/* Inputs: void.
 *
 * Return Value: The measured distance in Centimeter.
 *
 * Description:
 *	1. Send the trigger pulse by using Ultrasonic_Trigger function.
 *	2. Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	while(!(g_flag == 1));
	g_flag = 0 ;
	return ((float)g_HighTime / 58) ;
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	1. This is the call back function called by the ICU driver.
 *	2. This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_counter += 1 ;
	switch(g_counter)
	{
	case 1 :
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING_EDGE);
		break;
	case 2 :
		g_HighTime = ICU_getInputCaptureValue();
		g_flag = 1 ;
		g_counter = 0 ;
		ICU_DeInit();
		break;
	}
}


