/*
 * Display_16x2.c
 *
 *  Created on: 30 de mar de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/****************************************************************/
/* 				FUN��O PARA INICIAR DISPLAY 16x2				*/
/****************************************************************/
void Display_16x2_Init(void)
{
	HAL_Delay(200);

	Display_16x2_Clear();

	ENB_LOW;
	RS_CMD;

	Display_16x2_Send_Command(CMD_FUNCTION_SET);
	HAL_Delay(10);

	Display_16x2_Send_Command(CMD_FUNCTION_SET);
	HAL_Delay(10);

	Display_16x2_Send_Command(CMD_FUNCTION_SET_16x2);
	HAL_Delay(10);

	Display_16x2_Send_Command(CMD_FUNCTION_SET_16x2);
	HAL_Delay(10);

	Display_16x2_Clear();

	Display_16x2_Send_Command(CMD_DISPLAY_CONTROL);
	HAL_Delay(10);

	return;
}

/********************************************************/
/*     FUNCTION TO SEND DATA WITH NIBBLE CONVERSION     */
/********************************************************/
unsigned char Display_16x2_Position(char Column, char Line)
{
	unsigned char Status = LCD_ERROR;

	if((Column >= 0) && (Column <= 15))
	{
		Status = LCD_OK;
		switch (Line)
		{
			case 0:
				Display_16x2_Send_Command(Column|CMD_ADDRESS_LINE_0);
				break;

			case 1:
				Display_16x2_Send_Command(Column|CMD_ADDRESS_LINE_1);
				break;

			default:
				Status = LCD_ERROR;
				break;
		}
	}
	return(Status);
}

/****************************************************************/
/* 		FUN��O PARA ENVIO DE DADOS COM CONVERS�O DE NIBBLE		*/
/****************************************************************/
void Display_16x2_Send_Nibble(unsigned char Data_Nibble)
{
	ENB_HIGH; // EN = 1
	HAL_Delay(10);

	HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_7,DATA_LCD_BIT_7,((Data_Nibble & 0x08)!=0 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_6,DATA_LCD_BIT_6,((Data_Nibble & 0x04)!=0 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_5,DATA_LCD_BIT_5,((Data_Nibble & 0x02)!=0 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_4,DATA_LCD_BIT_4,((Data_Nibble & 0x01)!=0 ? GPIO_PIN_SET: GPIO_PIN_RESET));

	ENB_LOW; // EN = 0
	HAL_Delay(10);;

	return;
}

/****************************************************************/
/* 		FUN��O PARA ENVIO DE DADOS PARA COMANDO DISPLAY  		*/
/****************************************************************/
void Display_16x2_Send_Command(unsigned char Data_Command)
{
	RS_CMD;

	Display_16x2_Send_Nibble(Data_Command >> 4);
	Display_16x2_Send_Nibble(Data_Command & 0x0F);
	return;
}

/****************************************************************/
/* 		FUN��O PARA ENVIO DE DADOS PARA DADOS DISPLAY  		    */
/****************************************************************/
void Display_16x2_Send_Data(unsigned char Data_Command)
{
	RS_DATA;

	Display_16x2_Send_Nibble(Data_Command >> 4);
	Display_16x2_Send_Nibble(Data_Command & 0x0F);
	return;
}

/****************************************************************/
/* 					FUN��O PARA LIMPAR O  DISPLAY  		        */
/****************************************************************/
void Display_16x2_Clear(void)
{
	Display_16x2_Send_Command(CMD_CLEAR_DISPLAY);
	HAL_Delay(4);
	return;
}

/********************************************************/
/*     FUNCTION TO RETURN THE ORIGINAL POSITION         */
/********************************************************/
void Display_16x2_Return_Home(void)
{
	Display_16x2_Send_Command(CMD_CURSOR_HOME);
	HAL_Delay(4);
	return;
}

/********************************************************/
/* 		FUNCTION TO SEND DATA TO LCD TEXT               */
/********************************************************/
void Display_16x2_Write_Text(char *Text_LCD)
{
	while(*Text_LCD)
	{
		Display_16x2_Send_Data(*Text_LCD++);
	}
}

void Display_16x2_All_High(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4 ,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5 ,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_SET);
}

void Display_16x2_All_Low(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_RESET);
}

/**********************/
/* 				FUN��O PARA POSI��O XY DO TEXTO DISPLAY		    */
/**********************/
void Display_16x2_Write_Text_Position(char *Text_LCD_Position,unsigned char Column, unsigned char Line)
{
	if(Display_16x2_Position(Column, Line))
	{
		Display_16x2_Write_Text(Text_LCD_Position);
	}
	return;
}

/**********************/
/* 				FUN��O PARA HABILITAR OU DESABILITAR O CURSOR		    */
/**********************/
void Display_16x2_Disable_Cursor(void)
{
	Display_16x2_Send_Command(CMD_DISABLE_CURSOR);
}

void Display_16x2_Enable_Cursor(void)
{
	Display_16x2_Send_Command(CMD_DISPLAY_CONTROL);
}

void Display_16x2_Write_Number_Char(unsigned char Number)
{
	Display_16x2_Send_Data(Number >= 100 ?(((Number/100)%10)+'0'):' ');
	Display_16x2_Send_Data((Number >= 100)?(((Number/10)%10)+'0'):(((Number/10)%10))>0?(((Number/10)%10)+'0'):' ');
	Display_16x2_Send_Data(((Number%10)+'0'));
	return;
}
