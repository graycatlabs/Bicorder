/*
 * bicorder-plotter.h
 *
 *  Created on: May 12, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#ifndef BICORDER_PLOTTER_H_
#define BICORDER_PLOTTER_H_

#include "eGFX_DataTypes.h"

#define PLOT_WIDTH  40
#define PLOT_HEIGHT 20

#define PLOT_MARGIN_LEFT    20
#define PLOT_MARGIN_BOTTOM  3

#define PLOT_GRATICLE_WIDTH 2
#define PLOT_N_GRATICLE_X   5
#define PLOT_N_GRATICLE_Y   5


#define PLOT_LABEL_MAX_LEN             10
#define PLOT_SPECIAL_VALUE_MSG_MAX_LEN 5

typedef struct {
	int32_t y_min;
	int32_t y_max;
	int32_t data[PLOT_WIDTH];
	uint8_t start_index;
	char label[PLOT_LABEL_MAX_LEN+1];
	uint8_t special_value_en;
	int32_t special_value;
	char special_value_msg[PLOT_SPECIAL_VALUE_MSG_MAX_LEN+1];
	uint8_t is_fixed_point;
} uCorder_plot;


void Plot_Init(uCorder_plot *plot, int32_t y_min, int32_t y_max,
			   char *label, uint8_t is_fixed_point);

void Plot_SetSpecialValue(uCorder_plot *plot, int32_t special_value,
						  char *msg);

void Plot_Clear(uCorder_plot *plot);

void Plot_AddSample(uCorder_plot *plot, int32_t sample);

typedef enum {
	PLOT_LEFT,
	PLOT_RIGHT
} Plot_side;
void Plot_Draw(eGFX_ImagePlane *image, uCorder_plot *plot, Plot_side side);

#endif
