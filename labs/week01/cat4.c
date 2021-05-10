// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {
	
	FILE *fp;
	
	if (argc == 1) {
    	copy (stdin, stdout);
	} else {
		for (int i = 1; i < argc; i++) {
			fp = fopen (argv[i], "r");
			if (fp == NULL) {
				printf("Can't read %s\n", argv[i]);
			} else {
				copy (fp, stdout);
				fclose(fp);
			}
	 	}
	}
    return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

	char c[BUFSIZ];
	while ((fgets(c, BUFSIZ, input)) != NULL) {
		fputs(c, output);
	}
}
