#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Wrong usage\n");
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed to open file. Exiting.\n");
        return 1;
    }

    long byte_count = 0;
    int c = 0;
    while (c != EOF) {
        c = fgetc(fp);
        if (c == 0xffffffff)
            break;
        if (isprint(c) != 0) {
            printf("byte %4ld: %3d 0x%02x '%c'\n", byte_count, c, c, c);
        }
        else {
            printf("byte %4ld: %3d 0x%02x\n", byte_count, c, c);
        }
        // if (c == '\n') {
        //     continue;
        // }
        byte_count++;
    }

    fclose(fp);
    return 0;
}

