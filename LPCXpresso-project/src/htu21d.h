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
 * @file htu21d.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A library for the HTU21D I2C relative humidity sensor.
 */

#ifndef HTU21D_H_
#define HTU21D_H_

#define HTU21D_I2C_ADDR          0x40

#define HTU21D_CMD_TEMP          0xE3
#define HTU21D_CMD_RH            0xE5
#define HTU21D_CMD_USER_REG_READ 0xE7
#define HTU21D_CMD_RESET         0xFE

#define HTU21D_USER_REGISTER     0x02 // Reset value of the user register
#define HTU21D_CRC_DIVISOR       0b100110001

/**
 * An HTU21D object to be passed the the HTU21D routines.
 */
typedef struct {
	LPC_I2C_T *i2c;
	uint8_t connected;
} HTU21D;

/**
 * @brief Initializes the HTU21D on the given I2C port.
 *
 * @param htu Pointer to an #HTU21D object
 * @param i2c_port Pointer to the I2C port
 *
 * @return Returns non-zero value on successful initialization.
 */
uint8_t HTU21D_Init(HTU21D *htu, LPC_I2C_T *i2c);

/**
 * @brief Reads and returns the current humidity from the given HTU21D.
 *
 * @param htu Pointer to an initialized #HTU21D object
 *
 * @return The current humidity in %RH.
 */
uint8_t HTU21D_GetRH(HTU21D *htu);

/**
 * @brief Reads and returns the current temperature from the given HTU21D.
 *
 * @param htu Pointer to an initialized #HTU21D object
 *
 * @return The current temperature in Celsius.
 */
int8_t HTU21D_GetTemp(HTU21D *htu);

#endif /* HTU21D_H_ */
