#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "2-8.h"


int bill_in_column(int radix, char *number1, char *number2, char **result, int *size) {
    int index = 0;
    int len1 = len(number1);
    int len2 = len(number2);
    char *temp_max = (len1 > len2) ? number1 : number2;
    char *temp_min = (len1 <= len2) ? number1 : number2;
    int len_max = (len1 > len2) ? len1 : len2;
    int len_min = (len1 == len_max) ? len2 : len1;
    int size_temp = len_max + 2;
    char *temp_res = (char *) malloc(size_temp * sizeof(char));
    if (!temp_res) {
        return 1;
    }
    temp_res[index++] = '0';
    temp_res[len_max + 1] = '\0';
    for (int i = 0; temp_max[i]; i++) {
        int t = dtn(temp_max[i]);
        temp_res[index++] = ntd(t, radix);
    }
    int shift = 0;
    for (int i = 0; i < len_min; i++) {
        int n1 = dtn(temp_res[len_max - i]);
        int n2 = dtn(temp_min[len_min - 1 - i]);
        int n = n1 + n2 + shift;
        shift = n / radix;
        n = n % radix;
        temp_res[len_max - i] = ntd(n, radix);

    }
    for (int i = len_min; i <= len_max && shift; i++) {
        int n1 = dtn(temp_res[len_max - i]);
        int n = n1 + shift;
        shift = n / radix;
        n = n % radix;
        temp_res[len_max - i] = ntd(n, radix);
    }
    int ind = 0;
    int j = 0;
    while (temp_res[j]) {
        if (temp_res[j] == '0') {
            j++;
        } else { break; }
    }
    if (len_max + 1 == j) {
        j--;
    }

    for (int i = j; temp_res[i]; i++) {
        if (save_add(result, size, ind, temp_res[i])) {
            free(temp_res);
            return 1;
        }
        ind++;
    }
    free(temp_res);
    add(result[0], size[0], ind, '\0', char);
    return 0;

}


int number_validation(char const *number, int radix) {
    for (int i = 0; number[i]; i++) {
        if (!isalnum(number[i])) { return 1; }
        if (dtn(number[i]) >= radix) { return 1; }
    }
    if (!len(number)) { return 1; }
    return 0;
}


int len(char const str[]) {
    int i = 0;
    for (i = 0; str[i]; i++);
    return i;
}

int save_add(char **ans, int *size, int i, char element) {
    add(ans[0], size[0], i, element, char);
    return 0;
}

int sum_in_radix(int radix, char **ans, int *size, int count, ...) {
    if (radix > 36 || radix < 2) { return 1; }
    add(ans[0], size[0], 0, '0', char);
    add(ans[0], size[0], 1, '\0', char);
    if (count == 0) {
        return 0;
    }
    va_list argv;
    va_start(argv, count);
    for (int i = 0; i < count; i++) {
        char *arg = va_arg(argv, char *);
        if (number_validation(arg, radix)) {
            va_end(argv);
            return 1;
        }
        if (bill_in_column(radix, ans[0], arg, ans, size)) {
            va_end(argv);
            return 1;
        }

    }
    va_end(argv);
    return 0;
}