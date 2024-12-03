#ifndef LAB2_2_4_H
#define LAB2_2_4_H
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct cell {
    double x;
    double y;
    struct cell *min;
} cell;

#define Epsilon 1e-15

// 1

int compare(const void *cell1, const void *cell2);

int all_one_side(int numbers, cell **cells);

int is_convex_polygon(int numbers, ...);

// 2

#define dtn(digit) ((int) (((digit) >= '0' && (digit) <= '9') ? ((digit) - '0') : \
((digit) - 'A' + 10 - 32 * ((digit) >= 'a' && (digit) <= 'z'))))

double polynomial_at_point(double x0, int n, ...);

// 3

int number_caprecara(char **ans, int *size, int base, int n, ...);

#endif //LAB2_2_4_H
