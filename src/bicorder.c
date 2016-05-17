/*
===============================================================================
 Name        : bicorder.c
 Author      : Alex Hiam <alex@graycat.io>
 Version     :
 Copyright   : Gray Cat Labs - 2016
 Description : main definition
===============================================================================
*/

#include "bicorder.h"

#include "chip.h"
#include <cr_section_macros.h>

#include "MoonLander.h"
#include "MoonLander-i2c.h"

#include "eGFX.h"
#include "eGFX_Driver_C12832A_LPC824.h"
#include "Fonts/FONT_3_5_1BPP.h"

#include "htu21d.h"
#include "hmc5883l.h"

#include "gcl-fixedpoint.h"

#include <math.h>
#include "bicorder-compass.h"
#include "bicorder-plotter.h"

static C12832A_config g_C12832A;

// Sensors:
static HTU21D g_HTU21D;
static HMC5883L g_HMC5883L;

// Plots:
static volatile uCorder_plot g_plot_temp;
static volatile uCorder_plot g_plot_rh;

static volatile uCorder_Compass g_compass;

static volatile uCorder_plot g_plot_mag;
static volatile uint32_t g_delayms_counter;
static volatile uint32_t g_millis_counter;

static volatile uint8_t g_adc_sample_ready = 0;
static volatile uint32_t g_range_raw = 0;

static volatile uint8_t g_left_display = DISPLAY_TEMP;
static volatile uint8_t g_right_display = DISPLAY_RH;

static volatile uint8_t g_sw_left_debouncing = 0;
static volatile uint16_t g_sw_left_debounce_counter;
static volatile uint8_t g_sw_right_debouncing = 0;
static volatile uint16_t g_sw_right_debounce_counter;

static volatile uint8_t g_go_to_sleep;

void gpioInit(void) {
    //Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, LCD_BACKLIGHT);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, LCD_BACKLIGHT, 1);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, RANGE_POWER_PIN);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RANGE_POWER_PIN, 0);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, MoonLander_LED);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_LED, 0);

	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, SW_LEFT);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, SW_RIGHT);
}

void interruptInit(void) {
	Chip_SYSCTL_SetPinInterrupt(0, SW_LEFT);
	Chip_SYSCTL_SetPinInterrupt(1, SW_RIGHT);

	Chip_PININT_SetPinModeEdge(LPC_PININT,
			SW_LEFT_PININTCH | SW_RIGHT_PININTCH);
	Chip_PININT_EnableIntLow(LPC_PININT,
			SW_LEFT_PININTCH | SW_RIGHT_PININTCH);

	Chip_PININT_ClearIntStatus(LPC_PININT,
			SW_RIGHT_PININTCH | SW_LEFT_PININTCH);

	NVIC_EnableIRQ(SW_LEFT_IRQn);
	NVIC_EnableIRQ(SW_RIGHT_IRQn);
}

void adcInit(void) {
	/* Setup ADC for 12-bit mode and normal power */
	Chip_ADC_Init(LPC_ADC, 0);

	/* Need to do a calibration after initialization and trim */
	Chip_ADC_StartCalibration(LPC_ADC);
	while (!(Chip_ADC_IsCalibrationDone(LPC_ADC))) {}

	/* Setup for maximum ADC clock rate using sycnchronous clocking */
	Chip_ADC_SetClockRate(LPC_ADC, 500000);

	Chip_ADC_SetupSequencer(LPC_ADC, ADC_SEQA_IDX,
							(ADC_SEQ_CTRL_CHANSEL(MoonLander_IO8_ADC) | ADC_SEQ_CTRL_MODE_EOS));

	/* Setup threshold 0 low and high values to about 25% and 75% of max */
	Chip_ADC_SetThrLowValue(LPC_ADC, 0, ((1 * 0xFFF) / 4));
	Chip_ADC_SetThrHighValue(LPC_ADC, 0, ((3 * 0xFFF) / 4));

	/* Clear all pending interrupts */
	Chip_ADC_ClearFlags(LPC_ADC, Chip_ADC_GetFlags(LPC_ADC));

	/* Enable ADC overrun and sequence A completion interrupts */
	Chip_ADC_EnableInt(LPC_ADC, (ADC_INTEN_SEQA_ENABLE | ADC_INTEN_OVRRUN_ENABLE));

	/* Use threshold 0 for ADC channel and enable threshold interrupt mode for
	   channel as crossing */
	Chip_ADC_SelectTH0Channels(LPC_ADC, ADC_THRSEL_CHAN_SEL_THR1(MoonLander_IO8_ADC));
	Chip_ADC_SetThresholdInt(LPC_ADC, MoonLander_IO8_ADC, ADC_INTEN_THCMP_CROSSING);

	/* Enable ADC NVIC interrupt */
	NVIC_EnableIRQ(ADC_SEQA_IRQn);

	/* Enable sequencer */
	Chip_ADC_EnableSequencer(LPC_ADC, ADC_SEQA_IDX);
}

/* Moved this to sysinit to save some space in flash
void StuckI2CHack(void) {
	uint8_t i;
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_DisableFixedPin(SWM_FIXED_I2C0_SCL);


	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO10, PIN_I2CMODE_GPIO);

	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, MoonLander_IO_SCL);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 1);

	for (i=0; i<32; i++) {
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 0);
		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, MoonLander_IO_SCL, 1);
	}

	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO10, PIN_I2CMODE_FASTPLUS);

	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);

	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
}
*/

// Wait for the given number of milliseconds.
void delayms(uint16_t ms) {
	g_delayms_counter = 0;
	while(((uint16_t)g_delayms_counter) < ms) {};
}

void fillScreen(eGFX_PixelState state) {
	eGFX_Point pointa = {0, 0};
	eGFX_Point pointb = {eGFX_BackBuffer.SizeX - 1, eGFX_BackBuffer.SizeY - 1};
	eGFX_Box box = {pointa, pointb};
	eGFX_DrawFilledBox(&eGFX_BackBuffer, &box, state);
}

void SysTick_Handler(void) {
	//static uint32_t blink_counter = 0;
	static uint32_t sample_counter_temp = 0;
	static uint32_t sample_counter_rh = 10;

	static uint32_t sample_counter_mag = 20;
	static int_fp mag_x=0, mag_y=0, mag_z=0;

	static uint32_t sample_counter_range = 30;

	static uint32_t left_sw_hold_counter = 0;
	static uint8_t left_sw_engaged = 0;
	static uint32_t right_sw_hold_counter = 0;
	static uint8_t right_sw_engaged = 0;

	g_delayms_counter += MS_PER_TICK;

	//blink_counter += MS_PER_TICK;
	//if (blink_counter >= BLINK_PERIOD_MS/2) {
	//	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, 0, MoonLander_LED);
	//	blink_counter = 0;
	//}

	sample_counter_temp++;
	if (sample_counter_temp > SAMPLE_PERIOD_TEMP) {
		Plot_AddSample(&g_plot_temp, HTU21D_GetTemp(&g_HTU21D));
		sample_counter_temp = 0;
	}

	sample_counter_rh++;
	if (sample_counter_rh > SAMPLE_PERIOD_RH) {

		Plot_AddSample(&g_plot_rh, HTU21D_GetRH(&g_HTU21D));
		sample_counter_rh = 0;
	}

	sample_counter_mag++;
	if (sample_counter_mag > SAMPLE_PERIOD_MAG) {
		HMC5883L_GetXYZ(&g_HMC5883L, &mag_x, &mag_y, &mag_z);
		Plot_AddSample(&g_plot_mag, mag_z);
		Compass_UpdateXY(&g_compass, mag_x, mag_y);
		sample_counter_mag = 0;
	}


	sample_counter_range++;
	if (sample_counter_range > SAMPLE_PERIOD_RANGE) {

		if (g_adc_sample_ready) {
			g_adc_sample_ready = 0;
			sample_counter_range = 0;
			g_range_raw = ADC_DR_RESULT(Chip_ADC_GetDataReg(LPC_ADC, MoonLander_IO8_ADC));
			Chip_ADC_StartSequencer(LPC_ADC, ADC_SEQA_IDX);
		}
	}

	if (left_sw_engaged) {
		if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, 0, SW_LEFT)) {
			left_sw_engaged = 0;
			left_sw_hold_counter = 0;
		}
		else {
			left_sw_hold_counter += MS_PER_TICK;
			if (left_sw_hold_counter >= SW_OFF_HOLD_TIME_MS) {
				g_go_to_sleep = 1;
				left_sw_hold_counter = 0;
				left_sw_engaged = 0;
			}
		}
	}


	if (right_sw_engaged) {
		if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, 0, SW_RIGHT)) {
			right_sw_engaged = 0;
			right_sw_hold_counter = 0;
		}
		else {
			right_sw_hold_counter += MS_PER_TICK;
			if (right_sw_hold_counter >= SW_OFF_HOLD_TIME_MS) {
				g_go_to_sleep = 1;
				right_sw_hold_counter = 0;
				right_sw_engaged = 0;
			}
		}
	}

	if (g_sw_left_debouncing) {
		left_sw_engaged = 1;
		g_sw_left_debounce_counter += MS_PER_TICK;
		if (g_sw_left_debounce_counter >= SW_DEBOUNCE_MS) {
			g_sw_left_debouncing = 0;
			g_sw_left_debounce_counter = 0;
		}
	}

	if (g_sw_right_debouncing) {
		right_sw_engaged = 1;
		g_sw_right_debounce_counter += MS_PER_TICK;
		if (g_sw_right_debounce_counter >= SW_DEBOUNCE_MS) {
			g_sw_right_debouncing = 0;
			g_sw_right_debounce_counter = 0;
		}
	}

	g_millis_counter += MS_PER_TICK;
}


void SW_LEFT_IRQHandler(void) {
	Chip_PININT_ClearIntStatus(LPC_PININT, SW_LEFT_PININTCH);

	if (!g_sw_left_debouncing) {
		g_left_display = (g_left_display + 1) % N_DISPLAYS;

		// Don't allow same display on both sides:
		if (g_left_display == g_right_display) {
			g_left_display = (g_left_display + 1) % N_DISPLAYS;
		}
		g_sw_left_debouncing = 1;
	}
}

void SW_RIGHT_IRQHandler(void) {
	Chip_PININT_ClearIntStatus(LPC_PININT, SW_RIGHT_PININTCH);

	if (!g_sw_right_debouncing) {
		g_right_display = (g_right_display + 1) % N_DISPLAYS;

		// Don't allow same display on both sides:
		if (g_left_display == g_right_display) {
			g_right_display = (g_right_display + 1) % N_DISPLAYS;
		}
		g_sw_right_debouncing = 1;
	}
}


void ADC_SEQA_IRQHandler(void)
{
	uint32_t pending;

	/* Get pending interrupts */
	pending = Chip_ADC_GetFlags(LPC_ADC);

	/* Sequence A completion interrupt */
	if (pending & ADC_FLAGS_SEQA_INT_MASK) {
		g_adc_sample_ready = 1;
	}

	/* Clear any pending interrupts */
	Chip_ADC_ClearFlags(LPC_ADC, pending);
}


float getRangeCentimeters(void) {
	float v_range;
	v_range = ADC_V_PER_LSB * g_range_raw;
	v_range *= 2; // /2 voltage divider on range output
	return 61.681 * pow(v_range, -1.133);
}


float getRangeInches(void) {
	return getRangeCentimeters() / 2.54;
}


void goToSleep(void) {
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, LCD_BACKLIGHT, 1);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RANGE_POWER_PIN, 0);

	// Give time to release switch:
	delayms(1000);

	// Disable systick timer:
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;

	// Only allow enabled IRQ's to wake us up:
	NVIC_DisableIRQ(ADC_SEQA_IRQn);
	g_go_to_sleep = 0;
	Chip_SYSCTL_EnablePINTWakeup(SW_LEFT_PININT);
	Chip_SYSCTL_EnablePINTWakeup(SW_RIGHT_PININT);
	SCB->SCR &= ~(SCB_SCR_SEVONPEND_Msk);
	Chip_PMU_SleepState(LPC_PMU);
}

void wakeup(void) {
	Chip_SYSCTL_DisablePINTWakeup(SW_LEFT_PININT);
	Chip_SYSCTL_DisablePINTWakeup(SW_RIGHT_PININT);
	g_go_to_sleep = 0;

	Plot_Clear(&g_plot_temp);
	Plot_Clear(&g_plot_rh);

	Plot_Clear(&g_plot_mag);
	Plot_Clear(&g_plot_mag);

	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
	    		     SysTick_CTRL_TICKINT_Msk   |
	    		     SysTick_CTRL_ENABLE_Msk;


	g_sw_right_debouncing = 1;
	g_sw_left_debouncing = 1;
	g_sw_right_debounce_counter = 0;
	g_sw_left_debounce_counter = 0;


	NVIC_EnableIRQ(ADC_SEQA_IRQn);

	Chip_ADC_StartSequencer(LPC_ADC, ADC_SEQA_IDX);

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, LCD_BACKLIGHT, 0);

	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RANGE_POWER_PIN, 1);

	Chip_PININT_ClearIntStatus(LPC_PININT, SW_LEFT_PININTCH);
	Chip_PININT_ClearIntStatus(LPC_PININT, SW_RIGHT_PININTCH);

	NVIC_EnableIRQ(SW_LEFT_IRQn);
	NVIC_EnableIRQ(SW_RIGHT_IRQn);
}

int main(void) {
	char str_buffer[16];
	SystemCoreClockUpdate();

    gpioInit();
    interruptInit();
    adcInit();

	Chip_PMU_GetSleepFlags(LPC_PMU);
	Chip_PMU_ClearSleepFlags(LPC_PMU, PMU_PCON_DPDFLAG);

    Chip_SPI_Init(SPI_PORT);


    SysTick_Config(Chip_Clock_GetSystemClockRate() / TICKRATE_HZ);

    //StuckI2CHack();
    delayms(10);

    MoonLander_I2C_Init(SENSOR_I2C, MOONLANDER_I2C_100K);

    delayms(100);

    // Initialize sensors:
    HTU21D_Init(&g_HTU21D, SENSOR_I2C);
    delayms(10);
    HMC5883L_Init(&g_HMC5883L, SENSOR_I2C);
    delayms(10);

	HMC5883L_SetRange(&g_HMC5883L, HMC5883L_RANGE_2_5);

    eGFX_InitDriver();
    C12832A_Init(&g_C12832A, SPI_PORT, LCD_A0_PIN, LCD_RST_PIN, LCD_SSEL);
    delayms(10);

    Plot_Init(&g_plot_temp, -10, 40, "Temp (C)", 0);
    Plot_Init(&g_plot_rh, 0, 100, "RH", 0);

    Plot_Init(&g_plot_mag, -400, 300, "uTesla", 1);
    Plot_SetSpecialValue(&g_plot_mag, 9000, "OL");

    Compass_Init(&g_compass);

    g_left_display = DISPLAY_TEMP;
    g_right_display = DISPLAY_RH;

    // Straight to sleep on boot:
    g_go_to_sleep = 1;

    // Or not:
    //g_go_to_sleep = 0;
    //wakeup();

    while(1) {

    	fillScreen(0x0);

    	if (g_go_to_sleep) {

    		// Write the empty back buffer to the screen:
    		eGFX_Dump(&eGFX_BackBuffer, &g_C12832A);

    		// Sleep!
    		goToSleep();

    		// Processor has been woken up, restart clocks, etc.:
    		wakeup();
    	}

    	switch (g_left_display) {
    	case DISPLAY_TEMP:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_temp, PLOT_LEFT);
    		break;
    	case DISPLAY_RH:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_rh, PLOT_LEFT);
    		break;
    	case DISPLAY_MAG:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_mag, PLOT_LEFT);
    		break;
    	case DISPLAY_COMPASS:
    		Compass_Draw(&eGFX_BackBuffer, &g_compass, COMPASS_LEFT);
    		break;
    	case DISPLAY_RANGE:
    		eGFX_DrawString(&eGFX_BackBuffer, "Range", 24, 1, &FONT_3_5_1BPP);
    		sprintf(str_buffer, "%0.2f cm", getRangeCentimeters());
    		eGFX_DrawString(&eGFX_BackBuffer, str_buffer, 24, 13, &FONT_3_5_1BPP);
    		break;
    	default:
    		break;
    	}

    	switch (g_right_display) {
    	case DISPLAY_TEMP:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_temp, PLOT_RIGHT);
    		break;
    	case DISPLAY_RH:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_rh, PLOT_RIGHT);
    		break;
    	case DISPLAY_MAG:
    		Plot_Draw(&eGFX_BackBuffer, &g_plot_mag, PLOT_RIGHT);
    		break;
    	case DISPLAY_COMPASS:
    		Compass_Draw(&eGFX_BackBuffer, &g_compass, COMPASS_RIGHT);
    		break;
    	case DISPLAY_RANGE:
    		eGFX_DrawString(&eGFX_BackBuffer, "Range", 88, 1, &FONT_3_5_1BPP);
    		sprintf(str_buffer, "%0.2f cm", getRangeCentimeters());
    		eGFX_DrawString(&eGFX_BackBuffer, str_buffer, 88, 13, &FONT_3_5_1BPP);
    		break;
    	default:
    		break;
    	}


    	eGFX_Dump(&eGFX_BackBuffer, &g_C12832A);

    }
    return 0 ;
}
