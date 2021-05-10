#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int bcd(int bcd_value);
int get_nth_bit(int value, int n);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // convert bcd_value to binary 				e.g. 258 -> 0000000100000010
	// divide binary value into two bytes		unpacked -> 000000001  00000010
    // convert each byte back to int			convert  -> 1 2 i.e. 12
    
    // convert to binary:
    
    char *bits = malloc(100);	// allocate storage for string
	int j = 0;
	
	int byte_1 = 0;
	int byte_2 = 0;
	uint16_t mask1 = 1;
	uint16_t mask2 = 1;
	char s1[20];
	char s2[20];
	
	for (int i = 15; i >= 0; i--) {
		int bit = (bcd_value >> i) & 1;
		if (bit == 1) {
			bits[j] = '1';
		} else if (bit == 0) {
			bits[j] = '0';
		}
		j++;
	}
	bits[16] = '\0';
	//printf("bits = %s\n", bits);
	
	for (int k = 7; k >= 0; k--) {
		if (bits[k] == '1') {
			byte_1 = byte_1 | mask1;
		}
		mask1 = mask1 << 1;
	}
	
	//printf("byte 1 = %d\n", byte_1);
	
	for (int l = 15; l >= 8; l--) {
		if (bits[l] == '1') {
			byte_2 = byte_2 | mask2;
		}
		mask2 = mask2 << 1;
	}
	
	//printf("byte 2 = %d\n", byte_2);
	
	sprintf(s1, "%d", byte_1);
	sprintf(s2, "%d", byte_2);
	strcat(s1, s2);
	int value = atoi(s1);
	
    return value;
}

// this code is from the lecture
int get_nth_bit(int value, int n) {
    return (value >> n) & 1;
}

