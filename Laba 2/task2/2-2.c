#include "2-2.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>


double geometric_mean(size_t number, ...) {
    double result = 1;
    if (number == 0) { return NAN; }
    va_list argv;
    va_start(argv, number);
    for (int i = 0; i < number; i++) {
        double arg = va_arg(argv, double);
        if (arg <= 0) {
            va_end(argv);
            return NAN;
        }
        result *= arg;
    }
    result = pow(result, 1.0 / number);
    va_end(argv);
    return result;
}

double pow_2_0(double x, int n) {
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        return 1 / pow_2_0(x, -n);
    }
    if (!(n & 1)) {
        return pow_2_0(x * x, n / 2);
    }
    return x * pow_2_0(x * x, (n - 1) / 2);
}


