/*
 * MoonLander-i2c.h
 *
 *  Created on: May 15, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 *
 *	Basic polling I2C driver for the LPC824 (and probably other LPC8xx)
 */

#ifndef MOONLANDER_I2C_H_
#define MOONLANDER_I2C_H_


uint32_t MoonLander_I2C_Read(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							 uint8_t *rx_buffer, uint8_t len);

uint32_t MoonLander_I2C_Write(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							  uint8_t *tx_buffer, uint8_t len);

uint32_t MoonLander_I2C_Transaction(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							        uint8_t *tx_buffer, uint8_t tx_len,
									uint8_t *rx_buffer, uint8_t rx_len);

typedef enum {
	MOONLANDER_I2C_100K,
	MOONLANDER_I2C_400K
}MoonLander_I2C_bitrate;
void MoonLander_I2C_Init(LPC_I2C_T *i2c_port, MoonLander_I2C_bitrate bitrate);


#endif /* MOONLANDER_I2C_H_ */
