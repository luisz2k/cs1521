#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void swap(int * array);

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    int buffer[3] = {0};
    int length = 0;
    int next_char;
    while((next_char = fgetc(fp)) != EOF){
        if(!isprint(next_char)){
            if(length >= 4){
                putchar(buffer[0]);
                putchar(buffer[1]);
                putchar(buffer[2]);
                putchar('\n');
            }
            length = 0;
        } else if(length >= 3){
            putchar(buffer[0]);
            swap(buffer);
            buffer[2] = next_char;
            length++;
        } else {
            buffer[length] = next_char;
            length++;
        }
    }
    if(length >= 4){
        putchar(buffer[0]);
        putchar(buffer[1]);
        putchar(buffer[2]);
        putchar('\n');
    }
    fclose(fp);
}

void swap(int * array){
    array[0] = array[1];
    array[1] = array[2];
    array[2] = 0;
}