#include "2-9.h"
#include <stdio.h>

#define size_array 5

int main() {
    int *res = NULL;
    if (is_end_nums(&res, 4290, size_array, 0.125, 0.333333333333333333, 0.076923076923076923, 0.1, 0.0909090909090909090909)) {
        return 1;
    }
    for (int i = 0; i < size_array; i++) {
        printf("%d ", res[i]);
    }
    putchar('\n');


    free(res);
    return 0;
}