// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//

float_components_t float_bits(uint32_t f) {

	float_components_t my_float;
	
	// extracting sign bit
	if (((f >> 31) & 0x1) == 0x1) {
		my_float.sign = 0x1;
	} else if (((f >> 31) & 0x1) == 0x0) {
		my_float.sign = 0x0;
	}
	// extracing exponent bits 
	my_float.exponent = (f >> 23) & 0b011111111;
	
	// extracting fraction bits
	my_float.fraction = f & 0x7FFFFF;
    
    return my_float;
}


// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {

    if ((f.fraction != 0) && (f.exponent == 0xFF)) {
    	return 1;
	}
    return 0;
}


// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {

    if ((f.fraction == 0) && (f.exponent == 0xFF) && (f.sign == 0)) {
    	return 1;
	}
    return 0;
}


// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {

    if ((f.fraction == 0) && (f.exponent == 0xFF) && (f.sign == 1)) {
    	return 1;
	}
    return 0;
}


// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {

    if ((f.fraction == 0) && (f.exponent == 0)) {
    	return 1;
	}
    return 0;
}


uint32_t float_2048(uint32_t f) {

	uint32_t result = 0;
	float_components_t fcomp = float_bits(f);
	
	if (is_zero(fcomp) && (fcomp.sign == 0)) {
		return 0;
	}
	
	if (is_zero(fcomp) && (fcomp.sign == 1)) {
		return 0b10000000000000000000000000000000;
	}
	
	if (is_nan(fcomp)) {
		return f;	// return unchanged
	}
	
	fcomp.exponent = fcomp.exponent + 11;	// multiply by 2048
	result = (fcomp.sign << 31) | (fcomp.exponent << 23) | fcomp.fraction;	// combine the bits
	
	if (is_positive_infinity(fcomp)) {
		result = 0x7F800000;	// e.g. set to 0 1111 1111 00000000...
	} else if (is_negative_infinity(fcomp)) {
		result = 0xFF800000;	// e.g. set to 1 1111 1111 00000000...
	}
	
	if ((fcomp.exponent > 255) && (fcomp.sign == 0)) {	// if exponent is too large and f is +ve
		result = 0x7F800000;
	}
	
	if ((fcomp.exponent > 255) && (fcomp.sign == 1)) {
		result = 0xFF800000;
	}
	
	return result;
}

