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

// 32- and 64-bit fixed point types
typedef int32_t int_fp;
typedef int64_t long_fp;

#ifndef FP_FRACT_BITS
#define FP_FRACT_BITS 8
#endif

// int to fixed point conversions
#define FP_INT(X) ((int_fp) (X * (1<<FP_FRACT_BITS)))
#define FP_LONG(X) ((long_fp) (X * (1<<FP_FRACT_BITS)))

// Fixed point to int & float conversions
#define FP_TO_INT(X) ((int) X * (1.0 / (1<<FP_FRACT_BITS)))
#define FP_TO_FLOAT(X) (((float) X) * (1.0 / (1<<FP_FRACT_BITS)))

// 64-bit fixed point multiplication
static inline long_fp long_fp_mul(long_fp a, long_fp b) {
	return (a * b) >> FP_FRACT_BITS;
}

// 64-bit fixed point division
static inline long_fp long_fp_div(long_fp a, long_fp b) {
	return (a << FP_FRACT_BITS) / b;
}

// 32-bit fixed point multiplication. Uses 64-bit multiplication for
// Intermediate steps, so as long as the result fits in 32 bits there
// shouldn't be any overflow
static inline int_fp int_fp_mul(int_fp a, int_fp b) {
	return (int_fp) long_fp_mul((long_fp) a, (long_fp) b);
}

// 32-bit fixed point division. Uses 64-bit multiplication for
// Intermediate steps, so as long as the result fits in 32 bits there
// shouldn't be any overflow
static inline int_fp int_fp_div(int_fp a, int_fp b) {
	return (int_fp) long_fp_div((long_fp) a, (long_fp) b);
}

#endif /* GCL_FIXEDPOINT_H_ */
