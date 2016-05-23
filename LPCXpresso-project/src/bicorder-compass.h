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
 * @file bicorder-compass.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief A library for generating generic live plots on the Bicorder.
 */


#ifndef BICORDER_COMPASS_H_
#define BICORDER_COMPASS_H_

#include "gcl-fixedpoint.h"
#include "eGFX_DataTypes.h"

// Declination in radians:
//#define COMPASS_DECLINATION (-15) // VT
#define COMPASS_DECLINATION (15) // San Fran

typedef struct {
	int_fp mag_x;
	int_fp mag_y;
} uCorder_Compass;

void Compass_Init(uCorder_Compass *compass);

void Compass_UpdateXY(uCorder_Compass *compass, int_fp x, int_fp y);

uint16_t Compass_CalculateHeading(uCorder_Compass *compass);

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
Compass_direction Compass_HeadingToDirection(uint16_t heading);


typedef enum {
	COMPASS_LEFT,
	COMPASS_RIGHT
} Compass_side;
void Compass_Draw(eGFX_ImagePlane *image, uCorder_Compass *compass,
				  Compass_side side);

#endif /* BICORDER_COMPASS_H_ */
