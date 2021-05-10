#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {

	uint16_t right_bit = 0;
	uint16_t left_bit = 0;

	if (n_rotations >= 0) {
		for (int i = 0; i < n_rotations; i++) {
			if (bits >> 15 == 1) {
				right_bit = 1;
			}
			if (bits >> 15 == 0) {
				right_bit = 0;
			}
			bits = (bits << 1) | right_bit;
		}
	} else {
		for (int j = 0; j > n_rotations; j--) {
			if ((bits & 1) == 1) {
				left_bit = 0b1000000000000000;
			}
			if ((bits & 1) == 0) {
				left_bit = 0;
			}
			bits = (bits >> 1) | left_bit;
		}
	}

    return bits; 

}

