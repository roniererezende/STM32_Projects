/*
 * Display_16x2.c
 *
 *  Created on: 30 de mar de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void Display_16x2_Variable_Init(void)
{
	STM32_Test_Board.Display_16x2.Is8BitsMode  = true;
	STM32_Test_Board.Display_16x2.Control	   = 0x0F;
	STM32_Test_Board.Display_16x2.Function_Set = 0x38;
}

/* private functions prototypes */
/**
 * @brief DWT Cortex Tick counter for Microsecond delay
 */
//static uint32_t Display_16x2_DWT_Delay_Init(void)
//{
	/* Disable TRC */
	//CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
	/* Enable TRC */
	//CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	/* Disable clock cycle counter */
	//DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
	/* Enable clock cycle counter */
	//DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	/* Reset the clock cycle counter value */
	//DWT->CYCCNT = 0;
	/* 3 NO OPERATION instructions */
//	__NOP();
//	__NOP();
//	__NOP();
	/* Check if clock cycle counter has started */
	//if(DWT->CYCCNT)
	//{
	//return 0;
	//}
	//else
	//{
//	return 1;
	//}
//}

/**
 * @brief Enable Pulse function
 */
static void Display_16x2_Enable_Pulse(void)
{
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_RS_And_EN, STM32_Test_Board.Display_16x2.Pin_EN, GPIO_PIN_SET);
  HAL_Delay(T_CONST);
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_RS_And_EN, STM32_Test_Board.Display_16x2.Pin_EN, GPIO_PIN_RESET);
  HAL_Delay(60);
}

/**
 * @brief RS control
 */
static void Display_16x2_RS(bool State)
{
	HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_RS_And_EN, STM32_Test_Board.Display_16x2.Pin_RS,(GPIO_PinState)State);
}

/**
 * @brief Write parallel signal to lcd
 */
static void Display_16x2_Write(uint8_t WByte)
{
	uint8_t LSB_Nibble = WByte & 0xF, MSB_Nibble = (WByte >> 4) & 0xF;

	if(STM32_Test_Board.Display_16x2.Is8BitsMode)
	{
		// LSB data
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_LSB, STM32_Test_Board.Display_16x2.D0_Pin,(GPIO_PinState)(LSB_Nibble & 0x1));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_LSB, STM32_Test_Board.Display_16x2.D1_Pin,(GPIO_PinState)(LSB_Nibble & 0x2));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_LSB, STM32_Test_Board.Display_16x2.D2_Pin,(GPIO_PinState)(LSB_Nibble & 0x4));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_LSB, STM32_Test_Board.Display_16x2.D3_Pin,(GPIO_PinState)(LSB_Nibble & 0x8));
		// MSB data
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D4_Pin,(GPIO_PinState)(MSB_Nibble & 0x1));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D5_Pin,(GPIO_PinState)(MSB_Nibble & 0x2));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D6_Pin,(GPIO_PinState)(MSB_Nibble & 0x4));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D7_Pin,(GPIO_PinState)(MSB_Nibble & 0x8));

		Display_16x2_Enable_Pulse();
	}
	else
	{
		// MSB data
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D4_Pin,(GPIO_PinState)(MSB_Nibble & 0x1));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D5_Pin,(GPIO_PinState)(MSB_Nibble & 0x2));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D6_Pin,(GPIO_PinState)(MSB_Nibble & 0x4));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D7_Pin,(GPIO_PinState)(MSB_Nibble & 0x8));
		Display_16x2_Enable_Pulse();
		// LSB data
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D4_Pin,(GPIO_PinState)(LSB_Nibble & 0x1));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D5_Pin,(GPIO_PinState)(LSB_Nibble & 0x2));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D6_Pin,(GPIO_PinState)(LSB_Nibble & 0x4));
		HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D7_Pin,(GPIO_PinState)(LSB_Nibble & 0x8));
		Display_16x2_Enable_Pulse();
	}
}

/**
 * @brief Write command
 */
static void Display_16x2_Write_Command(uint8_t Command)
{
	Display_16x2_RS(false);
	Display_16x2_Write(Command);
}

/**
 * @brief Write data
 */
static void Display_16x2_Write_Data(uint8_t Data)
{
	Display_16x2_RS(true);
	Display_16x2_Write(Data);
}

/**
 * @brief 4-bits write
 */
static void Display_16x2_Write_4_Bits(uint8_t Nibble)
{
  Nibble &= 0xF;
  Display_16x2_RS(false);
  //LSB data
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D4_Pin, (GPIO_PinState)(Nibble&0x1));
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D5_Pin, (GPIO_PinState)(Nibble&0x2));
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D6_Pin, (GPIO_PinState)(Nibble&0x4));
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_MSB, STM32_Test_Board.Display_16x2.D7_Pin, (GPIO_PinState)(Nibble&0x8));
  Display_16x2_Enable_Pulse();
}

/* Public functions definitions */

/**
 * @brief Initialise LCD on 8-bits mode
 * @param[in] *port_rs_e RS and EN GPIO Port (e.g. GPIOB)
 * @param[in] *port_0_3 D0 to D3 GPIO Port
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void Display_16x2_Init_8_bits(
    GPIO_TypeDef* Port_RS_EN, uint16_t RS_Pin, uint16_t EN_Pin,
    GPIO_TypeDef* Port_0_3, uint16_t D0_Pin, uint16_t D1_Pin, uint16_t D2_Pin, uint16_t D3_Pin,
    GPIO_TypeDef* Port_4_7, uint16_t D4_Pin, uint16_t D5_Pin, uint16_t D6_Pin, uint16_t D7_Pin)
{
	//DWT_Delay_Init();
	//Set GPIO Ports and Pins data
	STM32_Test_Board.Display_16x2.Port_RS_And_EN = Port_RS_EN;
	STM32_Test_Board.Display_16x2.Pin_RS 		   = RS_Pin;
	STM32_Test_Board.Display_16x2.Pin_EN 		   = EN_Pin;
	STM32_Test_Board.Display_16x2.Port_LSB 	   = Port_0_3;
	STM32_Test_Board.Display_16x2.D0_Pin 		   = D0_Pin;
	STM32_Test_Board.Display_16x2.D1_Pin 		   = D1_Pin;
	STM32_Test_Board.Display_16x2.D2_Pin 		   = D2_Pin;
	STM32_Test_Board.Display_16x2.D3_Pin 		   = D3_Pin;
	STM32_Test_Board.Display_16x2.Port_MSB       = Port_4_7;
	STM32_Test_Board.Display_16x2.D4_Pin         = D4_Pin;
	STM32_Test_Board.Display_16x2.D5_Pin         = D5_Pin;
	STM32_Test_Board.Display_16x2.D6_Pin         = D6_Pin;
	STM32_Test_Board.Display_16x2.D7_Pin         = D7_Pin;
	STM32_Test_Board.Display_16x2.Is8BitsMode    = true;
	STM32_Test_Board.Display_16x2.Function_Set   = 0x38;

	//Initializes LCD
	//1. Wait at least 15ms
	HAL_Delay(20);
	//2. Attentions sequence
	Display_16x2_Write_Command(0x30);
	HAL_Delay(5);
	Display_16x2_Write_Command(0x30);
	HAL_Delay(1);
	Display_16x2_Write_Command(0x30);
	HAL_Delay(1);
	//3. Function set; Enable 2 lines, Data length to 8 bits
	Display_16x2_Write_Command(DISPLAY_16x2_FUNCTION_SET | DISPLAY_16x2_FUNCTION_N | DISPLAY_16x2_FUNCTION_DL);
	//4. Display control (Display ON, Cursor ON, blink cursor)
	Display_16x2_Write_Command(DISPLAY_16x2_CONTROL | DISPLAY_16x2_DISPLAY_B | DISPLAY_16x2_DISPLAY_C | DISPLAY_16x2_DISPLAY_D);
	//5. Clear LCD and return home
	Display_16x2_Write_Command(DISPLAY_16x2_CLEAR);
	HAL_Delay(2);
}

/**
 * @brief Initialise LCD on 4-bits mode
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void Display_16x2_Init_4_Bits(
	GPIO_TypeDef* Port_RS_EN, uint16_t RS_Pin, uint16_t EN_Pin,
	GPIO_TypeDef* Port_4_7, uint16_t D4_Pin, uint16_t D5_Pin, uint16_t D6_Pin, uint16_t D7_Pin)
{
	//DWT_Delay_Init();
	//Set GPIO Ports and Pins data
	STM32_Test_Board.Display_16x2.Port_RS_And_EN = Port_RS_EN;
	STM32_Test_Board.Display_16x2.Pin_RS 		   = RS_Pin;
	STM32_Test_Board.Display_16x2.Pin_EN 		   = EN_Pin;
	STM32_Test_Board.Display_16x2.Port_MSB       = Port_4_7;
	STM32_Test_Board.Display_16x2.D4_Pin         = D4_Pin;
	STM32_Test_Board.Display_16x2.D5_Pin         = D5_Pin;
	STM32_Test_Board.Display_16x2.D6_Pin         = D6_Pin;
	STM32_Test_Board.Display_16x2.D7_Pin         = D7_Pin;
	STM32_Test_Board.Display_16x2.Is8BitsMode    = false;
	STM32_Test_Board.Display_16x2.Function_Set   = 0x28;

	//Initialise LCD
	//1. Wait at least 15ms
	HAL_Delay(20);
	//2. Attentions sequence
	Display_16x2_Write_4_Bits(0x3);
	HAL_Delay(5);
	Display_16x2_Write_4_Bits(0x3);
	HAL_Delay(1);
	Display_16x2_Write_4_Bits(0x3);
	HAL_Delay(1);
	Display_16x2_Write_4_Bits(0x2);
	HAL_Delay(1);
	//4. Function set; Enable 2 lines, Data length to 4 bits
	Display_16x2_Write_Command(DISPLAY_16x2_FUNCTION_SET | DISPLAY_16x2_FUNCTION_N);
	//3. Display control (Display ON, Cursor ON, blink cursor)
	Display_16x2_Write_Command(DISPLAY_16x2_CONTROL | DISPLAY_16x2_DISPLAY_B | DISPLAY_16x2_DISPLAY_C | DISPLAY_16x2_DISPLAY_D);
	//4. Clear LCD and return home
	Display_16x2_Write_Command(DISPLAY_16x2_CLEAR);
	HAL_Delay(3);
}

/**
 * @brief Set cursor position
 * @param[in] row - 0 or 1 for line1 or line2
 * @param[in] col - 0 - 15 (16 columns LCD)
 */
void Display_16x2_Set_Cursor(uint8_t Row, uint8_t Column)
{
	uint8_t Mask_Data;
	Mask_Data = (Column)&0x0F;
	if(Row==0)
	{
		Mask_Data |= (0x80);
		Display_16x2_Write_Command(Mask_Data);
	}
	else
	{
		Mask_Data |= (0xc0);
		Display_16x2_Write_Command(Mask_Data);
	}
}

/**
 * @brief Move to beginning of 1st line
 */
void Display_16x2_1st_Line(void)
{
	Display_16x2_Set_Cursor(0,0);
}

/**
 * @brief Move to beginning of 2nd line
 */
void Display_16x2_2nd_Line(void)
{
	Display_16x2_Set_Cursor(1,0);
}

/**
 * @brief Select LCD Number of lines mode
 */
void Display_16x2_Two_Lines(void)
{
	STM32_Test_Board.Display_16x2.Function_Set |= (0x08);
	Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Function_Set);
}
void lcd16x2_oneLine(void)
{
	STM32_Test_Board.Display_16x2.Function_Set &= ~(0x08);
	Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Function_Set);
}

/**
 * @brief Cursor ON/OFF
 */
void Display_16x2_Cursor_Show(bool State)
{
  if(State)
  {
	  STM32_Test_Board.Display_16x2.Control |= (0x03);
	  Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Control);
  }
  else
  {
	  STM32_Test_Board.Display_16x2.Control &= ~(0x03);
	  Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Control);
  }
}

/**
 * @brief Display clear
 */
void Display_16x2_Clear(void)
{
  Display_16x2_Write_Command(DISPLAY_16x2_CLEAR);
  HAL_Delay(3);
}

/**
 * @brief Display ON/OFF, to hide all characters, but not clear
 */
void Display_16x2_On_Off(bool State)
{
	if(State)
	{
		STM32_Test_Board.Display_16x2.Control |= (0x04);
		Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Control);
	}
	else
	{
		STM32_Test_Board.Display_16x2.Control &= ~(0x04);
		Display_16x2_Write_Command(STM32_Test_Board.Display_16x2.Control);
	}
}

/**
 * @brief Shift content to right
 */
void Display_16x2_Shift_Right(uint8_t Offset)
{
	for(uint8_t Index = 0; Index < Offset; Index++)
	{
		Display_16x2_Write_Command(0x1c);
	}
}

/**
 * @brief Shift content to left
 */
void Display_16x2_Shift_Left(uint8_t Offset)
{
	for(uint8_t Index = 0; Index < Offset; Index++)
	{
		Display_16x2_Write_Command(0x18);
	}
}

/**
 * @brief Print to display any datatype (e.g. lcd16x2_printf("Value1 = %.1f", 123.45))
 */
void Display_16x2_Printf(const char* Str, ...)
{
  char String_Array[20];
  va_list Args;
  va_start(Args, Str);
  vsprintf(String_Array, Str, Args);
  va_end(Args);

  for(uint8_t Index = 0;  Index < strlen(String_Array) && Index < 16; Index++)
  {
    Display_16x2_Write_Data((uint8_t)String_Array[Index]);
  }
}

/****************************************************************/
/* 				FUN��O PARA INICIAR DISPLAY 16x2				*/
/****************************************************************/
void Display_16x2_Init(void)
{
	HAL_Delay(200);

	Display_16x2_Clear();

	ENB_LOW;
	RS_CMD;

//	Display_16x2_Send_Command(CMD_FUNCTION_SET);
//	HAL_Delay(10);

//	Display_16x2_Send_Command(CMD_FUNCTION_SET);
//	HAL_Delay(10);

//	Display_16x2_Send_Command(CMD_FUNCTION_SET_16x2);
//	HAL_Delay(10);

//	Display_16x2_Send_Command(CMD_FUNCTION_SET_16x2);
//	HAL_Delay(10);

//	Display_16x2_Clear();

//	Display_16x2_Send_Command(CMD_DISPLAY_CONTROL);
//	HAL_Delay(10);

	Display_16x2_Send_Command(0x38);
	HAL_Delay(10);

	Display_16x2_Send_Command(0x06);
	HAL_Delay(10);

	Display_16x2_Send_Command(0x0C);
	HAL_Delay(10);

	Display_16x2_Send_Command(0x01);
	HAL_Delay(2);

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

	HAL_Delay(10);
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
//void Display_16x2_Clear(void)
//{
//	Display_16x2_Send_Command(CMD_CLEAR_DISPLAY);
//	HAL_Delay(4);
//	return;
//}

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
