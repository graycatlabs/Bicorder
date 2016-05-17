/*
 * MoonLander-i2c.c
 *
 *  Created on: May 15, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#include "chip.h"
#include "MoonLander-i2c.h"


static I2CM_XFER_T  i2cmXferRec;


uint32_t MoonLander_I2C_Read(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							 uint8_t *rx_buffer, uint8_t len) {
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = slave_addr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = 0;
	i2cmXferRec.rxSz =len;
	i2cmXferRec.rxBuff = rx_buffer;
	return Chip_I2CM_XferBlocking(i2c_port, &i2cmXferRec);
}

uint32_t MoonLander_I2C_Write(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							  uint8_t *tx_buffer, uint8_t len) {
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = slave_addr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = len;
	i2cmXferRec.rxSz =0;
	i2cmXferRec.txBuff = tx_buffer;
	return Chip_I2CM_XferBlocking(i2c_port, &i2cmXferRec);
}

uint32_t MoonLander_I2C_Transaction(LPC_I2C_T *i2c_port, uint8_t slave_addr,
							        uint8_t *tx_buffer, uint8_t tx_len,
									uint8_t *rx_buffer, uint8_t rx_len) {
	/* Setup I2C transfer record */
	i2cmXferRec.slaveAddr = slave_addr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = tx_len;
	i2cmXferRec.rxSz =rx_len;
	i2cmXferRec.txBuff = tx_buffer;
	i2cmXferRec.rxBuff = rx_buffer;
	return Chip_I2CM_XferBlocking(i2c_port, &i2cmXferRec);
}

void MoonLander_I2C_Init(LPC_I2C_T *i2c_port, MoonLander_I2C_bitrate bitrate) {

	Chip_I2C_Init(i2c_port);

	switch (bitrate) {
	case MOONLANDER_I2C_100K:
		Chip_I2C_SetClockDiv(i2c_port, 50);
		Chip_I2CM_SetBusSpeed(i2c_port, 100000);
		break;

	case MOONLANDER_I2C_400K:
	default:
		Chip_I2C_SetClockDiv(i2c_port, 3);
		Chip_I2CM_SetBusSpeed(i2c_port, 400000);
		break;

	}
	Chip_I2CM_Enable(i2c_port);
}

