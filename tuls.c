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

//function to check if entry is a Directory
int isDirectory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

//function to check if entry is a File
int isFile(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

//prints the entry hierarchy
void print_hierarchy(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, ".." ) == 0 || strcmp(entry->d_name, ".cmake" ) == 0 ||
            strcmp(entry->d_name, ".DS_Store" ) == 0 || strcmp(entry->d_name, ".ninja_deps" ) == 0 || strcmp(entry->d_name, ".git" ) == 0 || strcmp(entry->d_name, ".idea" ) == 0) {
            continue;  //ignores the files in listed formats
        }
        if (entry->d_type == DT_DIR) {
            char newPath[1024];
            snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
            printf("%*s%s\n", depth, "", entry->d_name);
            print_hierarchy(newPath, depth + 4);
        } else {
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    closedir(dir);
}



    int main(int argc, char *argv[]) {
        DIR *dir;
        struct dirent *entry;
        __attribute__((unused)) char *cwds[10000];
        //struct dirent **namelist;
        char *positions[100];
        //int iterations = 0;


        for (size_t i = 0; i < argc; i++) {
            positions[i] = argv[i];
        }


        if (positions[0] != NULL && positions[1] == NULL) {
            dir = opendir(".");
            if (dir == NULL) {
                perror("opendir");
                exit(EXIT_FAILURE);
            }
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                //printf("***Current directory: %s\n", cwd);
            } else {
                perror("getcwd() ERROR");
                return 1;
            }
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, ".." ) == 0 || strcmp(entry->d_name, ".cmake" ) == 0 ||
                    strcmp(entry->d_name, ".DS_Store" ) == 0 || strcmp(entry->d_name, ".ninja_deps" ) == 0 || strcmp(entry->d_name, ".git" ) == 0 || strcmp(entry->d_name, ".idea" ) == 0) {
                    continue;
                } // Ignores the files in listed formats

                if (isDirectory(entry->d_name)) {
                    printf("> %s\n", entry->d_name);
                }
                if (isFile(entry->d_name)) {
                    printf("%s\n", entry->d_name);
                }
            }
            closedir(dir);
            exit(1); // Exit with error status 1
        } else {
            dir = opendir(".");
            if (dir == NULL) {
                perror("opendir");
                exit(EXIT_FAILURE);
            }
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                //printf("***Current directory: %s\n", cwd);
            } else {
                perror("getcwd() ERROR");
                return 1;
            }
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, ".." ) == 0 || strcmp(entry->d_name, ".cmake" ) == 0 ||
                    strcmp(entry->d_name, ".DS_Store" ) == 0 || strcmp(entry->d_name, ".ninja_deps" ) == 0 || strcmp(entry->d_name, ".git" ) == 0 || strcmp(entry->d_name, ".idea" ) == 0) {
                    continue;
                } // Ignores the files in listed formats
            }
            closedir(dir);
            char str1[1024] = "/";
            strcat(str1, positions[1]);
            print_hierarchy(strcat(cwd, str1), 0);
        }
    }