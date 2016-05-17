/*
 * bicorder.h
 *
 *  Created on: May 11, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#ifndef BICORDER_H__
#define BICORDER_H_

#include "MoonLander.h"
#include "chip.h"


#define SPI_MOSI_PIN  MoonLander_IO1
#define SPI_SCK_PIN   MoonLander_IO2

#define SPI_PORT      LPC_SPI0

#define LCD_A0_PIN    MoonLander_IO3
#define LCD_RST_PIN   MoonLander_IO4

#define LCD_BACKLIGHT MoonLander_IO7

#define LCD_CS_PIN    MoonLander_IO5
#define LCD_SSEL      0
#define SWM_LCD_CS    SWM_SPI0_SSEL0_IO

#define SW_LEFT             MoonLander_IO9
#define SW_RIGHT            MoonLander_IO10

#define SW_LEFT_PININT      0
#define SW_LEFT_PININTCH   (1<<SW_LEFT_PININT)
#define SW_LEFT_IRQn        PININT0_IRQn
#define SW_LEFT_IRQHandler  PIN_INT0_IRQHandler

#define SW_RIGHT_PININT     1
#define SW_RIGHT_PININTCH  (1<<SW_RIGHT_PININT)
#define SW_RIGHT_IRQn       PININT1_IRQn
#define SW_RIGHT_IRQHandler PIN_INT1_IRQHandler

#define SW1_PININT     2
#define SW1_PININTCH   (1<<SW1_PININT)
#define SW1_IRQn       PININT2_IRQn
#define SW1_IRQHandler PIN_INT2_IRQHandler

#define SW_DEBOUNCE_MS 300

#define RANGE_POWER_PIN MoonLander_IO6
#define RANGE_AIN       MoonLander_IO8_ADC

#define ADC_V_PER_LSB 0.0008056640625

#define SENSOR_I2C    LPC_I2C0

// Sample periods in ms:
#define SAMPLE_PERIOD_TEMP  100
#define SAMPLE_PERIOD_RH    100
#define SAMPLE_PERIOD_MAG   100
#define SAMPLE_PERIOD_RANGE 100

#define TICKRATE_HZ   1000
#define MS_PER_TICK   1

#define BLINK_PERIOD_MS 500

#define I2C_CLK_DIVIDER 50
#define I2C_BITRATE     MOONLANDER_I2C_100K


typedef enum {
	DISPLAY_TEMP,
	DISPLAY_RH,
	DISPLAY_MAG,
	DISPLAY_COMPASS,

	DISPLAY_RANGE,
	N_DISPLAYS
} uCorder_display;

#endif /BICORDER_H__H_ */
