/*
 * bicorder-plotter.c
 *
 *  Created on: May 12, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#include "bicorder-plotter.h"

#include "gcl-fixedpoint.h"
#include "eGFX.h"
#include "eGFX_DataTypes.h"
#include "Fonts/FONT_3_5_1BPP.h"
#include <string.h>
#include <stdio.h>


void Plot_Init(uCorder_plot *plot, int32_t y_min, int32_t y_max,
			   char *label, uint8_t is_fixed_point) {
	uint8_t i;
	plot->y_min = y_min;
	plot->y_max = y_max;
	for (i=0; i<PLOT_WIDTH; i++) plot->data[i] = 0;
	plot->start_index = PLOT_WIDTH - 1;
	strncpy(plot->label, label, PLOT_LABEL_MAX_LEN);
	plot->label[PLOT_LABEL_MAX_LEN] = 0;
	plot->special_value_en = 0;
	plot->is_fixed_point = is_fixed_point;
}

void Plot_SetSpecialValue(uCorder_plot *plot, int32_t special_value,
						  char *msg) {
	strncpy(plot->special_value_msg, msg, PLOT_SPECIAL_VALUE_MSG_MAX_LEN);
	plot->special_value = special_value;
	plot->special_value_en = 1;
}

void Plot_AddSample(uCorder_plot *plot, int32_t sample) {
	plot->data[plot->start_index] = sample;
	plot->start_index = (plot->start_index + 1) % PLOT_WIDTH;
}


void Plot_Clear(uCorder_plot *plot) {
	uint8_t i;
	for (i=0; i<PLOT_WIDTH; i++) plot->data[i] = 0;
}

uint8_t Plot_ValueToCoord(int32_t value, int32_t y_min, int32_t y_max) {
	int64_t new_val;
	// Map to [0, PLOT_HEIGHT]:
	new_val = (uint64_t) value;
	new_val -= y_min;
	new_val *= PLOT_HEIGHT;
	new_val /= y_max - y_min;
	// truncate:
	if (new_val < 0) new_val = 0;
	else if (new_val > PLOT_HEIGHT) new_val = PLOT_HEIGHT;
	return (uint8_t) new_val;
}

void Plot_Draw(eGFX_ImagePlane *image, uCorder_plot *plot, Plot_side side) {
	uint8_t sample, data_i, i, value, value_y;
	uint8_t origin_x, origin_y, y_bottom, graticle, graticle_inc;
	int16_t str_width;
	int32_t raw_value;
	int8_t str_x;
	char str_buffer[16];

	if (side == PLOT_LEFT) {
		origin_x = PLOT_MARGIN_LEFT;
	}

	else {
		origin_x = 63 + PLOT_MARGIN_LEFT;
	}

	y_bottom = 31 - PLOT_MARGIN_BOTTOM;

	if (plot->y_min < 0) {
		origin_y = y_bottom - Plot_ValueToCoord(0, plot->y_min, plot->y_max);
	}
	else origin_y = y_bottom;

	eGFX_DrawHline(image, origin_x, origin_x + PLOT_WIDTH - 1, origin_y, 1);
	eGFX_DrawVline(image, y_bottom, y_bottom - PLOT_HEIGHT + 1, origin_x, 1);

	graticle_inc = (PLOT_WIDTH) / PLOT_N_GRATICLE_X;
	graticle = origin_x + graticle_inc;
	for (i=0; i<PLOT_N_GRATICLE_X; i++) {
		eGFX_DrawVline(image, origin_y, origin_y + PLOT_GRATICLE_WIDTH,
					   graticle, 1);
		graticle += graticle_inc;
	}
	graticle_inc = (PLOT_HEIGHT) / PLOT_N_GRATICLE_Y;
	graticle = y_bottom - graticle_inc;
	for (i=0; i<PLOT_N_GRATICLE_Y; i++) {
		eGFX_DrawHline(image, origin_x, origin_x - PLOT_GRATICLE_WIDTH,
					   graticle, 1);
		graticle -= graticle_inc;
	}


	sprintf(str_buffer, "%d", plot->y_min);
	str_width = eGFX_GetStringWidth(str_buffer, &FONT_3_5_1BPP);
	str_x = origin_x - str_width - PLOT_GRATICLE_WIDTH - 1;
	if (str_x < (origin_x - PLOT_MARGIN_LEFT)) {
		str_x = origin_x - PLOT_MARGIN_LEFT;
	}
	if (str_width > PLOT_MARGIN_LEFT) str_width = PLOT_MARGIN_LEFT;
	eGFX_DrawString(image, str_buffer, str_x, y_bottom - 2, &FONT_3_5_1BPP);

	sprintf(str_buffer, "%d", plot->y_max);
	str_width = eGFX_GetStringWidth(str_buffer, &FONT_3_5_1BPP);
	str_x = origin_x - str_width - PLOT_GRATICLE_WIDTH - 1;
	if (str_x < (origin_x - PLOT_MARGIN_LEFT)) {
		str_x = origin_x - PLOT_MARGIN_LEFT;
	}
	eGFX_DrawString(image, str_buffer, str_x, y_bottom - PLOT_HEIGHT - 2,
					&FONT_3_5_1BPP);

	eGFX_DrawString(image, plot->label, origin_x+2,
					y_bottom - PLOT_HEIGHT - 6, &FONT_3_5_1BPP);

	data_i = plot->start_index;

	for (sample=0; sample<PLOT_WIDTH; sample++) {
		raw_value = plot->data[data_i];
		if (plot->is_fixed_point) {
			raw_value = FP_TO_INT(raw_value);
		}

		if (plot->special_value_en && raw_value == plot->special_value) {
			// Data point won't be visible here:
			value = origin_y + y_bottom;
		}
		else {
			value = Plot_ValueToCoord(raw_value, plot->y_min, plot->y_max);
		}

		eGFX_PutPixel(image, origin_x + sample, y_bottom - value, 1);

		data_i = (data_i + 1) % PLOT_WIDTH;
	}

	if (plot->special_value_en && raw_value == plot->special_value) {
		strncpy(str_buffer, plot->special_value_msg, PLOT_SPECIAL_VALUE_MSG_MAX_LEN);
	}
	else {
		sprintf(str_buffer, "%d", raw_value);
	}
	str_width = eGFX_GetStringWidth(str_buffer, &FONT_3_5_1BPP);

	if (value > (y_bottom - PLOT_HEIGHT + 5)) {
		if (origin_y != y_bottom && origin_y > y_bottom - 5) {
			value_y = origin_y - 6;
		}
		else value_y = y_bottom - 6;
	}
	else {
		value_y = y_bottom - PLOT_HEIGHT;
	}
		eGFX_DrawString(image, str_buffer, origin_x + PLOT_WIDTH - str_width,
						value_y, &FONT_3_5_1BPP);
}
