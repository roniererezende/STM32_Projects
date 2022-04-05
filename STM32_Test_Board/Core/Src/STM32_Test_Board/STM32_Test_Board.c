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
			HAL_TIM_Base_Start(&htim7);

			GPIO_Input_Init();

			Display_16x2_Init();

			ADC_Peripheral_Init();

			STM32_Test_Board.States = E_Execution;

			STM32_Test_Board.Display_16x2.Update = true;
		break;

		// Performs all routines here
		case E_Execution:
			if(STM32_Test_Board.Display_16x2.Update == true)
			{
				Display_16x2_Clear();
				Display_16x2_Printf("STM32 Test Board");
				Display_16x2_Set_Cursor(1, 0);
				Display_16x2_Printf("Temperature:");
				Display_16x2_Set_Cursor(1, 14);
				Display_16x2_Print_Character(0);
				Display_16x2_Set_Cursor(1, 15);
				Display_16x2_Printf("C");
				STM32_Test_Board.Display_16x2.Update = false;
			}
			GPIO_Input_Process();
			ADC_Peripheral_LM35_Get_Sample_Temperature();

			if(STM32_Test_Board.ADC_Peripheral.LM35.Update == true)
			{
				Display_16x2_Set_Cursor(1, 12);
				Display_16x2_Print_Number(STM32_Test_Board.ADC_Peripheral.LM35.Temperature);
				STM32_Test_Board.ADC_Peripheral.LM35.Update = false;
			}


		break;
	}
}
