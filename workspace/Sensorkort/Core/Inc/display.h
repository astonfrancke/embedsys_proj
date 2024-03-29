/**
  ******************************************************************************
  * @file           : display.h
  * @brief          : Header for display.c file.
  *                   This file contains the common defines of the display functions.
  * @author			: Carl Aston Francke
  * @version		: 1.0
  * @date			: 28-November-2019
  ******************************************************************************
  */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_



#endif /* INC_DISPLAY_H_ */

#include "stdint.h"
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "adc.h"

#define NUM_OF_COLORS 2
#define TRANSMIT_BUFFERSIZE 3
#define LCD_HOME_L1	0x80
#define LINE1	0
#define LINE2	LINE1+0x20
#define LINE3	LINE1+0x40
#define	LINE4 	LINE1+0x60

void display_backlight(uint8_t color);
void set_display_backlight_brightness();
void lcd_init();
void lcd_write_string(char * string);
void lcd_write_char(char character);
void lcd_write_ins(uint8_t ins);
void lcd_write_data(uint8_t data);
void lcd_clr();
void lcd_set_pos(char pos);
