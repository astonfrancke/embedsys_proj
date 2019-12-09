/*
 * hts.c
 *
 *  Created on: 6 dec. 2019
 *      Author: elfra
 */


#include "sensors.h"
#include "i2c.h"
#include "string.h"
#include "stdio.h"


typedef struct HTS221 {
	uint8_t DevAddr;

	uint8_t HumReg;
	uint8_t TempReg;

	/* Calibration registers */
	uint8_t H0_rH;
	uint8_t H1_rH;
	uint8_t T0_degC;
	uint8_t T1_degC;
	uint8_t T1T0Msb;
	uint8_t H0_T0_Out; // Auto-increment bit set
	uint8_t H1_T0_Out; // Auto-increment bit set
	uint8_t T0_OUT;	// Auto-increment bit set
	uint8_t T1_OUT;	// Auto-increment bit set

	uint16_t H0;
	uint16_t H1;
	uint16_t H2;
	uint16_t H3;

	uint16_t T0;
	uint16_t T1;
	uint16_t T2;
	uint16_t T3;
} HTS221 ;


HTS221 hts221;

char * get_humi_temp(){
	static char str[10];
	static char reg[1];
	static char data[4];
	HAL_StatusTypeDef ret;

	static int hum;
	static int temp;

	reg[0] = hts221.HumReg;

	ret = HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		strcpy((char*)str, "ERT HuTe");
	} else {

		ret = HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);
		if (ret != HAL_OK) {
			strcpy((char*)str, "ERR HuTe");
		} else {

			hum = (data[1] * 256) + data[0];
		}
	}

	reg[0] = hts221.TempReg;

	ret = HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		strcpy((char*)str, "ERT HuTe");
	} else {

		ret = HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);
		if (ret != HAL_OK) {
			strcpy((char*)str, "ERR HuTe");
		} else {

			temp = (data[1] * 256) + data[0];
			if(temp > 32767)
			{
				temp -= 65536;
			}
		}
	}

	float hum_c = ((1.0 * hts221.H1) - (1.0 * hts221.H0)) * (1.0 * hum - 1.0 * hts221.H2) / (1.0 * hts221.H3 - 1.0 * hts221.H2) + (1.0 * hts221.H0);
	float temp_c = ((hts221.T1 - hts221.T0) / 8.0) * (temp - hts221.T2) / (hts221.T3 - hts221.T2) + (hts221.T0 / 8.0);


	sprintf((char*)str, "T%02u H%02u", (unsigned int) temp_c, (unsigned int) hum_c);

	return str;
}

void get_hts_cali() {
	/* Calibrate humidity */
	static char reg[1];
	static char data[4];

	// Read H0_rH_x2 reg
	reg[0] = hts221.H0_rH;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	char data_0 = data[0];

	// Read H1_rH_x2 reg
	reg[0] = hts221.H1_rH;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 1, HAL_MAX_DELAY);
	char data_1 = data[0];

	hts221.H0 = data_0 / 2;
	hts221.H1 = data_1 / 2;

	// Read H0_T0_OUT reg
	reg[0] = hts221.H0_T0_Out;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	hts221.H2 = (data[1] << 8) + data[0];

	// Read H1_T0_OUT reg
	reg[0] = hts221.H1_T0_Out;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	hts221.H3 = (data[1] << 8) + data[0];


	/* Calibrate temp */

	// Read T_degC_x8 regs
	reg[0] = hts221.T0_degC;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	hts221.T0 = data[0];
	hts221.T1 = data[1];

	// Read T1/T0msb reg
	reg[0] = hts221.T1T0Msb;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	int msbdata = data[0];

	hts221.T0 = ((msbdata & 0x03) << 8) + hts221.T0;
	hts221.T1 = ((msbdata & 0x0C) << 6) + hts221.T1;


	// Read T0_Out reg
	reg[0] = hts221.T0_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	hts221.T2 = (data[1] << 8) + data[0];


	// Read T1_Out reg
	reg[0] = hts221.T1_OUT;
	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, hts221.DevAddr, data, 2, HAL_MAX_DELAY);

	hts221.T3 = (data[1] << 8) + data[0];

}

void init_hts(){
	hts221.DevAddr = 0x5F << 1;

	hts221.HumReg = 0x28;
	hts221.TempReg = 0x2A;

	/* Calibration registers */
	hts221.H0_rH = 0x30;
	hts221.H1_rH = 0x31;
	hts221.T0_degC = 0x32;
	hts221.T1_degC = 0x33;
	hts221.T1T0Msb = 0x35;
	hts221.H0_T0_Out = 0xB6; // Auto-increment bit set
	hts221.H1_T0_Out = 0xBA; // Auto-increment bit set
	hts221.T0_OUT = 0xBC;	// Auto-increment bit set
	hts221.T0_OUT = 0xBE;	// Auto-increment bit set

	static char config[2];

	config[0] = 0x10;
	config[1] = 0x1B;

	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, config, 2, HAL_MAX_DELAY);

	HAL_Delay(100);

	config[0] = 0x20;
	config[1] = 0x85;

	HAL_I2C_Master_Transmit(&hi2c3, hts221.DevAddr, config, 2, HAL_MAX_DELAY);

	HAL_Delay(100);
}
