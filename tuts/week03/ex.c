#include <stdio.h>
#include <stdlib.h>

int isPositive(int32_t x) {
   return !((x & (1 << 31)) | !x);
}

int main (void) {

	int32_t isPos = isPositive(5);
	printf("%d\n", isPos);
	isPos = isPositive(-5);
	printf("%d\n", isPos);
	
}
	
	
