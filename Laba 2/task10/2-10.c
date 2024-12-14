#include "2-10.h"


int combine(int n, int k) {
    if (n < k){
        return 0;
    }
    k = (n - k >= k) ? k : n - k;
    int res = 1;
    for (int i = 1; i <= k; i++){
        res = res * (n - i + 1) / i;
    }
    return res;
}

int re_decomposition(double e, double a, double **result, int n, ...) {
    if (e <= 0 || result == NULL || n <= 0){
        return 1;
    }
    *result = (double *) calloc(n + 1, sizeof(double ));
    if (*result == NULL){
        return 1;
    }
    a = -a;
    va_list argv;
    va_start(argv, n);
    for (int i = 0; i <= n; i++){
        double cof = a;
        double f = va_arg(argv, double);
        for (int j = 1; j <= i; j++){
            f -= cof * combine(n - i + j, j) * (*result)[i - j];
            cof *= a;
        }
        (*result)[i] = f;
    }
    va_end(argv);
    return 0;
}
