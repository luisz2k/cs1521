#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {

    uint32_t opcode = 0;
    uint32_t mask = 0b11111;

    opcode = (d & mask) << 11 | (t & mask) << 16 | (s & mask) << 21 | 0b100000;

    return opcode;

}
