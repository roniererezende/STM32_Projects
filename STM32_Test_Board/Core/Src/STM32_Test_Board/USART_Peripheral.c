/*
 * USART_Peripheral.c
 *
 *  Created on: Apr 6, 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/* Function Prototype */
void USART_Peripheral_Transmit_Data(uint8_t *Transmit_Data)
{
	char Transmit_Data_Type[USART_MAXIMUM_NUMBER_BITS_DATA_TRANSMIT];

	if(STM32_Test_Board.USART_Peripheral.Transmit_Enable == true)
	{
		switch(STM32_Test_Board.Show_Data)
		{
			case e_Temperature:
				strcpy(Transmit_Data_Type, "Temperature: ");
				strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
			break;

			case e_Potenciometer:
				strcpy(Transmit_Data_Type, "Potenciometer: ");
				strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
			break;

			case e_Serial_Data:
				strcpy(Transmit_Data_Type, "Serial Data: ");
				strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
			break;

			case e_PWM:
				strcpy(Transmit_Data_Type, "PMW: ");
				strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
			break;

			case e_DAC_Signal:
				strcpy(Transmit_Data_Type, "DAC_Signal: ");
				strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
			break;
		}
//		if(STM32_Test_Board.Show_Data == e_Temperature)
//		{
//			strcpy(Transmit_Data_Type, "Temperature: ");
//			strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
//		}
//		else if(STM32_Test_Board.Show_Data == e_Potenciometer)
//		{
//			strcpy(Transmit_Data_Type, "Potenciometer:");
//			strcat((char*)Transmit_Data_Type, (char*)Transmit_Data);
//		}


		HAL_TIM_Base_Stop_IT(&htim3); // Starts timer for General Functions
		HAL_TIM_Base_Stop_IT(&htim6); // Starts timer for General Functions
		HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1); // Stops PWM configured in TIM_14

		if(HAL_UART_Transmit(&huart2, (uint8_t*)Transmit_Data_Type, (uint16_t)(strlen((const char*)Transmit_Data_Type) + 1), 1000) != HAL_OK)
		{
			Error_Handler();
		}

		HAL_TIM_Base_Start_IT(&htim3); // Starts timer for General Functions
		HAL_TIM_Base_Start_IT(&htim6); // Starts timer for General Functions
		HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1); // Starts PWM configured in TIM_14

		STM32_Test_Board.USART_Peripheral.Transmit_Enable = false;
		STM32_Test_Board.USART_Peripheral.Time_Transmit = USART_TIME_TRANSMIT;
	}
}

void USART_Peripheral_Receive_Data(void)
{

}

void USART_Peripheral_Transmit_Receive(void)
{
	char Buffer_Transmit[USART_MAXIMUM_NUMBER_BITS_DATA_TRANSMIT] = {0};
	char Float_Buffer[USART_MAXIMUM_NUMBER_BITS_DATA_TRANSMIT] = {0};
	char Int_Buffer[USART_MAXIMUM_NUMBER_BITS_DATA_TRANSMIT] = {0};
	uint16_t Voltage_Milli_Volts = 0;


	switch(STM32_Test_Board.Show_Data)
	{
		case e_Temperature:
			sprintf(Buffer_Transmit, "%d", STM32_Test_Board.ADC_Peripheral.Temperature);
			strcat((char*)strcpy((char*)Buffer_Transmit, (const char*)Buffer_Transmit), " degrees celsius\n");
		break;

		case e_Potenciometer:
			Voltage_Milli_Volts = STM32_Test_Board.ADC_Peripheral.Potenciometer.Voltage * 1000;
			sprintf(Buffer_Transmit, "%d", Voltage_Milli_Volts / 1000);
			strcat(Buffer_Transmit, ".");
			sprintf(Float_Buffer, "%d",  Voltage_Milli_Volts % 1000);
			strcat(Buffer_Transmit, Float_Buffer);
			strcat(Buffer_Transmit, " V\n");
		break;

		case e_Serial_Data:
			strcat(Buffer_Transmit, (const char*)STM32_Test_Board.Screen.Previous_Buffer);
			strcat(Buffer_Transmit,"\n");
		break;

		case e_PWM:
			sprintf(Int_Buffer, "%d", STM32_Test_Board.PWM_Output.Value *100 / 1000);
			strcat(Buffer_Transmit, Int_Buffer);
			strcat(Buffer_Transmit, " %\n");
			//strcat(Buffer_Transmit, "\n");
		break;

		case e_DAC_Signal:
			sprintf(Int_Buffer, "%d", STM32_Test_Board.DAC_Signal.Frequency);
			strcat(Buffer_Transmit, Int_Buffer);
			strcat(Buffer_Transmit, " Hz \n");

		break;
	}

//	if(STM32_Test_Board.Show_Data == e_Temperature)
//	{
//		sprintf(Buffer_Transmit, "%d", STM32_Test_Board.ADC_Peripheral.Temperature);
//		strcat((char*)strcpy((char*)Buffer_Transmit, (const char*)Buffer_Transmit), " degrees celsius\n");
//	}
//	else if(STM32_Test_Board.Show_Data == e_Potenciometer)
//	{
//		Voltage_Milli_Volts = STM32_Test_Board.ADC_Peripheral.Potenciometer.Voltage * 1000;
//		sprintf(Buffer_Transmit, "%d", Voltage_Milli_Volts / 1000);
//		strcat(Buffer_Transmit, ".");
//		sprintf(Float_Buffer, "%d",  Voltage_Milli_Volts % 1000);
//		strcat(Buffer_Transmit, Float_Buffer);
//		strcat(Buffer_Transmit, " V\n");
//	}


	USART_Peripheral_Transmit_Data((uint8_t*)Buffer_Transmit);
}
