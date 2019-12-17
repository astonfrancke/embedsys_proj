/**
 ******************************************************************************
 * @file           	: alt1_program.c
 * @brief          	: alt1_program.c.
 *                    This is the program for alternative 1.
 * @author			: Carl Aston Francke
 * @version			: 1.0
 * @date			: 12-December-2019
 ******************************************************************************
 */


#include "alt1_program.h"

void alt1_program(){

	/* init display and wait for time to be set via USB-terminal */
	lcd_init();
	set_time(usb_receive_time());

	while(1){
		lcd_set_pos(LINE1);
		lcd_write_string(get_time());
		set_display_backlight_brightness();
	}
}

