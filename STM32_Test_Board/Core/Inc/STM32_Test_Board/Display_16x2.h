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
// Milisecond function
#define DISPLAY_16x2_MS_DELAY(X)	(HAL_Delay(X))

// Commands List
#define DISPLAY_16x2_CLEAR				0x01
#define DISPLAY_16x2_RETURN_HOME		0x02
#define DISPLAY_16x2_ENTRY_MODE_RESET	0x04
#define DISPLAY_16x2_CONTROL			0x08
#define DISPLAY_16x2_CURSOR_SHIFT		0x10
#define DISPLAY_16x2_FUNCTION_SET		0x20			//CMD_FUNCTION_SET
#define DISPLAY_16x2_SET_CGRAM_ADDR		0x40
#define DISPLAY_16x2_SET_DDRAM_ADDR		0x80

// Commands Bitfields List
// 1 -> Entry Mode Bitfields
#define DISPLAY_16x2_ENTRY_SH			0x01
#define DISPLAY_16x2_ENTRY_ID			0x02

// 2 -> Entry Mode Bitfields
#define DISPLAY_16x2_ENTRY_SH			0x01
#define DISPLAY_16x2_ENTRY_ID			0x02

// 3 -> Display Control
#define DISPLAY_16x2_DISPLAY_B			0x01
#define DISPLAY_16x2_DISPLAY_C			0x02
#define DISPLAY_16x2_DISPLAY_D			0x04

// 4 -> Shift Control
#define DISPLAY_16x2_SHIFT_RL			0x04
#define DISPLAY_16x2_SHIFT_SC			0x08

// 5 -> Function Set Control
#define DISPLAY_16x2_FUNCTION_F			0x04
#define DISPLAY_16x2_FUNCTION_N			0x08
#define DISPLAY_16x2_FUNCTION_DL		0x10

#define 	T_CONST						  20

#define     TOTAL_CHARACTER 		      63
#define     TOTAL_PIXEL      		       8

/* DISPLAY STRUCTURE */
typedef struct s_Display_16x2
{
	bool Update;
	bool Is8BitsMode;
	GPIO_TypeDef* Port_RS_And_EN;  				// RS and E Port
	uint16_t Pin_RS, Pin_EN;						// RS and E pins
	GPIO_TypeDef* Port_LSB;						// LSBs D0, D1, D2, and D3 port
	uint16_t D0_Pin, D1_Pin, D2_Pin, D3_Pin;	// LSBs D0, D1, D2, and D3 pins
	GPIO_TypeDef* Port_MSB;					// MSBs D4, D5, D6, and D7 port
	uint16_t D4_Pin, D5_Pin, D6_Pin, D7_Pin;	// MSBs D4, D5, D6, and D7 pins
	uint8_t Control;
	uint8_t Function_Set;
	uint8_t Index;
}s_Display_16x2;

/* FUNCTION PROTOTYPE  */

//Floating point linker flag: -u _printf_float

void Display_16x2_Init(void);

/**
 * @brief Initialise LCD on 8-bits mode
 * @param[in] *port_rs_e RS and EN GPIO Port (e.g. GPIOB)
 * @param[in] *port_0_3 D0 to D3 GPIO Port
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void Display_16x2_Init_8_Bits(
    GPIO_TypeDef* Port_RS_EN, uint16_t RS_Pin, uint16_t EN_Pin,
    GPIO_TypeDef* Port_0_3, uint16_t D0_Pin, uint16_t D1_Pin, uint16_t D2_Pin, uint16_t D3_Pin,
    GPIO_TypeDef* Port_4_7, uint16_t D4_Pin, uint16_t D5_Pin, uint16_t D6_Pin, uint16_t D7_Pin);

/**
 * @brief Initialise LCD on 4-bits mode
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void Display_16x2_Init_4_Bits(
	GPIO_TypeDef* Port_RS_EN, uint16_t RS_Pin, uint16_t EN_Pin,
	GPIO_TypeDef* Port_4_7, uint16_t D4_Pin, uint16_t D5_Pin, uint16_t D6_Pin, uint16_t D7_Pin);

/**
 * @brief Set cursor position
 * @param[in] row - 0 or 1 for line1 or line2
 * @param[in] col - 0 - 15 (16 columns LCD)
 */
void Display_16x2_Set_Cursor(uint8_t Row, uint8_t Column);

/**
 * @brief Move to beginning of 1st line
 */
void Display_16x2_1st_Line(void);
/**
 * @brief Move to beginning of 2nd line
 */
void Display_16x2_2nd_Line(void);

/**
 * @brief Select LCD Number of lines mode
 */
void Display_16x2_Two_Lines(void);
void Display_16x2_One_Line(void);

/**
 * @brief Cursor ON/OFF
 */
void Display_16x2_Cursor_Show(bool State);

/**
 * @brief Display clear
 */
void  Display_16x2_Clear(void);

/**
 * @brief Display ON/OFF, to hide all characters, but not clear
 */
void  Display_16x2_On_Off(bool State);

/**
 * @brief Shift content to right
 */
void Display_16x2_Shift_Right(uint8_t Offset);

/**
 * @brief Shift content to left
 */
void Display_16x2_Shift_Left(uint8_t Offset);

/**
 * @brief Print to display any datatype (e.g. lcd16x2_printf("Value1 = %.1f", 123.45))
 */
void Display_16x2_Printf(const char* Str, ...);


void Display_16x2_Print_Integer_Number(unsigned char Number);

void Display_16x2_Print_Float_Number(float Number, uint8_t Row, uint8_t Column);

void Display_16x2_Creates_Custom_Character(unsigned char *Pattern, uint8_t Address);

void Display_16x2_Print_Character(char Character);



#endif /* INC_STM32_TEST_BOARD_DISPLAY_16X2_H_ */
