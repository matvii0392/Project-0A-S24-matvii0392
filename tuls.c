//
// Created by Illia Matviienko on 1/24/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]) {
    DIR *dir;
    DIR *dir1;
    struct dirent *entry;
    int num_files;
    struct dirent **namelist;
    char *positions[100];


    printf("commandline args: \n\n");
    for (size_t i = 0; i < argc; i++)
    {
        printf("Position %li:%s\n", i, argv[i]);
        positions[i] = argv[i];
    }
    printf("-----------Current----------\n");
    //printf("\nValue of argc (argument count) was %d\n", argc);


    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    num_files = scandir(".", &namelist, NULL, alphasort);
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("***Current directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }


    closedir(dir);

    printf("Number of files: %d\n", num_files);
    printf("positions array:\n");
    for (size_t j = 0; j < argc; j++){
        printf("%s\n", positions[j]);
    }


    printf("__________________________________________\n");
    //char cwd2[1024];strcat("cwd", positions[1]);
    //printf("%s\n", strcat(cwd, strcat("/", positions[1])));
    dir1 = opendir(strcat(cwd, strcat("/", positions[1])));
    if (dir1 == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir1)) != NULL) {
        printf("%s\n", entry->d_name);
    }


    closedir(dir1);

    return 0;
}