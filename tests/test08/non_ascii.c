#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int i = 0;
    int c = 0;
    int isAscii = 1;
    FILE *fp = fopen(argv[1], "r");
    while (c != EOF) {
        c = fgetc(fp);
        if (c > 127) {
            printf("%s: byte %d is non-ASCII\n", argv[1], i);
            isAscii = 0;
        }
        i++;
    }
    if (isAscii) {
        printf("%s is all ASCII\n");
    }
    fclose(fp);
    return 0;
}