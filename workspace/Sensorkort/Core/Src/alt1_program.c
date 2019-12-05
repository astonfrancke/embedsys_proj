/*
 * alt1_program.c
 *
 *  Created on: Dec 5, 2019
 *      Author: elfra
 */

#include "alt1_program.h"

void alt1_program(){


	lcd_init();
	set_time(usb_receive_time());

	while(1){
		lcd_set_pos(LINE1);
		lcd_write_string(get_time());
		set_display_backlight_brightness();
	}
}
