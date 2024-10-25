#include <math.h>
#include "2-7.h"


double dichotomy(double e, double start, double end, double (*equation)(double)) {
    double a = start;
    double b = end;
    if (equation(a) * equation(b) >= 0 || a - b > 0 || e < 0.0000000000000001) {
        return NAN;
    }

    double m = (a + b) / 2;
    double res = 0;
    res = equation(m);
    if (!isfinite(res)) { return NAN; }
    while (fabs(res) > e) {
        if (b - a < 0.000000000000001){
            return NAN;
        }
        if (res * equation(b) > 0) { b = m; }
        else { a = m; }
        m = (a + b) / 2;
        res = equation(m);
        if (!isfinite(res)) { return NAN; }
    }
    return m;
}