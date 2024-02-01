//
// Created by Illia Matviienko on 1/24/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    int num_files;
    struct dirent **namelist;

    printf("commandline args: \n\n");
    for (size_t i = 0; i < argc; i++)
    {
        printf("Position %li:%s\n", i, argv[i]);
    }
    printf("-----------Current----------\n");
    //printf("\nValue of argc (argument count) was %d\n", argc);


    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    num_files = scandir(".", &namelist, NULL, alphasort);

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    printf("Number of files: %d\n", num_files);

    return 0;
}