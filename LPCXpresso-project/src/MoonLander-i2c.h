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
 * @file MoonLander-i2c.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief Basic polling I2C master driver for the NXP LPC824 (and probably
 * other LPC8XX) ARM Cortex-M0+.
 */

#ifndef MOONLANDER_I2C_H_
#define MOONLANDER_I2C_H_

/**
 * Passed to #MoonLander_I2C_Init to set the bitrate for the I2C interface.
 */
typedef enum {
	MOONLANDER_I2C_100K, ///< 100kHz clock
	MOONLANDER_I2C_400K  ///< 400kHz clock
}MoonLander_I2C_bitrate;

/**
 * @brief Initializes the given I2C interface at the given bitrate.
 *
 * Note the bitrate is currently set assuming that the system clock is
 * running at 30MHz, so other clock rates won't result in the correct btrate.
 *
 * @param i2c_port Pointer to the I2C port
 */
void MoonLander_I2C_Init(LPC_I2C_T *i2c_port, MoonLander_I2C_bitrate bitrate);


/**
 * @brief Attempt to read some bytes from an I2C slave.
 *
 * @param i2c_port Pointer to the I2C port
 * @param slave_addr Address of I2C slave device to read from
 * @param rx_buffer Preinitialized buffer to place read bytes
 * @param len Number of bytes to read
 *
 * @return Returns non-zero value on successful completion of transfer.
 */
uint32_t MoonLander_I2C_Read(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							 uint8_t *rx_buffer, uint8_t len);

/**
 * @brief Attempt to write some bytes to an I2C slave.
 *
 * @param i2c_port Pointer to the I2C port
 * @param slave_addr Address of I2C slave device to write to
 * @param tx_buffer Array of bytes to write
 * @param len Number of bytes to write
 *
 * @return Returns non-zero value on successful completion of transfer.
 */
uint32_t MoonLander_I2C_Write(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							  uint8_t *tx_buffer, uint8_t len);

/**
 * @brief Write some bytes to then immediately read some bytes from an I2C slave.
 *
 * @param i2c_port Pointer to the I2C port
 * @param slave_addr Address of I2C slave device
 * @param tx_buffer Array of bytes to write
 * @param tx_len Number of bytes to write
 * @param rx_buffer Preinitialized buffer to place read bytes
 * @param tx_len Number of bytes to read
 *
 * @return Returns non-zero value on successful completion of transfer.
 */
uint32_t MoonLander_I2C_Transaction(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							        uint8_t *tx_buffer, uint8_t tx_len,
									uint8_t *rx_buffer, uint8_t rx_len);


#endif /* MOONLANDER_I2C_H_ */
