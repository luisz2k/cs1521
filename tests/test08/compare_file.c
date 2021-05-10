#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    int diff = 0;
    int ch1 = 0; 
    int ch2 = 0;
    int count = 0;

    while (ch1 != EOF && ch2 != EOF) {
        ch1 = fgetc(fp1); 
        ch2 = fgetc(fp2); 
        if (ch1 == EOF && ch2 != EOF) {
            printf("EOF on %s\n", argv[1]);
            diff = 1;
            break;
        } else if (ch2 == EOF && ch1 != EOF) {
            printf("EOF on %s\n", argv[2]);
            diff = 1;
            break;
        }
        if (ch1 != ch2) {
            printf("Files differ at byte %d\n", count);
            diff = 1;
            break;
        }
        count++;
    }

    if (diff == 0) {
        printf("Files are identical\n");
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}

    
