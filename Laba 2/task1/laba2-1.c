#include <stdio.h>
#include <stdlib.h>
#include "2-1.h"


int main(int argc, char **argv) {
    kOpts opt;
    int sizes = 2;
    int *size_i = (int *) malloc(sizes * sizeof(int));
    if (!size_i) {
        printf("Memory allocation error");
        return 1;
    }
    size_i[0] = 32;
    char **strings = (char **) malloc(sizes * sizeof(char *));
    if (!strings) {
        free(size_i);
        printf("Memory allocation error");
        return 1;
    }
    strings[0] = (char *) malloc(size_i[0] * sizeof(char));
    if (!strings[0]) {
        free(size_i);
        free(strings);
        printf("Memory allocation error");
        return 1;
    }

    unsigned int number = 0;
    if (GetOpts(argc, argv, &opt, &strings, &size_i, &sizes, &number)) {
        for (int i = 0; strings[i] && i < sizes; i++) {
            free(strings[i]);
        }
        free(strings);
        free(size_i);
        printf("%s", "Incorrect option");
        return 1;
    }
    int size = 32;
    char *ans = (char *) malloc(size * sizeof(char));

    if (!ans) {
        for (int i = 0; strings[i]; i++) {
            free(strings[i]);
        }
        free(strings);
        free(size_i);
        printf("Memory allocation error");
        return 1;
    }
    int (*handlers[4])(char **, char **, int *) = {HandlerR, HandlerU, HandlerN, HandlerC};
    if (opt) {
        if (handlers[opt - 1](strings, &ans, &size)) {
            for (int i = 0; strings[i]; i++) {
                free(strings[i]);
            }
            free(strings);
            free(size_i);
            free(ans);
            return 1;
        }
        printf("%s", ans);
    } else { printf("%d", HandlerL(strings[0])); }

    for (int i = 0; strings[i]; i++) {
        free(strings[i]);
    }
    free(strings);
    free(size_i);
    free(ans);
    return 0;
}