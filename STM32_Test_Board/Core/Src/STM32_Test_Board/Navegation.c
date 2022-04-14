/*
 * Navegation.c
 *
 *  Created on: Apr 5, 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void Navegation_Processing(void)
{
	if(!STM32_Test_Board.Navegation.Should_Mount_Screen) return;

	switch(STM32_Test_Board.Navegation.Current_Screen)
	{
		case Screen_Temperature:
			Screen_Mount_Temperature();
		break;

		case Screen_Potenciometer:
			Screen_Mount_Potenciometer();
		break;

		case Screen_Serial_Data:
			Screen_Mount_Serial_Data();
		break;
	}
}
