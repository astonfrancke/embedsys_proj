/**
 ******************************************************************************
 * @file           	: usb_com.c
 * @brief          	: usb_com.c file.
 *                    This file contains the functions to communicate via USB.
 * @author			: Carl Aston Francke
 * @version			: 1.0
 * @date			: 28-November-2019
 ******************************************************************************
 */

#include "usb_com.h"


/**
 * *****************************************************************************
 * @brief 	Transmits a string via USART(USB)
 * @param1	uint8_t *string, the string to transmit.
 * @param2	uint16_t data_size, size of data to be transmitted.
 * @return 	void
 * *****************************************************************************
 */
void usb_transmit(uint8_t *string, uint16_t data_size){
	HAL_UART_Transmit(&huart5, (uint8_t*)string, data_size, 5000);
}

/**
 * *****************************************************************************
 * @brief 	Receives data via USART(USB), Timeout set to 10000 ms
 * @return 	char *, The string that was received.
 * *****************************************************************************
 */
char * usb_receive(void){
	static uint8_t buffer[RCV_BUFFERSIZE];
	HAL_UART_Receive(&huart5, (uint8_t*)buffer, RCV_BUFFERSIZE, 10000);
	return buffer;
}