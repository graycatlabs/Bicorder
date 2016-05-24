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
 * @brief A library for generating a compass display on the Bicorder.
 */


#ifndef BICORDER_COMPASS_H_
#define BICORDER_COMPASS_H_

#include "gcl-fixedpoint.h"
#include "eGFX_DataTypes.h"

// Declination in radians:
//#define COMPASS_DECLINATION (-15) // VT
#define COMPASS_DECLINATION (15) // San Fran


/**
 * Compass object
 */
typedef struct {
	int_fp mag_x;
	int_fp mag_y;
} uCorder_Compass;

/**
 * @brief Initializes the given compass object
 *
 * @param compass The #uCorder_Compass object to initialize
 */
void Compass_Init(uCorder_Compass *compass);

/**
 * @brief Sets the current X and Y magnetic field strength of the given
 *        compass object
 *
 * Fixed point values are used for the field strength because this routine
 * was meant to be called from an interrupt handler. In
 * #Compass_CalculateHeading they are converted to floats for the calculation.
 *
 * @param compass An initialized #uCorder_Compass object
 * @param x The current X axis field strength
 * @param y The current Y axis field strength
 */
void Compass_UpdateXY(uCorder_Compass *compass, int_fp x, int_fp y);

/**
 * @brief Calculates and returns the current compass heading in degrees
 *
 * This involves floating point calculations, so it shouldn't be called from
 * an interrup handler.
 *
 * @param compass An initialized #uCorder_Compass object
 *
 * @return Returns the current heading in degrees
 */
uint16_t Compass_CalculateHeading(uCorder_Compass *compass);

/**
 * Compass directions as returned by #Compass_HeadingToDirection
 */
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

/**
 * @brief Returns the current compass direction from the given heading.
 *
 * @param heading Heading in degrees
 *
 * @return Returns a compass direction.
 */
Compass_direction Compass_HeadingToDirection(uint16_t heading);

/**
 * Passed to #Compass_Draw to set which side of screen compass is displayed on
 */
typedef enum {
	COMPASS_LEFT, ///< Display compass on left side of screen
	COMPASS_RIGHT ///< Display compass on right side of screen
} Compass_side;

/**
 * @brief Returns the current compass direction from the given heading,
 *
 * @param heading Heading in degrees
 *
 * @return Returns a compass direction.
 */
void Compass_Draw(eGFX_ImagePlane *image, uCorder_Compass *compass,
				  Compass_side side);

#endif /* BICORDER_COMPASS_H_ */
