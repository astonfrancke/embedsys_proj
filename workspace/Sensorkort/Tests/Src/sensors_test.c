/*
 * sensors_test.c
 *
 *  Created on: 6 dec. 2019
 *      Author: elfra
 */


#include "../Inc/sensors_test.h"

#include "sensors.h"
#include "display.h"


void sensors_test_program(void) {
	lcd_init();
	test_get_humi_temp();
}


void test_get_humi_temp(void) {
	init_hts();
	get_hts_cali();
	while(1) {
		lcd_set_pos(LINE2);
		lcd_write_string(get_humi_temp());
		HAL_Delay(500);
	}
}
