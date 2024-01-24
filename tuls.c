//
// Created by Illia Matviienko on 1/24/24.
//
#include <dirent.h>
#include "libc.h"
#include "tuls.h"
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>

int scan(void ) {
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

int main(void) {
    scan();
}
