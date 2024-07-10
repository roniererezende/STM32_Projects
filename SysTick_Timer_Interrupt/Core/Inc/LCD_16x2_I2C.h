/*
 * LCD_16x2_I2C.h
 *
 *  Created on: Jun 22, 2024
 *      Author: Roniere
 */

#ifndef INC_LCD_16X2_I2C_H_
#define INC_LCD_16X2_I2C_H_

#define I2C_INT_ADDR 0x27 // I2C address of the PCF8574
#define RS_BIT	        0 // Register select bit
#define EN_BIT          2 // Enable bit
#define BL_BIT			3 // Backlight bit
#define D4_BIT			4 // Data 4 bit
#define D5_BIT			5 // Data 5 bit
#define D6_BIT			6 // Data 6 bit
#define D7_BIT			7 // Data 7 bit

#define LCD_ROWS		2 // Numbers of rows on the LCD
#define LCD_COLS       16 // Numbers of columns on the LCD

void lcd_write_nibble(uint8_t nibble, uint8_t rs);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_init(void);
void lcd_write_character(char character);
void lcd_write_string(char *str);
void lcd_set_cursor(uint8_t row, uint8_t column);
void lcd_clear(void);
void lcd_return_home(void);
void lcd_cursor_permanent(void);
void lcd_cursor_intermittent(void);
void lcd_turn_on_no_cursor(void);
void lcd_write_string_shift_left(void);
void lcd_write_shift_left_cursor(void);
void lcd_write_string_shift_right(void);
void lcd_backlight(bool state);
void lcd_sweep_string(char *str, uint8_t row, uint8_t column, bool direction);

#endif /* INC_LCD_16X2_I2C_H_ */
