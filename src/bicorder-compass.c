/*
 * bicorder-compass.c
 *
 *  Created on: May 15, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#include "bicorder-compass.h"

#include "gcl-fixedpoint.h"
#include "eGFX.h"
#include "eGFX_DataTypes.h"
#include "Fonts/FONT_3_5_1BPP.h"
#include <string.h>
#include <math.h>

void Compass_Init(uCorder_Compass *compass) {
	compass->mag_x = 0;
	compass->mag_y = 0;
}

void Compass_UpdateXY(uCorder_Compass *compass, int_fp x, int_fp y) {
	compass->mag_x = x;
	compass->mag_y = y;
}

double Compass_CalculateHeading(uCorder_Compass *compass) {
	int32_t x_utesla, y_utesla;
	double radians;
	x_utesla = FP_TO_INT(compass->mag_x);
	y_utesla = FP_TO_INT(compass->mag_y);
	radians = atan2((double) y_utesla, (double) x_utesla);
	return radians + COMPASS_DECLINATION;
}

uint16_t Compass_RadiansToDegrees(double radians) {
	return (uint16_t) (57.2958 * radians) + COMPASS_DECLINATION;
}

Compass_direction Compass_RadiansToDirection(double radians) {
	uint16_t heading;
	heading = Compass_RadiansToDegrees(radians);
	if (heading <= 11) return COMPASS_N;
	if (heading <= 34) return COMPASS_NNE;
	if (heading <= 56) return COMPASS_NE;
	if (heading <= 79) return COMPASS_ENE;
	if (heading <= 101) return COMPASS_E;
	if (heading <= 124) return COMPASS_ESE;
	if (heading <= 146) return COMPASS_SE;
	if (heading <= 169) return COMPASS_SSE;
	if (heading <= 191) return COMPASS_S;
	if (heading <= 214) return COMPASS_SSW;
	if (heading <= 236) return COMPASS_SW;
	if (heading <= 259) return COMPASS_WSW;
	if (heading <= 281) return COMPASS_W;
	if (heading <= 304) return COMPASS_WNW;
	if (heading <= 326) return COMPASS_NW;
	if (heading <= 349) return COMPASS_NNW;
	return COMPASS_N;
}


int8_t north_offset_x[16] = {
	12, 11, 8, 5, 0, -4, -7, -10, -11, -10, -7, -4, 0, 5, 8, 11
};

int8_t north_offset_y[16] = {
	0, 5, 8, 11, 12, 11, 8, 5, 0, -4, -7, -10, -11, -10, -7, -4
};

int8_t south_offset_x[16] = {
	-4, -4, -3, -1, 0, 2, 4, 5, 5, 5, 4, 2, 0, -1, -3, -4
};

int8_t south_offset_y[16] = {
	0, -1, -3, -4, -4, -4, -3, -1, 0, 2, 4, 5, 5, 5, 4, 2
};

int8_t base_offset_x[16] = {
	0, 2, 3, 4, 4, 4, 3, 2, 0, -1, -2, -3, -3, -3, -2, -1
};

int8_t base_offset_y[16] = {
	-3, -3, -2, -1, 0, 2, 3, 4, 4, 4, 3, 2, 0, -1, -2, -3
};


void Compass_Draw(eGFX_ImagePlane *image, uCorder_Compass *compass,
				  Compass_side side) {
	uint8_t center_x, center_y, north_x, north_y, south_x, south_y;
	uint8_t base_x1, base_y1, base_x2, base_y2;
	Compass_direction direction;
	double heading;
	heading = Compass_CalculateHeading(compass);

	if	(side == COMPASS_LEFT) center_x = 31;
	else center_x = 96;
	center_y = 19;

	eGFX_DrawString(image, "Compass", center_x - 14, 1, &FONT_3_5_1BPP);
	direction = Compass_RadiansToDirection(heading);
	north_x = center_x + north_offset_x[direction];
	north_y = center_y - north_offset_y[direction];

	south_x = center_x + south_offset_x[direction];
	south_y = center_y - south_offset_y[direction];

	base_x1 = center_x + base_offset_x[direction];
	base_y1 = center_y - base_offset_y[direction];

	base_x2 = center_x - base_offset_x[direction];
	base_y2 = center_y + base_offset_y[direction];

	eGFX_DrawLine(image, base_x1, base_y1, north_x, north_y, 1);
	eGFX_DrawLine(image, base_x2, base_y2, north_x, north_y, 1);

	eGFX_DrawLine(image, base_x1, base_y1, south_x, south_y, 1);
	eGFX_DrawLine(image, base_x2, base_y2, south_x, south_y, 1);

	eGFX_PutPixel(image, center_x, center_y, 1);
	//eGFX_DrawLine(image, center_x, center_y, point_x, point_y, 1);


	//eGFX_DrawString(image, heading_str, 70, 10, &FONT_3_5_1BPP);
}
