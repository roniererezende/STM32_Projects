/*
 * GPIO_Output.c
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void GPIO_Output_Execution(void)
{
//	LED_LIGHT_TOGGLE_STATE;
//	HAL_Delay(500);
//	LED_YELLOW_TOGGLE_STATE;
//	HAL_Delay(500);
//	LED_BLUE_A_TOGGLE_STATE;
//	HAL_Delay(500);
	LED_BLUE_B_TOGGLE_STATE;
	HAL_Delay(100);
//	LED_RED_A_TOGGLE_STATE;
//	HAL_Delay(500);
	LED_RED_B_TOGGLE_STATE;
	HAL_Delay(100);
//	LED_GREEN_TOGGLE_STATE;
//	HAL_Delay(500);

	GPIO_Input_Processing_Keyboard();

}

