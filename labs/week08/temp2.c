#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void stat_file(char *pathname);

int main(int argc, char *argv[]) {

    int file_count = 1;

    while (file_count < argc) {
        
        FILE *fp = fopen(argv[file_count], "r");
        if (fp == NULL) {
            perror("Failed to open file. Exiting.\n");
            return 1;
        }
        stat_file(argv[file_count]);
        file_count++;
        fclose(fp);
    }
    return 0;
}

void stat_file(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    printf("s.st_mode = %d\n", s.st_mode);

    printf( (S_ISDIR(s.st_mode)) ? "d" : "-");
    printf( (s.st_mode & S_IRUSR) ? "r" : "-");
    printf( (s.st_mode & S_IWUSR) ? "w" : "-");
    printf( (s.st_mode & S_IXUSR) ? "x" : "-");
    printf( (s.st_mode & S_IRGRP) ? "r" : "-");
    printf( (s.st_mode & S_IWGRP) ? "w" : "-");
    printf( (s.st_mode & S_IXGRP) ? "x" : "-");
    printf( (s.st_mode & S_IROTH) ? "r" : "-");
    printf( (s.st_mode & S_IWOTH) ? "w" : "-");
    printf( (s.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

}

