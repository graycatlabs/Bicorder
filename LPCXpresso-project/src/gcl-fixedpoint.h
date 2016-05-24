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
 * @file gcl-fixedpoint.h
 * @author Alex Hiam - <alex@graycat.io>
 *
 * @brief Basic 32- and 64-bit signed fixed point math library.
 */

#ifndef GCL_FIXEDPOINT_H_
#define GCL_FIXEDPOINT_H_

#include <stdint.h>

typedef int32_t int_fp;  ///< 32-bit fixed point number
typedef int64_t long_fp; ///< 64-bit fixed point number

/**
 * Number of bits used to store the fraction. Defaults to 8, but can
 * be changed using gcc's -D flag (e.g. `-DFP_FRACT_BITS=10`)
 */
#ifndef FP_FRACT_BITS
#define FP_FRACT_BITS 8
#endif

/**
 * convert an int to a 32-bit #int_fp
 */
#define FP_INT(X) ((int_fp) (X * (1<<FP_FRACT_BITS)))
/**
 * convert an int to a 64-bit #long_fp
 */
#define FP_LONG(X) ((long_fp) (X * (1<<FP_FRACT_BITS)))

/**
 * convert an #int_fp from fixed point to a 32-bit int
 */
#define FP_TO_INT(X) ((int32_t) X * (1.0 / (1<<FP_FRACT_BITS)))

/**
 * convert an #int_fp from fixed point to a 64-bit int
 */
#define FP_TO_LONG(X) ((int64_t) X * (1.0 / (1<<FP_FRACT_BITS)))

/**
 * convert an #int_fp from fixed point to a float
 */
#define FP_TO_FLOAT(X) (((float) X) * (1.0 / (1<<FP_FRACT_BITS)))

/**
 * @brief 64-bit fixed point multiplication of two #long_fp numbers
 *
 * @return Returns the #long_fp product of the given two numbers
 */
static inline long_fp long_fp_mul(long_fp a, long_fp b) {
	return (a * b) >> FP_FRACT_BITS;
}

/**
 * @brief 64-bit fixed point division of two #long_fp numbers
 *
 * @param a The dividend
 * @param a The divisor
 *
 * @return Returns the #long_fp quotient of the given two numbers
 */
static inline long_fp long_fp_div(long_fp a, long_fp b) {
	return (a << FP_FRACT_BITS) / b;
}

/**
 * @brief 32-bit fixed point multiplication of two #int_fp numbers
 *
 * Uses 64-bit multiplication for intermediate steps, so as long as the
 * result fits in 32 bits there shouldn't be any overflow
 *
 * @return Returns the #int_fp product of the given two numbers
 */
static inline int_fp int_fp_mul(int_fp a, int_fp b) {
	return (int_fp) long_fp_mul((long_fp) a, (long_fp) b);
}

/**
 * @brief 32-bit fixed point division of two #int_fp numbers
 *
 * Uses 64-bit operations for intermediate steps, so as long as the
 * result fits in 32 bits there shouldn't be any overflow
 *
 * @param a The dividend
 * @param a The divisor
 *
 * @return Returns the #int_fp quotient of the given two numbers
 */
static inline int_fp int_fp_div(int_fp a, int_fp b) {
	return (int_fp) long_fp_div((long_fp) a, (long_fp) b);
}

#endif /* GCL_FIXEDPOINT_H_ */
