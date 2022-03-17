/*
 * GPIO_Output.c
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void GPIO_Output_Execution(void)
{
	LED_RED_HIGH_STATE;
	LED_LIGHT_TOGGLE_STATE;
	HAL_Delay(500);
}

