// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
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
