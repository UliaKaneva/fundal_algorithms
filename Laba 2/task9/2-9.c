#include "2-9.h"

int is_end_nums(int **ans, int base, int n, ...) {
    if (n < 0 || base < 2 || *ans != NULL) {
        return 1;
    }
    *ans = (int *) calloc(n, sizeof(int));
    if (*ans == NULL) {
        return 1;
    }
    va_list argv;
    va_start(argv, n);
    double number = 0;
    for (int i = 0; i < n; i++) {
        number = va_arg(argv, double);
        if (number - 1 >= -1e-15 || number < 1e-15) {
            (*ans)[i] = -1;
        } else {
            (*ans)[i] = is_end_num(base, number);
        }
    }
    va_end(argv);
    return 0;
}

long long find_nod(long long a, long long b) {
    while (a != 0) {
        long long t = a;
        a = b % a;
        b = t;
    }
    return b;
}

void in_fraction(double num, long long *a, long long *b) {
    *a = 1;
    *b = (long long) round(1 / (num - (int) num));
    double dif = num - ((double) *a / (double) *b);
    long long tb;
    while (fabs(dif) >= 1e-10) {
        if (dif > 0) {
            tb = (long long) round(1.0 / dif);
            *a = *a * tb + *b;
            *b = *b * tb;
        }
        if (dif < 0) {
            tb = (long long) round(1 / (-dif));
            *a = *a * tb - *b;
            *b = *b * tb;
        }
        dif = num - ((double) *a / (double) *b);
    }
    long long nod = find_nod(*a, *b);
    *a /= nod;
    *b /= nod;
}


int is_end_num(int base, double num) {
    long long a = 0, b = 0;
    in_fraction(num, &a, &b);
    for (int i = 2; b != 1; i++) {
        int c_b = 0;
        int c_n = 0;
        while (base % i == 0) {
            base /= i;
            c_b++;
        }
        while (b % i == 0) {
            b /= i;
            c_n++;
        }
        if (c_b == 0 && c_n != 0) {
            return 0;
        }
    }
    return 1;

}
