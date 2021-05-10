#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {

	// e.g. 1 0000 0000 1111 1111 1111 1111 1111 111
	uint32_t new = 0;
	
	if (f >> 31 == 1) {
		new = f & 0b01111111111111111111111111111111;
	}
	if (f >> 31 == 0) {
		new = f | 0b10000000000000000000000000000000;
	}
	
    return new; 

}
