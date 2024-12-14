#include "2-10.h"
#include <stdio.h>

int main() {
    double *res = NULL;

    if (re_decomposition(0.001, 1.5, &res, 3, -7.0, -2.0, 4.0, 13.76)) {
        if (res != NULL) {
            free(res);
        }
        return 1;
    }
    for (int i = 0; i <= 3; i++) {
        printf("%lf ", res[i]);
    }
    free(res);

    return 0;
}