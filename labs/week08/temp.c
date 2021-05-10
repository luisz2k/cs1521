#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void stat_file(char *pathname);
int size(char *pathname);

int main(int argc, char *argv[]) {

    int file_count = 1;
    int total = 0;

    while (file_count < argc) {
        
        FILE *fp = fopen(argv[file_count], "r");
        if (fp == NULL) {
            perror("Failed to open file. Exiting.\n");
            return 1;
        }
        stat_file(argv[file_count]);
        total = total + size(argv[file_count]);
        file_count++;
        fclose(fp);
    }
    printf("Total: %d\n", total);
    return 0;
}

void stat_file(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    printf("%s: %ld bytes\n", pathname, (long)s.st_size);
}

int size(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    return s.st_size;
}