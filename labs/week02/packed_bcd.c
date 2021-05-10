#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    uint32_t mask = 0xF;
    int multiplier = 1;
    int dec = 0;
    int sum = 0;
    
    while (packed_bcd_value != 00000000) {
    	printf("New Iteration:\n");
    	
    	dec = (packed_bcd_value & mask) * multiplier;
		printf("dec = %d ( (%x & %x) * %d )\n", dec, packed_bcd_value, mask, multiplier);
		
    	packed_bcd_value = packed_bcd_value >> 4;
		printf("packed bcd value = %x (packed >> 4))\n", packed_bcd_value);
		
    	sum += dec;   	
    	printf("sum = %d (sum += %d)\n", sum, dec);
    	
		multiplier *= 10;
	}
	return sum;
}
