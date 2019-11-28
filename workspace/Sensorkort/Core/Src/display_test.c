/**
  ******************************************************************************
  * @file           : test_display.c
  * @brief          : test.c file.
  *                   This file tests the functions of the display.c file.
  * @author			: Carl Aston Francke
  * @version		: 1.0
  * @date			: 27-November-2019
  ******************************************************************************
  */

#include "display_test.h"

/**
 * *****************************************************************************
 * @brief 	Runs the test functions.
 * @return 	void
 * *****************************************************************************
 */
void display_test_program(void)
{
	test_backlight();
	test_lcd_init();
	test_lcd_write();
}


/**
 * *****************************************************************************
 * @brief 	Tests the display_backlight function in display.c.
 * 			Parameter for lcd_backlight is defined as: 0 = RED, 1 = GREEN, 2 = WHITE.
 * @return 	void
 * *****************************************************************************
 */
void test_backlight(void)
{
	display_backlight(0);
	HAL_Delay(500);
	display_backlight(1);
	HAL_Delay(500);
	display_backlight(2);
	HAL_Delay(500);
}

/**
 * *****************************************************************************
 * @brief 	Tests the lcd_init function in display.c.
 * @return 	void
 * *****************************************************************************
 */
void test_lcd_init(void){
	lcd_init();
}

/**
 * *****************************************************************************
 * @brief 	tests the lcd_write_string and lcd_write_char function in display.c.
 * 			Should write the string StringTest on line one and the char T on line 2.
 * @return 	void
 * *****************************************************************************
 */
void test_lcd_write(void){
	lcd_set_pos(LINE1);
	uint8_t test_buffer1[] = "StringTest";
	lcd_write_string(test_buffer1);

	lcd_set_pos(LINE2);
	lcd_write_char('T');
}