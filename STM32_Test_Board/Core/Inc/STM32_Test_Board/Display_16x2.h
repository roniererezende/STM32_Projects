/*
 * Display_16x2.h
 *
 *  Created on: 30 de mar de 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_DISPLAY_16X2_H_
#define INC_STM32_TEST_BOARD_DISPLAY_16X2_H_

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/* DEFINES */
#define		CMD_FUNCTION_SET		0x20			//CMD_FUNCTION_SET
#define     CMD_FUNCTION_SET_16x2   0x28            // configura LCD, 8 bits, matriz de 7x5, 2 linhas

#define		CMD_CLEAR_DISPLAY		0x01
#define		CMD_CURSOR_HOME			0x02

#define		CMD_ADDRESS_LINE_0		0x80
#define		CMD_ADDRESS_LINE_1		0xC0

#define     LCD_OK					1
#define		LCD_ERROR				0

#define		CMD_DISPLAY_CONTROL		0x0F

#define 	CMD_DISABLE_CURSOR      0x0C

#define		DATA_LCD_BIT_7			GPIO_PIN_4
#define		DATA_LCD_BIT_6			GPIO_PIN_2
#define		DATA_LCD_BIT_5			GPIO_PIN_1
#define		DATA_LCD_BIT_4			GPIO_PIN_0

#define 	DATA_PORT_LCD_BIT_7 	GPIOD
#define 	DATA_PORT_LCD_BIT_6 	GPIOD
#define 	DATA_PORT_LCD_BIT_5 	GPIOD
#define 	DATA_PORT_LCD_BIT_4 	GPIOD

#define		LCD_BIT_ENB			    GPIO_PIN_5
#define		DATA_PORT_LCD_BIT_ENB	GPIOD
#define		ENB_HIGH				HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_ENB,LCD_BIT_ENB,GPIO_PIN_SET);
#define		ENB_LOW					HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_ENB,LCD_BIT_ENB,GPIO_PIN_RESET);
#define		ENB_BLINK				ENB_HIGH; HAL_Delay(1);ENB_LOW;HAL_Delay(1);


#define		LCD_BIT_RS			    GPIO_PIN_4
#define		DATA_PORT_LCD_BIT_RS	GPIOD
#define		RS_CMD					HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_RS,LCD_BIT_RS,GPIO_PIN_RESET);
#define		RS_DATA					HAL_GPIO_WritePin(DATA_PORT_LCD_BIT_RS,LCD_BIT_RS,GPIO_PIN_SET);

/* DISPLAY STRUCTURE */
typedef struct s_Display_16x2
{
	bool Update;
}s_Display_16x2;

/* FUNCTION PROTOTYPE  */
void Display_16x2_Send_Nibble(unsigned char Data_Nibble);
void Display_16x2_Send_Command(unsigned char Data_Command);
void Display_16x2_Send_Data(unsigned char Data_Command);
void Display_16x2_Clear(void);
void Display_16x2_Return_Home(void);
void Display_16x2_Write_Text(char *Text_LCD);
void Display_16x2_Init(void);
void Display_16x2_All_Low(void);
void Display_16x2_Write_Text_Position(char *Text_LCD_Position,unsigned char Column, unsigned char Line);
void Display_16x2_Disable_Cursor(void);
void Display_16x2_Enable_Cursor(void);
unsigned char Display_16x2_Position(char Column, char Line);
void Display_16x2_Write_Number_Char(unsigned char Number);

#endif /* INC_STM32_TEST_BOARD_DISPLAY_16X2_H_ */
