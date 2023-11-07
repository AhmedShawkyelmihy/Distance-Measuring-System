/*
 ============================================================================
 Name        : Mini_Project4.c
 Author      : Ahmed Shawky
 Description : System to measure the distance using ultrasonic sensor
 Date        : 04/09/2023
 ============================================================================
 */

#include "lcd.h"
#include "ultrasonic.h"

int main()
{
	uint16 distance = 0 ;

	LCD_init();

	LCD_displayString("Distance = ");

	//Ultrasonic_init();

	while(1)
	{
		Ultrasonic_init();
		LCD_moveCursor(0, 11);
		distance = Ultrasonic_readDistance();
		if(distance >= 100)
		{
			LCD_integerToString(distance);
			LCD_displayString("cm");
		}
		else
		{
			LCD_integerToString(distance);
			LCD_displayString("cm ");
		}
	}

	return 0 ;
}
