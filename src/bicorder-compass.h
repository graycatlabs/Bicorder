/*
 * bicorder-compass.h
 *
 *  Created on: May 15, 2016
 *      Author: Alex Hiam <alex@graycat.io>
 *		Copyright (c) 2016 - Gray Cat Labs
 */

#ifndef BICORDER_COMPASS_H_
#define BICORDER_COMPASS_H_

#include "gcl-fixedpoint.h"
#include "eGFX_DataTypes.h"

// Declination in radians:
//#define COMPASS_DECLINATION (-0.2618) // VT
#define COMPASS_DECLINATION (0.2618) // San Fran

typedef struct {
	int_fp mag_x;
	int_fp mag_y;
} uCorder_Compass;

void Compass_Init(uCorder_Compass *compass);

void Compass_UpdateXY(uCorder_Compass *compass, int_fp x, int_fp y);

double Compass_CalculateHeading(uCorder_Compass *compass);

uint16_t Compass_RadiansToDegrees(double radians);

typedef enum {
	COMPASS_N,
	COMPASS_NNE,
	COMPASS_NE,
	COMPASS_ENE,
	COMPASS_E,
	COMPASS_ESE,
	COMPASS_SE,
	COMPASS_SSE,
	COMPASS_S,
	COMPASS_SSW,
	COMPASS_SW,
	COMPASS_WSW,
	COMPASS_W,
	COMPASS_WNW,
	COMPASS_NW,
	COMPASS_NNW
} Compass_direction;
Compass_direction Compass_RadiansToDirection(double radians);


uint16_t Compass_CalculateHeadingDegrees(uCorder_Compass *compass);

typedef enum {
	COMPASS_LEFT,
	COMPASS_RIGHT
} Compass_side;
void Compass_Draw(eGFX_ImagePlane *image, uCorder_Compass *compass,
				  Compass_side side);

#endif /* BICORDER_COMPASS_H_ */
