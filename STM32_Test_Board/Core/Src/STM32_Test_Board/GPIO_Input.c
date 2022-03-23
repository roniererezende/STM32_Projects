/*
 * GPIO_Input.c
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void GPIO_Input_Init(void)
{
	STM32_Test_Board.GPIO_Input.Button_One.portX       = BUTTON_ONE_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_One.pinX 	   = BUTTON_ONE_Pin;
	STM32_Test_Board.GPIO_Input.Button_One.Pull_Type   = Button_Pull_Up;

	STM32_Test_Board.GPIO_Input.Button_Two.portX       = BUTTON_TWO_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_Two.pinX        = BUTTON_TWO_Pin;
	STM32_Test_Board.GPIO_Input.Button_Two.Pull_Type   = Button_Pull_Up;

	STM32_Test_Board.GPIO_Input.Button_Three.portX     = BUTTON_THREE_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_Three.pinX 	   = BUTTON_THREE_Pin;
	STM32_Test_Board.GPIO_Input.Button_Three.Pull_Type = Button_Pull_Up;

	STM32_Test_Board.GPIO_Input.Button_Four.portX      = BUTTON_FOUR_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_Four.pinX       = BUTTON_FOUR_Pin;
	STM32_Test_Board.GPIO_Input.Button_Four.Pull_Type  = Button_Pull_Up;

	STM32_Test_Board.GPIO_Input.Button_Five.portX      = BUTTON_FIVE_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_Five.pinX 	   = BUTTON_FIVE_Pin;
	STM32_Test_Board.GPIO_Input.Button_Five.Pull_Type  = Button_Pull_Up;
}

void GPIO_Input_Reading_Button(s_Button *Button)
{
	if(Button->Pull_Type == Button_Pull_Down)
	{
		Button->Reading_Pressed = ((_Bool)HAL_GPIO_ReadPin(Button->portX, Button->pinX));
	}
	else if(Button->Pull_Type == Button_Pull_Up)
	{
		Button->Reading_Pressed = !((_Bool)HAL_GPIO_ReadPin(Button->portX, Button->pinX));
	}
}

void GPIO_Input_Process(void)
{
	if(STM32_Test_Board.GPIO_Input.Timers.Generic == 0)
	{
		GPIO_Input_Process_Button(&STM32_Test_Board.GPIO_Input.Button_One);
		GPIO_Input_Process_Button(&STM32_Test_Board.GPIO_Input.Button_Two);
		GPIO_Input_Process_Button(&STM32_Test_Board.GPIO_Input.Button_Three);
		GPIO_Input_Process_Button(&STM32_Test_Board.GPIO_Input.Button_Four);
		GPIO_Input_Process_Button(&STM32_Test_Board.GPIO_Input.Button_Five);

		STM32_Test_Board.GPIO_Input.Timers.Generic = GPIO_INPUT_DELAY_AMONG_EACH_SAMPLE;
	}

	if(STM32_Test_Board.GPIO_Input.Timers.Timer_Hold_Buttons == 0)
	{
		GPIO_Input_Process_Button_One();
		GPIO_Input_Process_Button_Two();
		GPIO_Input_Process_Button_Three();
		GPIO_Input_Process_Button_Four();
		GPIO_Input_Process_Button_Five();
		STM32_Test_Board.GPIO_Input.Timers.Timer_Hold_Buttons = GPIO_INPUT_DELAY_AMONG_EACH_PROCESSING_KEY;
	}
}

void GPIO_Input_Process_Button(s_Button *Button)
{
	switch(Button->State)
	{
		case E_Button_Start:
			Button->Debounce_Average = 0;
			Button->Samples_Counter   = 0;
			Button->Behavior         = Button_No_Pressed;
			Button->State            = E_Button_Waiting_First_Pressing;
		break;

		case E_Button_Waiting_First_Pressing:
			if(STM32_Test_Board.GPIO_Input.Performing_Debounce_Any_Key)
			{
				break;
			}

			GPIO_Input_Reading_Button(Button);

			if(Button->Reading_Pressed)
			{
				Button->State = E_Button_Performing_Debounce_Pressing;
				Button->Debounce_Average = 0;
				STM32_Test_Board.GPIO_Input.Performing_Debounce_Any_Key = true;
			}
		break;

		case E_Button_Performing_Debounce_Pressing:
			GPIO_Input_Reading_Button(Button);
			Button->Debounce_Average += Button->Reading_Pressed;
			Button->Samples_Counter++;

			if(Button->Samples_Counter >= GPIO_INPUT_DEBOUNCE_AVERAGE_NUMBER)
			{
				Button->Debounce_Average = (float)Button->Debounce_Average / Button->Samples_Counter;

				if(Button->Debounce_Average >= GPIO_SUCCESS_DEBOUNCE_THRESHOLD)
				{
					Button->Behavior = Button_Held;
					Button->Debounce_Average = 0;
					Button->Samples_Counter  = 0;
					Button->State = E_Button_Waiting_First_Releasing;
					Button->Should_Ignore_Behavior_Clicked = false;
				}
				else
				{
					Button->Behavior = Button_No_Pressed;
					Button->State    = E_Button_Start;
					STM32_Test_Board.GPIO_Input.Performing_Debounce_Any_Key = false;
				}
			}
		break;

		case E_Button_Waiting_First_Releasing:
			GPIO_Input_Reading_Button(Button);
			if(!Button->Reading_Pressed)
			{
				Button->State = E_Button_Performing_Debounce_Releasing;
			}
		break;

		case E_Button_Performing_Debounce_Releasing:
			GPIO_Input_Reading_Button(Button);
			Button->Debounce_Average += Button->Reading_Pressed;
			Button->Samples_Counter++;

			if(Button->Samples_Counter >= GPIO_INPUT_DEBOUNCE_AVERAGE_NUMBER)
			{
				Button->Debounce_Average = (float)Button->Debounce_Average / Button->Samples_Counter;

				if(Button->Debounce_Average <= (float)(1 - GPIO_SUCCESS_DEBOUNCE_THRESHOLD) && Button->Should_Ignore_Behavior_Clicked == false)
				{
					Button->Behavior = Button_Clicked;
					Button->Waiting_Perform_Function = true;
					STM32_Test_Board.GPIO_Input.Timers.Timer_Hold_Buttons = 0;
					STM32_Test_Board.GPIO_Input.Performing_Debounce_Any_Key = false;
					Button->State = E_Button_Start;
				}
				else
				{
					Button->Debounce_Average = 0;
					Button->Samples_Counter = 0;
					Button->Behavior = Button_No_Pressed;
					Button->State = E_Button_Waiting_First_Pressing;
					Button->Waiting_Perform_Function = false;
					STM32_Test_Board.GPIO_Input.Performing_Debounce_Any_Key = false;
				}
			}
		break;
	}
}

_Bool GPIO_Input_Any_Button_Is_Waiting_perform_Function(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_One.Waiting_Perform_Function   ||
	   STM32_Test_Board.GPIO_Input.Button_Two.Waiting_Perform_Function   ||
	   STM32_Test_Board.GPIO_Input.Button_Three.Waiting_Perform_Function ||
	   STM32_Test_Board.GPIO_Input.Button_Four.Waiting_Perform_Function  ||
	   STM32_Test_Board.GPIO_Input.Button_Five.Waiting_Perform_Function )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GPIO_Input_Process_Button_One(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_One.Behavior == Button_Clicked)
	{
		LED_LIGHT_LOW_STATE;
	}
	else
	{
		LED_LIGHT_TOGGLE_STATE;
	}
}

void GPIO_Input_Process_Button_Two(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_Two.Behavior == Button_Clicked)
	{
		LED_YELLOW_LOW_STATE;
	}
	else
	{
		LED_YELLOW_TOGGLE_STATE;
	}
}

void GPIO_Input_Process_Button_Three(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_Three.Behavior == Button_Clicked)
	{
		LED_BLUE_A_LOW_STATE;
	}
	else
	{
		LED_BLUE_A_TOGGLE_STATE;
	}
}

void GPIO_Input_Process_Button_Four(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_Four.Behavior == Button_Clicked)
	{
		LED_RED_A_LOW_STATE;
	}
	else
	{
		LED_RED_A_TOGGLE_STATE;
	}
}

void GPIO_Input_Process_Button_Five(void)
{
	if(STM32_Test_Board.GPIO_Input.Button_Five.Behavior == Button_Clicked)
	{
		LED_GREEN_LOW_STATE;
	}
	else
	{
		LED_GREEN_TOGGLE_STATE;
	}
}


void GPIO_Input_Processing_Keyboard(void)
{
	/* Button Debounce */
//	if(Neurodyn_DC.Teclado.Timers.Generico == 0)
//	{
//		Teclado_Processar_Botao(&STM32_Test_Board..Teclado.Botao_Intensidade_Mais);
//		Teclado_Processar_Botao(&Neurodyn_DC.Teclado.Botao_Intensidade_Menos);
//		Teclado_Processar_Botao(&Neurodyn_DC.Teclado.Botao_Timer_Mais);
//		Teclado_Processar_Botao(&Neurodyn_DC.Teclado.Botao_Timer_Menos);
//		Teclado_Processar_Botao(&Neurodyn_DC.Teclado.Botao_Start_Stop);
//		//Teclado_Processar_Botao(&Neurodyn_DC.Teclado.Botao_Liga_Desliga);
//
//		Neurodyn_DC.Teclado.Timers.Generico = TECLADO_DELAY_ENTRE_CADA_SAMPLE;
//	}

//	if(HAL_GPIO_ReadPin(BUTTON_ONE_GPIO_Port, BUTTON_ONE_Pin) == false)
//	{
//		LED_LIGHT_LOW_STATE;
//	}
//	else
//	{
//		LED_LIGHT_HIGH_STATE;
//	}
//
//	if(HAL_GPIO_ReadPin(BUTTON_TWO_GPIO_Port, BUTTON_TWO_Pin) == false)
//	{
//		LED_YELLOW_LOW_STATE;
//	}
//	else
//	{
//		LED_YELLOW_HIGH_STATE;
//	}
//
//	if(HAL_GPIO_ReadPin(BUTTON_THREE_GPIO_Port, BUTTON_THREE_Pin) == false)
//	{
//		LED_BLUE_A_LOW_STATE;
//	}
//	else
//	{
//		LED_BLUE_A_HIGH_STATE;
//	}
//
//	if(HAL_GPIO_ReadPin(BUTTON_FOUR_GPIO_Port, BUTTON_FOUR_Pin) == false)
//	{
//		LED_RED_A_LOW_STATE;
//	}
//	else
//	{
//		LED_RED_A_HIGH_STATE;
//	}
//
//	if(HAL_GPIO_ReadPin(BUTTON_FIVE_GPIO_Port, BUTTON_FIVE_Pin) == false)
//	{
//		LED_GREEN_LOW_STATE;
//	}
//	else
//	{
//		LED_GREEN_HIGH_STATE;
//	}
}


