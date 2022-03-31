/*
 * STM32_Test_Board.c
 *
 *  Created on: Mar 14, 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/* Structure Declaration */
s_STM32_Test_Board STM32_Test_Board;

/* Main Project Routine */
void STM32_Test_Board_Main(void)
{
	switch (STM32_Test_Board.States)
	{
		// Initializes all peripheral here
		case E_Initialization:
			HAL_TIM_Base_Start_IT(&htim3); // Starts timer for General Functions
			HAL_TIM_Base_Start_IT(&htim6); // Starts timer for General Functions
			GPIO_Input_Init();
			Display_16x2_Init();
			Display_16x2_Disable_Cursor();
			STM32_Test_Board.States = E_Execution;

			STM32_Test_Board.Display_16x2.Update = true;
		break;

		// Performs all routines here
		case E_Execution:
			if(STM32_Test_Board.Display_16x2.Update == true)
			{
				Display_16x2_Return_Home();
				Display_16x2_Write_Text("STM32 TEST BOARD");
				STM32_Test_Board.Display_16x2.Update = false;
			}
			GPIO_Input_Process();
		break;
	}
}
