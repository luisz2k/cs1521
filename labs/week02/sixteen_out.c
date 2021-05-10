//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);
int get_nth_bit(int value, int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
	
	char *ptr = malloc(100);	// allocate storage for string
	int j = 0;
	
	for (int i = N_BITS - 1; i >= 0; i--) {
		int bit = (value >> i) & 1;
		if (bit == 1) {
			ptr[j] = '1';
		} else if (bit == 0) {
			ptr[j] = '0';
		}
		j++;
	}
	ptr[16] = '\0';
	return ptr;
}

