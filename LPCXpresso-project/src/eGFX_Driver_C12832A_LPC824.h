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
 * @file eGFX_Driver_C12832A_LPC824.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief An eGFX driver for the Newhaven Display C12832A on the NXP LPC824
 * (and probably other LPC8XX) ARM Cortex-M0+.
 *
 * @see The eGFX library: https://github.com/ehughes/eGFX
 */

#ifndef EGFX_DRIVER_C12832A_LPC824_H_
#define EGFX_DRIVER_C12832A_LPC824_H_

#include "chip.h"
#include "eGFX_DataTypes.h"

#define C12832A_A0_CMD  0
#define C12832A_A0_DATA 1

#define C12832A_SPI_BITRATE        5000000
#define C12832A_SPI_CLOCKMODE      SPI_CLOCK_CPHA1_CPOL1 // base=high, capture on rising
#define C12832A_SPI_DATABITS       8

#define C12832A_CMD_DISPLAY_ON     0xAF
#define C12832A_CMD_DISPLAY_OFF    0xAE

#define CMD_SET_DISP_START_LINE    0x40
#define C12832A_CMD_PAGE           0xB0

#define C12832A_CMD_COL_HIGH       0x10
#define C12832A_CMD_COL_LOW        0x00

#define C12832A_CMD_ADC_NORMAL     0xA0
#define C12832A_CMD_ADC_REVERSE    0xA1

#define C12832A_CMD_DISP_NORMAL    0xA6
#define C12832A_CMD_DISP_REVERSE   0xA7

#define C12832A_CMD_ALLPTS_NORMAL  0xA4
#define C12832A_CMD_ALLPTS_ON      0xA5
#define C12832A_CMD_BIAS_9         0xA2
#define C12832A_CMD_BIAS_7		   0xA3

#define C12832A_CMD_RMW            0xE0
#define C12832A_CMD_RMW_CLEAR      0xEE
#define C12832A_CMD_INTERNAL_RESET 0xE2
#define C12832A_CMD_COM_NORMAL     0xC0
#define C12832A_CMD_COM_REVERSE    0xC8
#define C12832A_CMD_POWER_CONTROL  0x28
#define C12832A_CMD_RESISTOR_RATIO 0x20
#define C12832A_CMD_VOLUME_FIRST   0x81
#define C12832A_CMD_VOLUME_SECOND  0x00
#define C12832A_CMD_STATIC_OFF     0xAC
#define C12832A_CMD_STATIC_ON      0xAD
#define C12832A_CMD_STATIC_REG     0x00
#define C12832A_CMD_BOOSTER_FIRST  0xF8
#define C12832A_CMD_BOOSTER_234    0
#define C12832A_CMD_BOOSTER_5      1
#define C12832A_CMD_BOOSTER_6      3
#define C12832A_CMD_NOP            0xE3
#define C12832A_CMD_TEST           0xF0


/**
 * The C12832A object
 */
typedef struct {
	LPC_SPI_T *lpc_spi;
	uint8_t a0_pin;
	uint8_t rst_pin;
	uint8_t ssel_num;
} C12832A_config;

// LCD GFX Driver Configuration.
// The Symbols below must be defined for the GFX library to work.
#define eGFX_PHYSICAL_SCREEN_SIZE_X	((uint16_t) 128)
#define eGFX_PHYSICAL_SCREEN_SIZE_Y	((uint16_t) 32)

// This driver requires the user to define a routine for blocking delays
extern void delayms(uint16_t ms);

/**
 * @brief Writes a command to the screen
 *
 * @param screen An initialized #C12832A_config object
 * @param command The command byte to write
 */
void C12832A_writeCommand(C12832A_config *screen, uint8_t command);

/**
 * @brief Writes a byte of data to the screen
 *
 * @param screen An initialized #C12832A_config object
 * @param data The data byte to write
 */
void C12832A_writeData(C12832A_config *screen, uint8_t data);

/**
 * @brief Sets the current page address in the LCD's RAM
 *
 * @param screen An initialized #C12832A_config object
 * @param page The desired page address
 */
void C12832A_setPageAddress(C12832A_config *screen, uint8_t page);

/**
 * @brief Sets the current column address in the LCD's RAM
 *
 * @param screen An initialized #C12832A_config object
 * @param column The desired column address
 */
void C12832A_setColumnAddress(C12832A_config *screen, uint8_t column);

/**
 * @brief Sets the SPI port's settings per the C12832A's requirements
 *
 * This is automatically called by #C12832A_Init, but can come in handy if
 * the C12832A is sharing the bus with devices that require different SPI
 * configurations.
 *
 * @param screen An initialized #C12832A_config object
 */
void C12832A_ConfigureSPI(C12832A_config *screen);


/**
 * @brief Initializes the C12832A
 *
 * this function returns, the given C12832A_config object will be initialized
 * and ready to pass to the other functions.
 *
 * @param screen A #C12832A_config object
 * @param lpc_spi The SPI port the screen is connected to
 * @param a0_pin The GPIO pin connected to the screen's A0 input
 * @param rst_pin The GPIO pin connected to the screen's reset input
 * @param ssel_num Which of the SPI port's SSEL signals to use for the screen
 */
void C12832A_Init(C12832A_config *screen, LPC_SPI_T *lpc_spi, uint8_t a0_pin,
				  uint8_t rst_pin, uint8_t ssel_num);

/**
 * @brief Set's the screen's contrast
 *
 * @param screen An initialized #C12832A_config object
 * @param contrast The desired contrast (0-63)
 */
void C12832A_SetContrast(C12832A_config *screen, uint8_t contrast);

/**
 * @brief Initializes the eGFX driver
 *
 * Must be called before using eGFX with this driver
 */
void eGFX_InitDriver();

/**
 * @brief Sends the backbuffer to the screen
 *
 * @param Image The eGFX backbuffer object
 * @param screen An initialized #C12832A_config object
 */
void eGFX_Dump(eGFX_ImagePlane *Image, C12832A_config *screen);

/**
 * The eGFX backbuffer used by this driver
 */
eGFX_ImagePlane eGFX_BackBuffer;


#endif /* EGFX_DRIVER_C12832A_LPC824_H_ */
