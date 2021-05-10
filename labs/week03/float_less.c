// Compare 2 floats using bit operations only

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

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
	
	uint32_t res = 0;
    float_components_t float1 = float_bits(bits1);
    float_components_t float2 = float_bits(bits2);

	// check for nan
    if (is_nan(float1) || is_nan(float2)) {
        return 0;	
    }

    if (float1.sign == 0 && float2.sign == 1) {
        res = 0;	// float1 positive and float2 negative
    } else if (float1.sign == 1 && float2.sign == 0) {
        res = 1;	// float1 negative and float2 positive
    } else if (float1.sign == 0 && float2.sign == 0) {	// both positive
        if (float1.exponent > float2.exponent) {
            res = 0;	// both positive, float1 > float2 (exps)
        } else if (float1.exponent < float2.exponent) {
            res = 1;	// both positive, float1 < float2 (exps)
        } else {	// both positive, both exponents equal
            if (float1.fraction > float2.fraction) {
                res = 0;	// float1 > float2 (fracs)
            } else if (float1.fraction < float2.fraction) {
                res = 1;	// float 1 < float2 (fracs)
            }
        }
    }
    else {	// both negative
        if (float1.exponent > float2.exponent) {
            res = 1;	// float1 < float2 (exps)
        } else if (float1.exponent < float2.exponent) {
            res = 0;	// float1 > float2 (exps)
        } else {	// both negative, both exponents equal
            if (float1.fraction > float2.fraction) {
                res = 1;	// float1 > float2 (fracs)
            } else if (float1.fraction < float2.fraction) {
                res = 0;	// float1 < float2 (fracs)
            }
        }
    }
    return res;
}
