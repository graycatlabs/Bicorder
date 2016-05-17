/*
 * htu21d.h
 *
 *  Created on: May 13, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
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

typedef struct {
	LPC_I2C_T *i2c;
	uint8_t connected;
} HTU21D;


uint8_t HTU21D_Init(HTU21D *htu, LPC_I2C_T *i2c);

uint8_t HTU21D_GetRH(HTU21D *htu);
int8_t HTU21D_GetTemp(HTU21D *htu);

#endif /* HTU21D_H_ */
