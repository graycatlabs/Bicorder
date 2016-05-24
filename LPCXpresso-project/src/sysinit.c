/*
 * @brief Common SystemInit function for LPC8xx chips
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013-14
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"

#include "bicorder.h"

const uint32_t OscRateIn = 12000000;
const uint32_t ExtRateIn = 0;

void pinMux(void) {
	int i;
	// Switch Matrix config:
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

	// Mux the SPI signals:
	Chip_SWM_MovablePinAssign(SWM_SPI0_MOSI_IO, SPI_MOSI_PIN);
	Chip_SWM_MovablePinAssign(SWM_SPI0_SCK_IO, SPI_SCK_PIN);
	Chip_SWM_MovablePinAssign(SWM_LCD_CS, LCD_CS_PIN);

	// Enable the ADC input for the range finder:
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC8);

	// Enabled xtal pins - required to use external osc:
	Chip_SWM_FixedPinEnable(SWM_FIXED_XTALIN, 1);
	Chip_SWM_FixedPinEnable(SWM_FIXED_XTALOUT, 1);

	// Enable the I2C0 data pin (clock comes later after a little hack):
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);

	// IOCON config:
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	// Disable pullups on xtal in/out:
	Chip_IOCON_PinSetMode(LPC_IOCON, IOCON_PIO8, PIN_MODE_INACTIVE);
	Chip_IOCON_PinSetMode(LPC_IOCON, IOCON_PIO9, PIN_MODE_INACTIVE);

	// Disable pullup on ADC8 input:
	Chip_IOCON_PinSetMode(LPC_IOCON, IOCON_PIO18, PIN_MODE_INACTIVE);

	// Enable Fast Mode Plus for I2C data:
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO11, PIN_I2CMODE_FASTPLUS);

	// Set the I2C0 clock pin to GPIO output mode:
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO10, PIN_I2CMODE_GPIO);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, MoonLander_IO_SCL);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 1);

	// Enable the GPIO module clock:
	Chip_GPIO_Init(LPC_GPIO_PORT);

	// Toggle the I2C clock pin a few times to make sure any confused I2C
	// devices get back to a good state:
	for (i=0; i<32; i++) {
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 0);
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 1);
	}

	// Now set the I2C0 SCL pin to I2C mode and enalbe it:
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO10, PIN_I2CMODE_FASTPLUS);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);

	// Don't need these clocks anymore - disable to save a little power:
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_IOCON);
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

}

/* Set up and initialize hardware prior to call to main */
void SystemInit(void)
{
	//Chip_SystemInit();
	//return;
	pinMux();
	Chip_SetupXtalClocking();
}
