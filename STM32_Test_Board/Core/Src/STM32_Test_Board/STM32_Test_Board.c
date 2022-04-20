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
			STM32_Test_Board_Initialization();
		break;

		// Performs all routines here
		case E_Execution:
			STM32_Test_Board_Execution();
		break;
	}

	GPIO_Input_Process();
	ADC_Peripheral_Get_Samples();
	Navegation_Processing();
	USART_Peripheral_Transmit_Receive();
}

void STM32_Test_Board_Initialization(void)
{
	STM32_Test_Board.PWM_Output.Value = 5;

	HAL_TIM_Base_Start_IT(&htim3); // Starts timer for General Functions
	HAL_TIM_Base_Start_IT(&htim6); // Starts timer for General Functions
	HAL_TIM_Base_Start(&htim7);



	HAL_UARTEx_ReceiveToIdle_DMA(&huart2, STM32_Test_Board.Screen.Buffer, USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);

	__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

	PWM_Output_Init();

	GPIO_Input_Init();

	Display_16x2_Init();

	ADC_Peripheral_Init();

	STM32_Test_Board.States = E_Execution;
	STM32_Test_Board.Show_Data = e_Temperature;

	STM32_Test_Board.Navegation.Should_Mount_Screen = true;

	STM32_Test_Board.USART_Peripheral.Time_Transmit = USART_TIME_TRANSMIT;
	STM32_Test_Board.USART_Peripheral.Transmit_Enable = true;

	STM32_Test_Board.PWM_Output.Update = true;
}

void STM32_Test_Board_Execution(void)
{
	STM32_Test_Board_Update_Data();
}

void STM32_Test_Board_Update_Data(void)
{
	switch(STM32_Test_Board.Show_Data)
	{
		case e_Temperature:
			if(STM32_Test_Board.ADC_Peripheral.Update == true)
			{
				Display_16x2_Set_Cursor(1, 12);
				Display_16x2_Print_Integer_Number(STM32_Test_Board.ADC_Peripheral.Temperature);
				STM32_Test_Board.ADC_Peripheral.Counter_Update = TIMER_UPDATE_TEMPERATURE;
				STM32_Test_Board.ADC_Peripheral.Update = false;
			}
		break;

		case e_Potenciometer:
			if(STM32_Test_Board.ADC_Peripheral.Update == true)
			{
				Display_16x2_Set_Cursor(1, 12);
				Display_16x2_Print_Integer_Number(STM32_Test_Board.ADC_Peripheral.Potenciometer.Voltage);
				Display_16x2_Print_Float_Number(STM32_Test_Board.ADC_Peripheral.Potenciometer.Voltage, 1, 10);
				STM32_Test_Board.ADC_Peripheral.Counter_Update = TIMER_UPDATE_POTENCIOMETER;
				STM32_Test_Board.ADC_Peripheral.Update = false;
			}
		break;

		case e_Serial_Data:
			if(STM32_Test_Board.USART_Peripheral.Clear == true)
			{
				Display_16x2_Set_Cursor(1, 7);
				Display_16x2_Printf("        ");
				Display_16x2_Set_Cursor(1, 7);
				Display_16x2_Printf((char*)&STM32_Test_Board.Screen.Buffer);
				strcpy((char*)STM32_Test_Board.Screen.Previous_Buffer, (char*)STM32_Test_Board.Screen.Buffer);

				memset(STM32_Test_Board.Screen.Buffer, 0, USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);

				STM32_Test_Board.USART_Peripheral.Clear = false;
			}
		break;

		case e_PWM:
			if(STM32_Test_Board.PWM_Output.Update == true)
			{
				TIM14->CCR1 = STM32_Test_Board.PWM_Output.Value;
				Display_16x2_Set_Cursor(1, 9);
				Display_16x2_Printf("   ");
				Display_16x2_Set_Cursor(1, 9);
				Display_16x2_Print_Integer_Number(STM32_Test_Board.PWM_Output.Printed_Value);
				STM32_Test_Board.PWM_Output.Update = false;
			}
		break;
	}
}
