//
// Created by Illia Matviienko on 1/24/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


int main(int argc, char *argv[]) {
    DIR *dir;
    DIR *dir1;
    struct dirent *entry;
    int num_files;
    char *cwds[10000];
    struct dirent **namelist;
    char *positions[100];
    int iterations = 0;


    printf("commandline args: \n\n");
    for (size_t i = 0; i < argc; i++) {
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
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        } // // Ignore "." and ".." entries
        if (isDirectory(entry->d_name)) {
            printf("> %s\n", entry->d_name);
        }
    }

    closedir(dir);

    printf("positions array:\n");
    for (size_t j = 0; j < argc; j++) {
        iterations++;
        printf("%s\n", positions[j]);
    }

    if (iterations < 2) {
        exit(1); // Exit with error status 1
    } else {
        printf("%s\n", "hello");
        char str1[1024] = "/";
        printf("%s\n", str1);
        printf("%s\n", positions[1]);
        strcat(str1,positions[1]);
        printf("United: %s\n", str1);
        //printf("%s\n", strcat(str1,positions[1]));
        //printf("%s\n", strcat(cwd, str1));
        dir1 = opendir(strcat(cwd, str1));   //works
        if (dir1 == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }

        while ((entry = readdir(dir1)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            printf("%s\n", entry->d_name);
        }


        closedir(dir1);

        return 0;
    }
}