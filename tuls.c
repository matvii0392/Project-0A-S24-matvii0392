//
// Created by Illia Matviienko on 1/24/24.
//
#include <dirent.h>
#include "libc.h"
#include "tuls.h"
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>

int scandirr (void) {
    struct dirent **namelist;
    int n;
    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}

int readirr (){
    DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(".");
    while ((dp=readdir(dir)) != NULL) {
        printf("debug: %s\n", dp->d_name);
        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
        {
            // do nothing (straight logic)
        } else {
            file_name = dp->d_name; // use it
            printf("file_name: \"%s\"\n",file_name);
        }
    }
    closedir(dir);
    return 0;
}

int opendirr () {
    DIR *dir;
    struct dirent *dp;
    dir = opendir(".");   //what directory to open??
    if (dir == NULL) {
        perror("");
    } else {
        for (;;) {
            dp = readdir(dir);
            if ((dp = readdir(dir)) == NULL) break;
            printf("%s\n", dp->d_name);

            closedir(dir);
        }
    }
}

int main() {
    scandirr();
    printf("*******************************");
    readirr();
    printf("*******************************");
    opendirr();
}
