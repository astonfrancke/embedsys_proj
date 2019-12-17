/**
  ******************************************************************************
  * @file           : usb_com.h
  * @brief          : Header for usb_com.c file.
  *                   This file contains the common defines of the usb communication functions.
  * @author			: Carl Aston Francke
  * @version		: 1.0
  * @date			: 28-November-2019
  ******************************************************************************
  */

#ifndef INC_USB_COM_H_
#define INC_USB_COM_H_



#endif /* INC_USB_COM_H_ */

#define RCV_BUFFERSIZE 10

#include "usart.h"
#include "stdint.h"
#include "string.h"

void usb_transmit(uint8_t * string, uint16_t data_size);
char * usb_receive(void);
uint8_t * usb_receive_time(void);
