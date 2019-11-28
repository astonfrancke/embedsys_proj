/**
  ******************************************************************************
  * @file           : usb_com_test.c
  * @brief          : usb_com_test.c file.
  *                   This file tests the functions of the usb_com.c file.
  * @author			: Carl Aston Francke
  * @version		: 1.0
  * @date			: 28-November-2019
  ******************************************************************************
  */

#include "usb_com_test.h"

/**
 * *****************************************************************************
 * @brief 	Runs the USB test functions.
 * @return 	void
 * *****************************************************************************
 */
void usb_test_program(void)
{
	lcd_init();
	test_usb_transmit();
	test_usb_receive();
}


/**
 * *****************************************************************************
 * @brief 	Tests usb_transmit function in usb_com.c.
 * @return 	void
 * *****************************************************************************
 */
void test_usb_transmit(void)
{
	static uint8_t *tx_buffer = "Transmit test!";
	usb_transmit(tx_buffer, strlen(tx_buffer));
}

/**
 * *****************************************************************************
 * @brief 	Tests usb_receive function in usb_com.c.
 * @return 	void
 * *****************************************************************************
 */
void test_usb_receive(void)
{
	uint8_t *rx_buffer = usb_receive();
	lcd_set_pos(LINE1);
	lcd_write_string(rx_buffer);
}
