/*******************************************************************************
 * Copyright (c) 2016 - Gray Cat Labs - https://graycat.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/**
 * @file htu21d.c
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A library for the HMC5883L 3-axis I2C magnetometer.
 */

#include "chip.h"
#include "htu21d.h"
#include "MoonLander-i2c.h"


uint8_t HTU21D_GetRH(HTU21D *htu) {
	uint8_t rx_buffer[3], cmd, ret;
	float raw_value;
	if (htu->connected == 0) return 0;
	cmd = HTU21D_CMD_RH;
	ret = MoonLander_I2C_Transaction(htu->i2c, HTU21D_I2C_ADDR,
								     &cmd, 1, rx_buffer, 3);
	if (!ret) return 0;
	raw_value = (rx_buffer[0]<<8) | rx_buffer[1];
	return (uint8_t) (-6 + 125 * (raw_value / 65536));
}

int8_t HTU21D_GetTemp(HTU21D *htu) {
	uint8_t rx_buffer[3], cmd, ret;
	float raw_value;
	if (htu->connected == 0) return 0;
	cmd = HTU21D_CMD_TEMP;
	ret = MoonLander_I2C_Transaction(htu->i2c, HTU21D_I2C_ADDR,
								     &cmd, 1, rx_buffer, 3);
	raw_value = (rx_buffer[0]<<8) | rx_buffer[1];
	return (uint8_t) (-46.85 + 175.72 * (raw_value / 65536));
}

uint8_t HTU21D_Init(HTU21D *htu, LPC_I2C_T *i2c) {
	//uint8_t user_reg, cmd, ret;
	htu->i2c = i2c;
	htu->connected = 1;
	return 1;
	/*
	htu->connected = 0;
	cmd = HTU21D_CMD_USER_REG_READ;
	user_reg = 0;
	ret = MoonLander_I2C_Transaction(htu->i2c, HTU21D_I2C_ADDR,
								     &cmd, 1, &user_reg, 1);

	if (ret && user_reg == HTU21D_USER_REGISTER) {
		htu->connected = 1;
		return 1;
	}
	return 0;
	*/
}

