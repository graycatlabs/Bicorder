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
 * @file hmc5883l.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A library for the HMC5883L 3-axis I2C magnetometer.
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#define HMC5883L_I2C_ADDR     0x1E

#define HMC5883L_REG_CONFIG_A 0x00
#define HMC5883L_REG_CONFIG_B 0x01
#define HMC5883L_REG_MODE     0x02
#define HMC5883L_REG_X_MSB    0x03
#define HMC5883L_REG_X_LSB    0x04
#define HMC5883L_REG_Z_MSB    0x05
#define HMC5883L_REG_Z_LSB    0x06
#define HMC5883L_REG_Y_MSB    0x07
#define HMC5883L_REG_Y_LSB    0x08
#define HMC5883L_REG_STATUS   0x09
#define HMC5883L_REG_ID_A     0x0a
#define HMC5883L_REG_ID_B     0x0b
#define HMC5883L_REG_ID_C     0x0c

#define HMC5883L_ID_A         0x48 // ASCII 'H'
#define HMC5883L_ID_B         0x34 // ASCII '4'
#define HMC5883L_ID_C         0x33 // ASCII '3'

#define	HMC5883L_DIVIDER_RANGE_0_88 1370
#define	HMC5883L_DIVIDER_RANGE_1_3  1090
#define	HMC5883L_DIVIDER_RANGE_1_9  820
#define	HMC5883L_DIVIDER_RANGE_2_5  660
#define	HMC5883L_DIVIDER_RANGE_4_0  440
#define	HMC5883L_DIVIDER_RANGE_4_7  390
#define	HMC5883L_DIVIDER_RANGE_5_6  330
#define	HMC5883L_DIVIDER_RANGE_8_1  230

/**
 * To be passed to #HMC5883L_SetRange
 */
typedef enum {
	HMC5883L_RANGE_0_88 = 0x00, ///< +/- 0.88 Gauss
	HMC5883L_RANGE_1_3  = 0x20, ///< +/- 1.3 Gauss
	HMC5883L_RANGE_1_9  = 0x40, ///< +/- 1.9 Gauss
	HMC5883L_RANGE_2_5  = 0x60, ///< +/- 2.5 Gauss
	HMC5883L_RANGE_4_0  = 0x80, ///< +/- 4.0 Gauss
	HMC5883L_RANGE_4_7  = 0xA0, ///< +/- 4.7 Gauss
	HMC5883L_RANGE_5_6  = 0xC0, ///< +/- 5.6 Gauss
	HMC5883L_RANGE_8_1  = 0xE0 ///< +/- 8.1 Gauss
} HMC5883L_range;

/**
 * An HMC5883L object to be passed the the HMC5883L routines.
 */
typedef struct {
	LPC_I2C_T *i2c;
	uint8_t connected;
	HMC5883L_range range;
	int16_t divider;
} HMC5883L;

/**
 * @brief Initializes the HMC5883L on the given I2C port.
 *
 * @param hmc Pointer to an #HMC5883L object
 * @param i2c_port Pointer to the I2C port
 *
 * @return Returns non-zero value on successful initialization.
 */
uint8_t HMC5883L_Init(HMC5883L *hmc, LPC_I2C_T *i2c);

/**
 * @brief Sets the range of the HMC5883L.
 *
 * @param hmc Pointer to an initialized #HMC5883L object
 * @param range The desired range
 *
 * @return Returns non-zero value on success.
 */
uint8_t HMC5883L_SetRange(HMC5883L *hmc, HMC5883L_range range);

/**
 * @brief Reads the current magnetic field strength.
 *
 * @param hmc Pointer to an initialized #HMC5883L object
 * @param x Address to store current X value in uTesla
 * @param y Address to store current Y value in uTesla
 * @param z Address to store current Z value in uTesla
 *
 * @return Returns non-zero value on success.
 */
uint8_t HMC5883L_GetXYZ(HMC5883L *hmc, int32_t *x, int32_t *y, int32_t *z);

/**
 * @brief Reads the value of the given register in the HMC5883L.
 *
 * @param hmc Pointer to an initialized #HMC5883L object
 * @param addr Register address to read
 * @param y Address to store register value
 *
 * @return Returns non-zero value on success.
 */
uint32_t HMC5883L_ReadRegister(HMC5883L *hmc, uint8_t addr, uint8_t *value);

/**
 * @brief Writes the given value in the given HMC5883L register.
 *
 * @param hmc Pointer to an initialized #HMC5883L object
 * @param addr Register address to read
 * @param value Address to store register value
 *
 * @return Returns non-zero value on success.
 */
uint32_t HMC5883L_WriteRegister(HMC5883L *hmc, uint8_t addr, uint8_t value);

/**
 * @brief Reads data from the HMC5883L starting at the given register address.
 *
 * @param hmc Pointer to an initialized #HMC5883L object
 * @param start_addr Register address to start read
 * @param rx_buffer Initialized buffer to store read data
 * @param len Number of bytes to read
 *
 * @return Returns non-zero value on success.
 */
uint32_t HMC5883L_ReadRegisters(HMC5883L *hmc, uint8_t start_addr,
							    uint8_t *rx_buffer, uint8_t len);


#endif /* HMC5883L_H_ */
