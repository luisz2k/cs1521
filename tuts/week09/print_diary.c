// prints the contents of the file $HOME/.diary to stdout

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // open environment variables to show where this is looking
    char *homePath = getenv("HOME");
    if (homePath == NULL) {
        homePath = ".";
    }

    char *fileName = "diary.txt";
    // figure out how much space you need to store the new pathname (strlen)
    int size = strlen(homePath) + 1 + strlen(fileName) + 1;

    // create buffer
    char buffer[size];

    // print to the string using: snprintf(char *str, size_t size, const char *format, ...); (%s/%s)
    snprintf(buffer, size, "%s/%s", homePath, fileName);

    // open file for reading

    FILE *stream = fopen(buffer, "r");
    if (stream == NULL) {
        perror(buffer);
        return 1;
    }

    int byte;
    while ((byte = fgetc(stream)) != EOF) {
        fputc(byte, stdout);
    }

}