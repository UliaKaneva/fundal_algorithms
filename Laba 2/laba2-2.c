#include <stdio.h>
#include <math.h>
#include "2-2.h"


int main(void) {
    double ans = pow_2_0(20, 1000);
    printf("%lf\n", ans);
    double ans2 = geometric_mean(4, 0.01, 0.01, 36.0, 36.0);
    printf("%lf\n", ans2);
    return 0;
}