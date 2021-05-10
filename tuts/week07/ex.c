#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// Ensure correct input has been received
    if (argc != 2) {
        printf("Usage: ./%s somefile\n", argv[0]);
    }

    // Try to open the file
    FILE *file = fopen(argv[1], "r");

    // Handle failure to open file
    if (file == NULL) {
        // printf("Failed to open file. Exiting.\n");
        perror("Failed to open file. Exiting.\n");
        return 1;
    }

    // Print first line of file using fgetc and fputc
    int c;
    c = fgetc(file);
    while (c != EOF) {
        fputc(c, stdout);
        c = fgetc(file);
    }

    // Close the file
    printf("\n");
    fclose(file);

    return 0;
}