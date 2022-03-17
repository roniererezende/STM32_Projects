/*
 * GPIO_Input.c
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void GPIO_Input_Execution(void)
{

}

void Teclado_Iniciar(void)
{
	STM32_Test_Board.GPIO_Input.Button_One.portX         = BUTTON_ONE_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_One.pinX 		 = BUTTON_ONE_Pin;
	STM32_Test_Board.GPIO_Input.Button_One.Tipo_De_Pull  = Botao_Pull_Up;

	STM32_Test_Board.GPIO_Input.Button_Two.portX        = BUTTON_TWO_GPIO_Port;
	STM32_Test_Board.GPIO_Input.Button_Two.pinX         = BUTTON_TWO_Pin;
	STM32_Test_Board.GPIO_Input.Button_Two.Tipo_De_Pull = Botao_Pull_Up;
}
