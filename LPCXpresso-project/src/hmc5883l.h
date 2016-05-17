/*
 * hmc5883l.h
 *
 *  Created on: May 13, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
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

typedef enum {
	HMC5883L_RANGE_0_88 = 0x00,
	HMC5883L_RANGE_1_3  = 0x20,
	HMC5883L_RANGE_1_9  = 0x40,
	HMC5883L_RANGE_2_5  = 0x60,
	HMC5883L_RANGE_4_0  = 0x80,
	HMC5883L_RANGE_4_7  = 0xA0,
	HMC5883L_RANGE_5_6  = 0xC0,
	HMC5883L_RANGE_8_1  = 0xE0
} HMC5883L_range;

typedef struct {
	LPC_I2C_T *i2c;
	uint8_t connected;
	HMC5883L_range range;
	int16_t divider;
} HMC5883L;

uint8_t HMC5883L_Init(HMC5883L *hmc, LPC_I2C_T *i2c);

uint8_t HMC5883L_SetRange(HMC5883L *hmc, HMC5883L_range range);

uint8_t HMC5883L_GetXYZ(HMC5883L *hmc, int32_t *x, int32_t *y, int32_t *z);

uint32_t HMC5883L_ReadRegister(HMC5883L *hmc, uint8_t addr, uint8_t *value);

uint32_t HMC5883L_WriteRegister(HMC5883L *hmc, uint8_t addr, uint8_t value);

uint32_t HMC5883L_ReadRegisters(HMC5883L *hmc, uint8_t start_addr,
							    uint8_t *rx_buffer, uint8_t len);


#endif /* HMC5883L_H_ */
