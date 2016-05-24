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
 * @file eGFX_Driver_C12832A_LPC824.c
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief An eGFX driver for the Newhaven Display C12832A on the NXP LPC824
 * (and probably other LPC8XX) ARM Cortex-M0+.
 */


#include "chip.h"
#include "eGFX_DataTypes.h"
#include "eGFX.h"
#include "eGFX_Driver_C12832A_LPC824.h"

eGFX_ImagePlane eGFX_BackBuffer;
uint8_t BackBufferStore[eGFX_CALCULATE_1BPP_IMAGE_STORAGE_SPACE_SIZE(
						  eGFX_PHYSICAL_SCREEN_SIZE_X,
						  eGFX_PHYSICAL_SCREEN_SIZE_Y
						)];


void C12832A_ConfigureSPI(C12832A_config *screen) {
	SPI_DELAY_CONFIG_T DelayConfigStruct;

	Chip_SPI_ConfigureSPI(screen->lpc_spi, SPI_MODE_MASTER |	/* Enable master/Slave mode */
						  C12832A_SPI_CLOCKMODE |				/* Set Clock polarity to 0 */
						  SPI_CFG_MSB_FIRST_EN |				/* Enable MSB first option */
						  SPI_CFG_SPOL_LO);						/* Chipselect is active low */

	DelayConfigStruct.FrameDelay = 0;
	DelayConfigStruct.PostDelay = 0;
	DelayConfigStruct.PreDelay = 0;
	DelayConfigStruct.TransferDelay = 0;
	Chip_SPI_DelayConfig(screen->lpc_spi, &DelayConfigStruct);

	Chip_SPI_SetXferSize(screen->lpc_spi, C12832A_SPI_DATABITS);

	Chip_SPIM_SetClockRate(screen->lpc_spi, C12832A_SPI_BITRATE);

	Chip_SPI_Enable(screen->lpc_spi);
}

void C12832A_writeCommand(C12832A_config *screen, uint8_t command) {
	SPI_DATA_SETUP_T xfer;
	uint16_t tx = (uint16_t) command;
	xfer.DataSize = 8;
	xfer.Length = 1;
	xfer.pTx = &tx;
	Chip_SPIM_AssertSSEL(screen->lpc_spi, screen->ssel_num);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->a0_pin, C12832A_A0_CMD);
	Chip_SPI_WriteFrames_Blocking(screen->lpc_spi, &xfer);
	Chip_SPIM_DeAssertSSEL(screen->lpc_spi, screen->ssel_num);
}

void C12832A_writeData(C12832A_config *screen, uint8_t data) {
	SPI_DATA_SETUP_T xfer;
	uint16_t tx = (uint16_t) data;
	xfer.DataSize = 8;
	xfer.Length = 1;
	xfer.pTx = &tx;
	Chip_SPIM_AssertSSEL(screen->lpc_spi, screen->ssel_num);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->a0_pin, C12832A_A0_DATA);
	Chip_SPI_WriteFrames_Blocking(screen->lpc_spi, &xfer);
	Chip_SPIM_DeAssertSSEL(screen->lpc_spi, screen->ssel_num);
}



void C12832A_setPageAddress(C12832A_config *screen, uint8_t page) {
	C12832A_writeCommand(screen, C12832A_CMD_PAGE | (page & 0xf));
}

void C12832A_setColumnAddress(C12832A_config *screen, uint8_t column) {
	C12832A_writeCommand(screen, C12832A_CMD_COL_HIGH | (column>>4));
	C12832A_writeCommand(screen, C12832A_CMD_COL_LOW | (column & 0xf));
}

void C12832A_Init(C12832A_config *screen, LPC_SPI_T *lpc_spi, uint8_t a0_pin,
				  uint8_t rst_pin, uint8_t ssel_num) {

	screen->lpc_spi = lpc_spi;
	screen->a0_pin = a0_pin;
	screen->rst_pin = rst_pin;
	screen->ssel_num = ssel_num;

	C12832A_ConfigureSPI(screen);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, screen->a0_pin);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, screen->rst_pin);

	/*
	// Initialization procedure given in datasheet:

	C12832A_writeCommand(screen, C12832A_CMD_ADC_NORMAL); // RAM address correspondence = normal
	C12832A_writeCommand(screen, C12832A_CMD_DISPLAY_OFF); // RAM address correspondence = normal
	C12832A_writeCommand(screen, C12832A_CMD_COM_NORMAL); // COM output scan direction = normal
	C12832A_writeCommand(screen, C12832A_CMD_BIAS_9); // Drive voltage to 1/9 bias
	C12832A_writeCommand(screen, C12832A_CMD_POWER_CONTROL | 0x7);
	delayms(10);
	C12832A_writeCommand(screen, C12832A_CMD_RESISTOR_RATIO | 1); // Internal resistor ratio (Rb/Ra) to 1
	C12832A_SetContrast(screen, 0x3f);
	*/

	// u8glib init sequence:
	Chip_SPIM_DeAssertSSEL(screen->lpc_spi, screen->ssel_num);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->a0_pin, C12832A_A0_CMD);
	delayms(100);

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->rst_pin, 0);
	delayms(500);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->rst_pin, 1);
	delayms(100);

	C12832A_writeCommand(screen, CMD_SET_DISP_START_LINE);
	C12832A_writeCommand(screen, C12832A_CMD_ADC_NORMAL);
	C12832A_writeCommand(screen, C12832A_CMD_COM_REVERSE);
	C12832A_writeCommand(screen, C12832A_CMD_DISP_NORMAL);
	C12832A_writeCommand(screen, C12832A_CMD_BIAS_9);

	C12832A_writeCommand(screen, C12832A_CMD_POWER_CONTROL | 0x4);
	delayms(50);
	C12832A_writeCommand(screen, C12832A_CMD_POWER_CONTROL | 0x6);
	delayms(50);
	C12832A_writeCommand(screen, C12832A_CMD_POWER_CONTROL | 0x7);
	delayms(10);

	C12832A_writeCommand(screen, C12832A_CMD_BOOSTER_FIRST);
	C12832A_writeCommand(screen, C12832A_CMD_BOOSTER_234);
	C12832A_writeCommand(screen, C12832A_CMD_RESISTOR_RATIO | 0x3);
	C12832A_SetContrast(screen, 0xa);
	C12832A_writeCommand(screen, C12832A_CMD_STATIC_OFF);
	C12832A_writeCommand(screen, 0x0);
	C12832A_writeCommand(screen, C12832A_CMD_DISPLAY_ON);

}

void C12832A_SetContrast(C12832A_config *screen, uint8_t contrast) {
	C12832A_writeCommand(screen, C12832A_CMD_VOLUME_FIRST);
	C12832A_writeCommand(screen, C12832A_CMD_VOLUME_SECOND | (contrast & 0x3f));
}

void eGFX_InitDriver() {
	eGFX_ImagePlaneInit(&eGFX_BackBuffer, &BackBufferStore[0], eGFX_PHYSICAL_SCREEN_SIZE_X,
							eGFX_PHYSICAL_SCREEN_SIZE_Y, eGFX_IMAGE_PLANE_1BPP);
}

void eGFX_Dump(eGFX_ImagePlane *Image, C12832A_config *screen) {
	SPI_DATA_SETUP_T xfer;
	uint32_t offset;
	uint16_t tx[128];
	uint8_t column, page, bit, y, mask;

	xfer.DataSize = 8;
	xfer.pTx = tx;

	Chip_SPIM_AssertSSEL(screen->lpc_spi, screen->ssel_num);

	y = 0;
	for (page=0; page<4; page++) {
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->a0_pin, C12832A_A0_CMD);

		// Set page address:
		tx[0] = (uint16_t) (C12832A_CMD_PAGE | (page & 0xf));

		// Set to first column:
		tx[1] = (uint16_t) (C12832A_CMD_COL_LOW);
		tx[2] = (uint16_t) C12832A_CMD_COL_HIGH;
		xfer.Length = 3;
		Chip_SPI_WriteFrames_Blocking(screen->lpc_spi, &xfer);

		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, screen->a0_pin, C12832A_A0_DATA); // data mode

		for (column=0; column<128; column++) {
			tx[column] = 0;
			for (bit=0; bit<8; bit++) {

				offset = ((y+bit) * 16) + (column>>3);
				mask = 0x01 << (column & 0x07);

                if(Image->Data[offset] & mask) {
                	tx[column] |= 1<<bit;
                }
			}
		}
		xfer.Length = 128;
		Chip_SPI_WriteFrames_Blocking(screen->lpc_spi, &xfer);
		y += 8;
	}

	Chip_SPIM_DeAssertSSEL(screen->lpc_spi, screen->ssel_num);
}

