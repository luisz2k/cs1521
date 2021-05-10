#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Wrong usage\n");
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("Failed to open file. Exiting.\n");
        return 1;
    }

    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    while (low <= high) {
        fprintf(fp, "%d\n", low);
        low++;
    }

    fclose(fp);
    return 0;
}

