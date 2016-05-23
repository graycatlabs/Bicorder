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
 * @file hmc5883l.c
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A library for the HMC5883L 3-axis I2C magnetometer.
 */

#include "chip.h"
#include "hmc5883l.h"

#include "gcl-fixedpoint.h"
#include "MoonLander-i2c.h"

uint8_t HMC5883L_GetXYZ(HMC5883L *hmc, int_fp *x, int_fp *y, int_fp *z) {
	uint8_t data_buffer[6], cmd, ret;
	int_fp divider_fp;
	int16_t x_raw, y_raw, z_raw;
	if (!hmc->connected) return 0;
	cmd = HMC5883L_REG_X_MSB;
	ret = MoonLander_I2C_Transaction(hmc->i2c, HMC5883L_I2C_ADDR,
								     &cmd, 1, data_buffer, 6);
	if (!ret) return 0;

	x_raw = (data_buffer[0]<<8) | data_buffer[1];
	z_raw = (data_buffer[2]<<8) | data_buffer[3];
	y_raw = (data_buffer[4]<<8) | data_buffer[5];

	divider_fp = FP_INT(hmc->divider);


	if (x_raw == -4096) (*x) = FP_INT(9000);
	else {
		(*x) = FP_INT((int32_t) x_raw);
		(*x) = int_fp_div((*x), divider_fp);  // In Gauss
		(*x) = int_fp_mul((*x), FP_INT(100)); // In uTesla
	}

	if (y_raw == -4096) (*y) = FP_INT(9000);
	else {
		(*y) = FP_INT((int32_t) y_raw);
		(*y) = int_fp_div((*y), divider_fp);  // In Gauss
		(*y) = int_fp_mul((*y), FP_INT(100)); // In uTesla
	}
	if (z_raw == -4096) (*z) = FP_INT(9000);
	else {
		(*z) = FP_INT((int32_t) z_raw);
		(*z) = int_fp_div((*z), divider_fp);  // In Gauss
		(*z) = int_fp_mul((*z), FP_INT(100)); // In uTesla
	}
	return 1;
}

uint8_t HMC5883L_SetRange(HMC5883L *hmc, HMC5883L_range range) {
	uint8_t tx_buffer[2], ret;
	if (!hmc->connected) return 0;
	tx_buffer[0] = HMC5883L_REG_CONFIG_B;
	tx_buffer[1] = range;
	ret = MoonLander_I2C_Write(hmc->i2c, HMC5883L_I2C_ADDR, tx_buffer, 2);
	if (!ret) return 0;

	switch(range) {
	case HMC5883L_RANGE_0_88:
		hmc->divider = HMC5883L_DIVIDER_RANGE_0_88;
		break;
	case HMC5883L_RANGE_1_3:
		hmc->divider = HMC5883L_DIVIDER_RANGE_1_3;
		break;
	case HMC5883L_RANGE_1_9:
		hmc->divider = HMC5883L_DIVIDER_RANGE_1_9;
		break;
	case HMC5883L_RANGE_2_5:
		hmc->divider = HMC5883L_DIVIDER_RANGE_2_5;
		break;
	case HMC5883L_RANGE_4_0:
		hmc->divider = HMC5883L_DIVIDER_RANGE_4_0;
		break;
	case HMC5883L_RANGE_4_7:
		hmc->divider = HMC5883L_DIVIDER_RANGE_4_7;
		break;
	case HMC5883L_RANGE_5_6:
		hmc->divider = HMC5883L_DIVIDER_RANGE_5_6;
		break;
	case HMC5883L_RANGE_8_1:
		hmc->divider = HMC5883L_DIVIDER_RANGE_8_1;
		break;
	default:
		break;
	}

	hmc->range = range;
	return 1;
}

uint8_t HMC5883L_Init(HMC5883L *hmc, LPC_I2C_T *i2c) {
	uint8_t tx_buffer[2], ret;
	uint8_t id_buffer[3];
	hmc->i2c = i2c;
	tx_buffer[0] = HMC5883L_REG_ID_A;
	ret = MoonLander_I2C_Transaction(hmc->i2c, HMC5883L_I2C_ADDR,
								     tx_buffer, 1, id_buffer, 3);

	if (ret && id_buffer[0] == HMC5883L_ID_A &&
			id_buffer[1] == HMC5883L_ID_B &&
			id_buffer[2] == HMC5883L_ID_C) {
		hmc->connected = 1;
	}
	else {
		hmc->connected = 0;
		return 0;
	}

	if (!HMC5883L_SetRange(hmc, HMC5883L_RANGE_1_3)) return 0;
	// Set to continuous sampling (@ default 15Hz):
	tx_buffer[0] = HMC5883L_REG_MODE;
	tx_buffer[1] = 0x00;
	ret = MoonLander_I2C_Write(hmc->i2c, HMC5883L_I2C_ADDR, tx_buffer, 2);
	//if (!ret) return 0;
	hmc->connected = 1;
	return 1;
}
