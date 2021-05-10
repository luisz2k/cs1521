#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("Failed to open file. Exiting.\n");
        return 1;
    }

    int c = 2;
    while (c < argc) {
        int num = atoi(argv[c]);
        fputc(num, fp);
        c++;
    }

    fclose(fp);
    return 0;
}

