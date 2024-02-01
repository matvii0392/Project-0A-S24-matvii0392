//
// Created by Illia Matviienko on 1/24/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

struct stat statbuf;

int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int isFile(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void print_tree(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if (!(dir = opendir(path)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char newPath[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
            printf("%*s%s\n", depth, "", entry->d_name);
            print_tree(newPath, depth + 4);
        } else {
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    closedir(dir);
}



    int main(int argc, char *argv[]) {
        DIR *dir;
        struct dirent *entry;
        char *cwds[10000];
        struct dirent **namelist;
        char *positions[100];
        int iterations = 0;


        //printf("commandline args: \n\n");
        for (size_t i = 0; i < argc; i++) {
            //printf("Position %li:%s\n", i, argv[i]);
            positions[i] = argv[i];
        }
        //printf("-----------Current----------\n");
        //printf("\nValue of argc (argument count) was %d\n", argc);


        dir = opendir(".");
        if (dir == NULL) {
            perror("opendir");
            exit(EXIT_FAILURE);
        }


        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            //printf("***Current directory: %s\n", cwd);
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
            if (isFile(entry->d_name)) {
                printf("%s\n", entry->d_name);
            }
        }

        closedir(dir);

        //printf("positions array:\n");
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
            strcat(str1, positions[1]);
            printf("United: %s\n", str1);
            //printf("%s\n", strcat(str1,positions[1]));
            //printf("%s\n", strcat(cwd, str1));
            //dir1 = opendir(strcat(cwd, str1));   //works
            print_tree(strcat(cwd, str1), 0);
        }
    }