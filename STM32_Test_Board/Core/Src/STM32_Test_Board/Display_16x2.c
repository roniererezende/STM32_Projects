/*
 * Display_16x2.c
 *
 *  Created on: 30 de mar de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

unsigned char Display_16x2_Custom_Character_5x8[] = {
  0b00000,0b01110,0b01010,0b01110,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 1
  0b10000,0b01000,0b00100,0b00010,0b00001,0b00010,0b00100,0b01000, // Code for CGRAM memory space 2
  0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 3
  0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 4
  0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 5
  0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 6
  0b10000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000, // Code for CGRAM memory space 7
  0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b11111, // Code for CGRAM memory space 8
};

void Display_16x2_Init(void)
{
	STM32_Test_Board.Display_16x2.Is8BitsMode  = true;
	STM32_Test_Board.Display_16x2.Control	   = 0x0F;
	STM32_Test_Board.Display_16x2.Function_Set = 0x38;


	Display_16x2_Init_4_Bits(GPIOD, DISP_RS_Pin, DISP_EN_Pin, GPIOD, DISP_D4_Pin, DISP_D5_Pin, DISP_D6_Pin, DISP_D7_Pin);
	Display_16x2_Creates_Custom_Character(&Display_16x2_Custom_Character_5x8[0],0);
	Display_16x2_Cursor_Show(false);
	Display_16x2_Clear();
}

/**
 * @brief Enable Pulse function
 */
static void Display_16x2_Enable_Pulse(void)
{
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_RS_And_EN, STM32_Test_Board.Display_16x2.Pin_EN, GPIO_PIN_SET);
  //HAL_Delay(T_CONST);
  Delay_us(T_CONST);
  HAL_GPIO_WritePin(STM32_Test_Board.Display_16x2.Port_RS_And_EN, STM32_Test_Board.Display_16x2.Pin_EN, GPIO_PIN_RESET);
  Delay_us(60);
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
	STM32_Test_Board.Display_16x2.Pin_RS 		 = RS_Pin;
	STM32_Test_Board.Display_16x2.Pin_EN 		 = EN_Pin;
	STM32_Test_Board.Display_16x2.Port_LSB 	     = Port_0_3;
	STM32_Test_Board.Display_16x2.D0_Pin 		 = D0_Pin;
	STM32_Test_Board.Display_16x2.D1_Pin 		 = D1_Pin;
	STM32_Test_Board.Display_16x2.D2_Pin 		 = D2_Pin;
	STM32_Test_Board.Display_16x2.D3_Pin 		 = D3_Pin;
	STM32_Test_Board.Display_16x2.Port_MSB       = Port_4_7;
	STM32_Test_Board.Display_16x2.D4_Pin         = D4_Pin;
	STM32_Test_Board.Display_16x2.D5_Pin         = D5_Pin;
	STM32_Test_Board.Display_16x2.D6_Pin         = D6_Pin;
	STM32_Test_Board.Display_16x2.D7_Pin         = D7_Pin;
	STM32_Test_Board.Display_16x2.Is8BitsMode    = true;
	STM32_Test_Board.Display_16x2.Function_Set   = 0x38;

	//Initializes LCD
	//1. Wait at least 15ms
	Delay_ms(20);
	//2. Attentions sequence
	Display_16x2_Write_Command(0x30);
	Delay_ms(5);
	Display_16x2_Write_Command(0x30);
	Delay_ms(1);
	Display_16x2_Write_Command(0x30);
	Delay_ms(1);
	//3. Function set; Enable 2 lines, Data length to 8 bits
	Display_16x2_Write_Command(DISPLAY_16x2_FUNCTION_SET | DISPLAY_16x2_FUNCTION_N | DISPLAY_16x2_FUNCTION_DL);
	//4. Display control (Display ON, Cursor ON, blink cursor)
	Display_16x2_Write_Command(DISPLAY_16x2_CONTROL | DISPLAY_16x2_DISPLAY_B | DISPLAY_16x2_DISPLAY_C | DISPLAY_16x2_DISPLAY_D);
	//5. Clear LCD and return home
	Delay_ms(2);
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
	STM32_Test_Board.Display_16x2.Pin_RS 		 = RS_Pin;
	STM32_Test_Board.Display_16x2.Pin_EN 	     = EN_Pin;
	STM32_Test_Board.Display_16x2.Port_MSB       = Port_4_7;
	STM32_Test_Board.Display_16x2.D4_Pin         = D4_Pin;
	STM32_Test_Board.Display_16x2.D5_Pin         = D5_Pin;
	STM32_Test_Board.Display_16x2.D6_Pin         = D6_Pin;
	STM32_Test_Board.Display_16x2.D7_Pin         = D7_Pin;
	STM32_Test_Board.Display_16x2.Is8BitsMode    = false;
	STM32_Test_Board.Display_16x2.Function_Set   = 0x28;

	//Initialise LCD
	//1. Wait at least 15ms
	Delay_ms(20);
	//2. Attentions sequence
	Display_16x2_Write_4_Bits(0x3);
	Delay_ms(5);
	Display_16x2_Write_4_Bits(0x3);
	Delay_ms(1);
	Display_16x2_Write_4_Bits(0x3);
	Delay_ms(1);
	Display_16x2_Write_4_Bits(0x2);
	Delay_ms(1);
	//4. Function set; Enable 2 lines, Data length to 4 bits
	Display_16x2_Write_Command(DISPLAY_16x2_FUNCTION_SET | DISPLAY_16x2_FUNCTION_N);
	//3. Display control (Display ON, Cursor ON, blink cursor)
	Display_16x2_Write_Command(DISPLAY_16x2_CONTROL | DISPLAY_16x2_DISPLAY_B | DISPLAY_16x2_DISPLAY_C | DISPLAY_16x2_DISPLAY_D);
	//4. Clear LCD and return home
	Display_16x2_Write_Command(DISPLAY_16x2_CLEAR);
	Delay_ms(3);
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
  Delay_ms(3);
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

void Display_16x2_Print_Character(char Character)
{
	Display_16x2_Write_Data(Character);
}
/**
 * @brief Print to display any datatype (e.g. lcd16x2_printf("Value1 = %.1f", 123.45))
 */
void Display_16x2_Printf(const char* Str, ...)
{
	//HAL_ADC_Stop_DMA(&hadc1);
	char String_Array[20];
	va_list Args;
	va_start(Args, Str);
	vsprintf(String_Array, Str, Args);
	va_end(Args);

	for(uint8_t Index = 0;  Index < strlen(String_Array) && Index < 16; Index++)
	{
		Display_16x2_Write_Data((uint8_t)String_Array[Index]);
	}

	//HAL_ADC_Start_DMA(&hadc1, &STM32_Test_Board.ADC_Peripheral.LM35.Sampled_Value, NUMBER_MONITORING_CHANNEL);
}

void Display_16x2_Print_Integer_Number(unsigned char Number)
{
	char String[4];

	sprintf(String, "%d", Number);
	Display_16x2_Printf(String);
	return;
}

void Display_16x2_Print_Float_Number(float Number, uint8_t Row, uint8_t Column)
{
	uint16_t Millivolt = Number * 1000;
	uint8_t Unit       = 0;
	uint8_t Hundreth   = 0;
	uint8_t Tenth      = 0;

	if(Number >= 1.0)
	{
		Unit = Millivolt / 1000;
		Hundreth = (Millivolt % 1000) / 100;
		Tenth = ((Millivolt % 1000) % 100) / 10;
	}
	else
	{
		Unit = 0;
		Hundreth = (Millivolt % 1000) / 100;
		Tenth = ((Millivolt % 1000) % 100) / 10;
	}

	Display_16x2_Set_Cursor(Row,Column);
	Display_16x2_Print_Integer_Number(Unit);
	Display_16x2_Set_Cursor(Row,Column + 1);
	Display_16x2_Print_Character('.');
	Display_16x2_Set_Cursor(Row,Column + 2);
	Display_16x2_Print_Integer_Number(Hundreth);
	Display_16x2_Set_Cursor(Row,Column + 3);
	Display_16x2_Print_Integer_Number(Tenth);


}

void Display_16x2_Creates_Custom_Character(unsigned char *Pattern, uint8_t Address)
{
	STM32_Test_Board.Display_16x2.Index = 0;

	Display_16x2_Write_Command(0x40 + (Address * 8));

	for(STM32_Test_Board.Display_16x2.Index = 0; STM32_Test_Board.Display_16x2.Index < TOTAL_PIXEL; STM32_Test_Board.Display_16x2.Index++)
	{
		Display_16x2_Write_Data(Pattern[STM32_Test_Board.Display_16x2.Index]);
	}
}
