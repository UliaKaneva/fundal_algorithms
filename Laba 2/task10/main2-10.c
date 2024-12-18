#include "2-10.h"
#include <stdio.h>

int main() {
    double *res = NULL;

    if (re_decomposition(0.001, 5.0, &res, 1, 5.0, -20.0)) {
        if (res != NULL) {
            free(res);
        }
        return 1;
    }
    for (int i = 0; i <= 1; i++) {
        printf("%lf ", res[i]);
    }
    free(res);

    return 0;
}