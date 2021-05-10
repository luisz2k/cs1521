// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {

    int count = 0;
    uint64_t mask = 1;
    
    while (value != 0) {
    	if ((value & mask) == 1) {
    		count++;
		}
		value = value >> 1;
	}

    return count;
}
