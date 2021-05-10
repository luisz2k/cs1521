#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {

	// e.g. 1 0000 0000 1111 1111 1111 1111 1111 111
	uint32_t exp = (f >> 23) & 0b011111111;
	
    return exp; 

}
