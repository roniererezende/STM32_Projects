/*
 * LCD_16x2_I2C.c
 *
 *  Created on: Jun 22, 2024
 *      Author: Roniere Rezende
 */
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

bool backlight_state = true;

/*************************************************************************************************
 *  Function: void lcd_write_nibble(uint8_t nibble, uint8_t rs)
 *  Description: Sends 4-b nibble of data to the LCD display through the PCF8574 I2C I/O expander.
 *  Parameters: nibble, rs
 *  Return: no return
 ************************************************************************************************/
void lcd_write_nibble(uint8_t nibble, uint8_t rs)
{
	uint8_t data = nibble << D4_BIT;

	data |= rs << RS_BIT;
	data |= backlight_state << BL_BIT;
	data |= 1 << EN_BIT;
	HAL_I2C_Master_Transmit(&hi2c1, I2C_INT_ADDR << 1, &data, 1, 100);
	HAL_Delay(1);
	data &= ~(1 << EN_BIT);
	HAL_I2C_Master_Transmit(&hi2c1, I2C_INT_ADDR << 1, &data, 1, 100);
}

/************************************************************************************************
 *  Function: void lcd_send_cmd(uint8_t cmd)
 *  Description: Sends a command to the LCD display thought the PCF8574 I2C I/O expander.
 *  Parameters: cmd
 *  Return: no return
 ***********************************************************************************************/
void lcd_send_cmd(uint8_t cmd)
{
	uint8_t upper_nibble = cmd >> 4;
	uint8_t lower_nibble = cmd & 0x0F;
	lcd_write_nibble(upper_nibble, 0);
	lcd_write_nibble(lower_nibble, 0);
	if(cmd == 0x01 || cmd == 0x02)
	{
		HAL_Delay(2);
	}

}

/************************************************************************************************
 *  Function: void lcd_send_data(uint8_t data)
 *  Description: Sends data to the LCD display through the PCF8574 I2C I/O expander.
 *  Parameters: data
 *  Return: no return
 ***********************************************************************************************/
void lcd_send_data(uint8_t data)
{
	uint8_t upper_nibble = data >> 4;
	uint8_t lower_nibble = data & 0x0F;
	lcd_write_nibble(upper_nibble, 1);
	lcd_write_nibble(lower_nibble, 1);
}

/************************************************************************************************
 *  Function: void lcd_init(void)
 *  Description: Initializes the LCD display.
 *  Parameters: no parameters
 *  Return: no return
 ***********************************************************************************************/
void lcd_init(void)
{
	HAL_Delay(50);
	lcd_write_nibble(0x03, 0);
	HAL_Delay(5);
	lcd_write_nibble(0x03, 0);
	HAL_Delay(1);
	lcd_write_nibble(0x03, 0);
	HAL_Delay(1);
	lcd_write_nibble(0x02, 0);
	lcd_send_cmd(0x28);
	lcd_send_cmd(0x0C);
	lcd_send_cmd(0x06);
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_write_character(char character)
 *  Description: Writes a null-terminated string to the LCD display through the PCF8574 I2C I/O
 *  			 expander.
 *  Parameters: character
 *  Return: no return
 ***********************************************************************************************/
void lcd_write_character(char character)
{
	lcd_send_data(character);
}

/************************************************************************************************
 *  Function: void lcd_write_string(char *str)
 *  Description: Writes a null-terminated string to the LCD display through the PCF8574 I2C I/O
 *  			 expander.
 *  Parameters: str
 *  Return: no return
 ***********************************************************************************************/
void lcd_write_string(char *str)
{
	while(*str)
	{
		lcd_send_data(*str++);
	}
}

/************************************************************************************************
 *  Function: void lcd_set_cursor(uint8_t row, uint8_t column)
 *  Description: Sets the cursor position on the LCD display.
 *  Parameters: row, column
 *  Return: no return
 ***********************************************************************************************/
void lcd_set_cursor(uint8_t row, uint8_t column)
{
	uint8_t address;
	switch(row)
	{
		case 0:
			address = 0x00;
			break;

		case 1:
			address = 0x40;
			break;

		default:
			address = 0x00;
	}
	address += column;
	lcd_send_cmd(0x80 | address);
}

/************************************************************************************************
 *  Function: void lcd_clear(void)
 *  Description: Clears the display of the LCD.
 *  Parameters: nibble, rs
 *  Return: no return
 ***********************************************************************************************/
void lcd_clear(void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_return_home(void)
 *  Description: Positions cursor in row 0 and column 0.
 *  Parameters: no parameters
 *  Return: no return
 ***********************************************************************************************/
void lcd_return_home(void)
{
	lcd_send_cmd(0x02);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_cursor_permanent(void)
 *  Description: Display turn on with permanent cursor.
 *  Parameters: no parameters
 *  Return: no return
 ***********************************************************************************************/
void lcd_cursor_permanent(void)
{
	lcd_send_cmd(0x0E);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_cursor_intermittent(void)
 *  Description: Display turn on with intermittent cursor.
 *  Parameters: no parameters
 *  Return: no return
 ***********************************************************************************************/
void lcd_cursor_intermittent(void)
{
	lcd_send_cmd(0x0F);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_turn_on_no_cursor(void)
 *  Description: Display turn on without cursor.
 *  Parameters: no parameters
 *  Return: no return
 ***********************************************************************************************/
void lcd_turn_on_no_cursor(void)
{
	lcd_send_cmd(0x0C);
	HAL_Delay(2);
}

/************************************************************************************************
 *  Function: void lcd_backlight(bool state)
 *  Description: Turns the backlight of the LCD on or off
 *  Parameters: state
 *  Return: no return
 ***********************************************************************************************/
void lcd_backlight(bool state)
{
	if(state)
	{
		backlight_state = true;
	}
	else
	{
		backlight_state = false;
	}
}

/************************************************************************************************
 *  Function: void lcd_sweep_string(char *str, uint8_t row_init, uint8_t column_init, bool direction)
 *  Description: Sweeps string from left to right direction or from right to left direction
 *  Parameters: str, row_init, column_init, direction
 *  Return: no return
 ***********************************************************************************************/
void lcd_sweep_string(char *str, uint8_t row_init, uint8_t column_init, bool direction)
{
	//static uint8_t pos_col = 0;
	uint8_t index = 0;
	char string_cpy_left[20];
	char string_cpy_right[20];
	static bool init_string_left = false;
	static bool init_string_right = false;;
	static char string_right[20] = {'\0'};
	static char string_left[20]  = {'\0'};

	// Initializes string to be printed
	if(init_string_left == false && direction == false)
	{
		for(index = 0; index <= 15; index++)
		{
			if(index < column_init)
			{
				string_left[index] = 32;
			}
			else
			{
				if(*str != '\0')
				{
					string_left[index] = *str++;
				}
				else
				{
					string_left[index] = 32;
				}
			}
		}
		init_string_left = true;
	}

	if(init_string_right == false && direction == true)
	{
		for(index = 0; index <= 15; index++)
		{
			if(index < column_init)
			{
				string_right[index] = 32;
			}
			else
			{
				if(*str != '\0')
				{
					string_right[index] = *str++;
				}
				else
				{
					string_right[index] = 32;
				}
			}
		}
		init_string_right = true;
	}

	if(direction == false)
	{
		strcpy(string_cpy_left, string_left);
		lcd_set_cursor(row_init, 0);
		lcd_write_string(string_left);

		for(index = 15; index > 0; index--)
		{
			if(string_cpy_left[0] != 32)
			{
				string_left[15] = string_cpy_left[0];
			}
			else if(string_cpy_left[0] == 32)
			{
				string_left[15] = 32;
			}
			string_left[index-1] = string_cpy_left[index];
		}
	}
	else
	{
		strcpy(string_cpy_right, string_right);
		lcd_set_cursor(row_init, 0);
		lcd_write_string(string_right);

		for(index = 0; index < 15; index++)
		{
			if(string_cpy_right[15] != 32)       // 32 -> ASCII for ''(blank space)
			{
				string_right[0] = string_cpy_right[15];
			}
			else if(string_cpy_right[15] == 32)  // 32 -> ASCII for ''(blank space)
			{
				string_right[0] = 32;  		   // 32 -> ASCII for ''(blank space)
			}

			string_right[index+1] = string_cpy_right[index];
		}
	}
}
