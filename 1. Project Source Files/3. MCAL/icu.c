/*
 ============================================================================
 Name        : icu.c
 Author      : Ahmed Shawky
 Description : Source File for ICU Driver
 Date        : 03/09/2023
 ============================================================================
 */

/****************************************************************************
 * 								  Includes								    *
 ****************************************************************************/
#include "icu.h"

/****************************************************************************
 * 						   Static Global Variables							*
 ****************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR ;

/****************************************************************************
 * 						  Interrupt Service Routines						*
 ****************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	/* ICF1 is automatically cleared when the Input Capture Interrupt Vector is executed.
	 * Alternatively, ICF1 can be cleared by writing a logic one to its bit location.
	 */
	TIFR |= (1<<ICF1) ;

	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		g_callBackPtr();
	}
}

/****************************************************************************
 * 							Functions Definitions						    *
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
void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	/* Configure ICP1/PD6 as input pin. */
	GPIO_setupPinDirection(ICU_INPUT_PORT, ICU_INPUT_PIN, PIN_INPUT);

	/* Timer1 always operates in Normal Mode. */
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B) ;

	/* Insert the required edge type in ICES1 bit in TCCR1B Register. */
	switch(Config_Ptr->edge)
	{
	case FALLING_EDGE :
		TCCR1B &= ~(1<<ICES1) ;
		break;
	case RISING_EDGE :
		TCCR1B |= (1<<ICES1) ;
		break;
	}

	/* Insert the required clock value in the first
	 * three bits (CS10, CS11 and CS12) of TCCR1B Register. */
	switch(Config_Ptr->clock)
	{
	case NO_CLOCK :
		TCCR1B = ( TCCR1B & 0xF8 ) | NO_CLOCK ;
		break;
	case F_CPU_CLOCK :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_CLOCK ;
		break;
	case F_CPU_8 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_8 ;
		break;
	case F_CPU_64 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_64 ;
		break;
	case F_CPU_256 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_256 ;
		break;
	case F_CPU_1024 :
		TCCR1B = ( TCCR1B & 0xF8 ) | F_CPU_1024 ;
		break;
	}

	/* Initial Value for Timer1 */
	TCNT1 = 0 ;

	/* Initial Value for the input capture register */
	ICR1 = 0 ;

	sei();

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	TIMSK |= (1<<TICIE1) ;
}

/* Inputs:
 * 	1. Pointer to function has a parameter void and return void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr ;
}

/* Inputs:
 * 	1. The required edge detection.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType)
{
	/* Insert the required edge type in ICES1 bit in TCCR1B Register. */
	switch(edgeType)
	{
	case FALLING_EDGE :
		TCCR1B &= ~(1<<ICES1) ;
		break;
	case RISING_EDGE :
		TCCR1B |= (1<<ICES1) ;
		break;
	}
}

/* Inputs: void.
 *
 * Return Value: Input Capture Register ICR1 value.
 *
 * Description:
 *	Function to get the Timer1 Value when the input is captured.
 *	The value stored at Input Capture Register ICR1.
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1 ;
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to clear the Timer1 Value to start count from ZERO.
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0 ;
}

/* Inputs: void.
 *
 * Return Value: void.
 *
 * Description:
 *	Function to disable the Timer1 to stop the ICU Driver.
 */
void ICU_DeInit(void)
{
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,TICIE1);
}




