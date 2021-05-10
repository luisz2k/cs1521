// COMP1521 19T3 ... lab 1
// cat1: Copy input to output

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main(void) {
    copy (stdin, stdout);
    return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

   	char c; //c = ??
   		
	while (fscanf(input, "%c", &c) == 1) {
		fprintf(output, "%c", c);
	}
	
}
