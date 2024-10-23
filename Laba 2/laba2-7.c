#include <stdio.h>
#include <math.h>
#include "2-7.h"


double fun(double x) { return 1 / x + 1; }

double fun1(double x) { return cos(x) + 1; }

double fun2(double x) { return sin(x); }

double fun3(double x) { return x - 3; }


int main(void) {
    double e = 0.000001;
    double start = 0.13;
    double end = 3.0000001;
    double ans = dichotomy(e, start, end, fun3);
    if (isnan(ans)) {
        printf("With these inputs, it is impossible to find the root using the dichotomy method");
    } else { printf("%lf", ans); }
    return 0;
}