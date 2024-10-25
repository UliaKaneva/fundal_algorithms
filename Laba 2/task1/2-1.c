#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "2-1.h"


int GetOpts(int argc, char **argv, kOpts *option, char ***input, int **size_i, int *sizes, unsigned int *number) {
    if (argc < 3) {
        return 1;
    }
    const char *proceeding_option = argv[1];
    if (proceeding_option[0] == '/' || proceeding_option[0] == '-') {
        int h = 0;
        while (proceeding_option[h++]) {
            if (h > 2) return 1;
        }
        switch (proceeding_option[1]) {
            case 'l':
                *option = OPT_L;
                break;
            case 'r':
                *option = OPT_R;
                break;
            case 'u':
                *option = OPT_U;
                break;
            case 'n':
                *option = OPT_N;
                break;
            case 'c':
                *option = OPT_C;
                break;
            default:
                return 1;
        }
    } else
        return 1;
    if (argc != 3 && *option != OPT_C) { return 1; }
    if (*option == OPT_C && argc < 4) { return 1; }
    int j = 0;
    for (j = 0; argv[2][j]; j++) {
        add(input[0][0], size_i[0][0], j, argv[2][j], char);
    }
    add(input[0][0], size_i[0][0], j, '\0', char);
    int n = 1;
    if (*option == OPT_C) {
        proceeding_option = argv[3];
        for (int i = 0; proceeding_option[i]; ++i) {
            if (proceeding_option[i] >= '0' && proceeding_option[i] <= '9') {
                unsigned v_number = *number;
                *number *= 10;
                if (*number / 10 != v_number) return 1;
                if (*number > INT_MAX - (proceeding_option[i] - '0')) return 1;
                *number += proceeding_option[i] - '0';
            } else { return 1; }
        }
        for (int i = 4; argv[i]; i++) {
            int vsp_size = *sizes;
            add(*size_i, *sizes, n, 32, int);
            char *vsp = (char *) malloc(size_i[0][n] * sizeof(char));
            if (vsp == NULL) {
                return 1;
            }
            add(input[0], vsp_size, n, vsp, char *);
            int k;
            for (k = 0; argv[i][k]; k++) {
                add(input[0][n], size_i[0][n], k, argv[i][k], char);
            }
            add(input[0][n], size_i[0][n], k, '\0', char);
            n++;
        }
    }
    add(input[0], *sizes, n, NULL, char *);
    return 0;
}

void shuffle(char **array) {
    int n = 0;
    for (n = 0; array[n]; n++);
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() % (n - i);
            char *temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

int HandlerL(char const str[]) {
    int i = 0;
    for (i = 0; str[i]; i++);
    return i;
}

int HandlerR(char **str, char **ans, int *size) {
    int len = HandlerL(str[0]) - 1;
    int index = 0;
    for (int i = 0; i <= len; i++) {
        add(*ans, *size, index, str[0][len - i], char);
        index += 1;
    }
    add(*ans, *size, index, '\0', char);
    return 0;
}

int HandlerU(char **str, char **ans, int *size) {
    int index = 0;
    for (int i = 0; str[0][i]; i++) {
        add(*ans, *size, index, str[0][i] - 32 * (i & 1) * (str[0][i] >= 'a' && str[0][i] <= 'z'), char);
        index += 1;
    }
    add(*ans, *size, index, '\0', char);
    return 0;
}

int HandlerN(char **str, char **ans, int *size) {
    int index = 0;
    for (int i = 0; str[i]; i++) {
        if (isdigit(str[0][i])) {
            add(*ans, *size, index, str[0][i], char);
            index += 1;
        }
    }
    for (int i = 0; str[0][i]; i++) {
        if (isalpha(str[0][i])) {
            add(*ans, *size, index, str[0][i], char);
            index += 1;
        }
    }
    for (int i = 0; str[0][i]; i++) {
        if (!isalnum(str[0][i])) {
            add(*ans, *size, index, str[0][i], char);
            index += 1;
        }
    }
    add(*ans, *size, index, '\0', char);
    return 0;
}


int HandlerC(char **str, char **ans, int *size) {
    int index = 0;
    shuffle(str);
    for (int i = 0; str[i]; i++) {
        for (int j = 0; str[i][j]; j++) {
            add(*ans, *size, index, str[i][j], char);
            index++;
        }
    }
    add(*ans, *size, index, '\0', char);
    return 0;
}