/*
 * Screen.c
 *
 *  Created on: Apr 5, 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"


void Screen_Mount_Temperature(void)
{
	if(STM32_Test_Board.Navegation.Should_Mount_Screen == true)
	{
		Display_16x2_Clear();
		Display_16x2_Printf("STM32 Test Board");

		Display_16x2_Set_Cursor(1, 0);
		Display_16x2_Printf("Temperature:");

		Display_16x2_Set_Cursor(1, 14);
		Display_16x2_Print_Character(0);

		Display_16x2_Set_Cursor(1, 15);
		Display_16x2_Printf("C");

		STM32_Test_Board.Navegation.Should_Mount_Screen = false;
	}
}

void Screen_Mount_Potenciometer(void)
{
	if(STM32_Test_Board.Navegation.Should_Mount_Screen == true)
	{
		Display_16x2_Clear();
		Display_16x2_Printf("STM32 Test Board");

		Display_16x2_Set_Cursor(1, 0);
		Display_16x2_Printf("Pot:");

		Display_16x2_Set_Cursor(1, 15);
		Display_16x2_Printf("V");

		STM32_Test_Board.Navegation.Should_Mount_Screen = false;
	}
}

void Screen_Mount_Serial_Data(void)
{
	if(STM32_Test_Board.Navegation.Should_Mount_Screen == true)
	{
		Display_16x2_Clear();
		Display_16x2_Printf("STM32 Test Board");
		Display_16x2_Set_Cursor(1, 0);

		Display_16x2_Set_Cursor(1, 0);
		Display_16x2_Printf("Serial:");

		STM32_Test_Board.Navegation.Should_Mount_Screen = false;
	}
}

void Screen_Mount_PWM(void)
{
	if(STM32_Test_Board.Navegation.Should_Mount_Screen == true)
	{
		Display_16x2_Clear();
		Display_16x2_Printf("STM32 Test Board");
		Display_16x2_Set_Cursor(1, 0);

		Display_16x2_Set_Cursor(1, 0);
		Display_16x2_Printf("PWM:");

		Display_16x2_Set_Cursor(1, 12);
		Display_16x2_Print_Character(0x25);

		STM32_Test_Board.Navegation.Should_Mount_Screen = false;
	}
}

void Screen_Mount_DAC(void)
{
	if(STM32_Test_Board.Navegation.Should_Mount_Screen == true)
	{
		Display_16x2_Clear();
		Display_16x2_Printf("STM32 Test Board");
		Display_16x2_Set_Cursor(1, 0);

		Display_16x2_Set_Cursor(1, 0);
		Display_16x2_Printf("FREQ:");

		Display_16x2_Set_Cursor(1, 9);
		Display_16x2_Printf("000");

		Display_16x2_Set_Cursor(1, 13);
		Display_16x2_Printf("Hz");

		STM32_Test_Board.Navegation.Should_Mount_Screen = false;
	}
}
