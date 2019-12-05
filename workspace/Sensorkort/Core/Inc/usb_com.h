/*
 * usb_com.h
 *
 *  Created on: 28 nov. 2019
 *      Author: elfra
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
