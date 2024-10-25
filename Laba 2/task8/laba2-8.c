#include <stdio.h>
#include <stdlib.h>
#include "2-8.h"


int main(void) {
    int radix = 36;
    int count = 4;
    int size = 8;
    char *ans = (char *) malloc(size * sizeof(char));
    if (!ans) {
        printf("Memory error");
        return 1;
    }
    if (sum_in_radix(radix, &ans, &size, count, "0", "0", "0",
                     "0")) {
        free(ans);
        printf("Incorrect numbers");
        return 1;
    }
    printf("%s", ans);
    free(ans);
    return 0;
}