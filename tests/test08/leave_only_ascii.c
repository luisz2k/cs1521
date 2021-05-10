#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int ch1 = 0;
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen("temp.txt", "w+");

    while (ch1 != EOF) {
        ch1 = fgetc(fp1);
        if (ch1 > 127 || ch1 == '\x82' || ch1 == '\xba') {
            continue;
        }
        fprintf(fp2, "%c", ch1);
    }

    while (ch1 != EOF) {
        ch1 = fgetc(fp2);
        fprintf(fp1, "%c", ch1);
    }

    fclose(fp1);
    fclose(fp2);

}