/**
  ******************************************************************************
  * @file           : test_rtc.c
  * @brief          : test_rtc.c file.
  *                   This file tests the functions of the rtc.c file.
  * @author			: Carl Aston Francke
  * @version		: 1.0
  * @date			: 28-November-2019
  ******************************************************************************
  */


#include "rtc_test.h"


/**
 * *****************************************************************************
 * @brief 	Runs the test functions.
 * @return 	void
 * *****************************************************************************
 */
void rtc_test_program(){
	test_set_time();
	while(1){
	HAL_Delay(1000);
	test_get_time();
	}
}

/**
 * *****************************************************************************
 * @brief 	Tests the set_time function in rtc.c.
 * @return 	void
 * *****************************************************************************
 */
void test_set_time(){
	static uint8_t date_time[] = { 0x13, 0x0B, 0x05, 0x1D, 0x0A, 0x00, 0x00 };
	set_time(date_time);
	lcd_init();
}


/**
 * *****************************************************************************
 * @brief 	Tests the get_time function in rtc.c.
 * @return 	void
 * *****************************************************************************
 */
void test_get_time(){
	lcd_clr();
	lcd_set_pos(LINE1);
	lcd_write_string(get_time());
}
