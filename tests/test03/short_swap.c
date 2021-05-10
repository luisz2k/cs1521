// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {

    uint16_t new1 = (value & 0b1111111100000000) >> 8;
    uint16_t new2 = (value & 0b0000000011111111) << 8;
    
    uint16_t new = new1 | new2;

    return new;
}
