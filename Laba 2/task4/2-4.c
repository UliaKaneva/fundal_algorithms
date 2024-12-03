#include "2-4.h"
#include <stdio.h>
#include <ctype.h>

int all_one_side(int numbers, cell **cells){
    for (int i = 0; i < numbers; i++){
        cell *a = cells[i];
        cell *b = cells[(i + 1) % numbers];
        cell *c = cells[(i + 2) % numbers];
        if ((b->x - a->x) * (c->y - b->y) - (c->x - b->x) * (b->y - a->y) > Epsilon){
            return 0;
        }
    }
    return 1;
}

int compare(const void *cell1, const void *cell2) {
    cell *c1 = *(struct cell**) cell1;
    cell *c2 = *(struct cell**) cell2;
    double d1;
    double d2;
    if (fabs(c1->y - c1->min->y) < Epsilon && fabs(c2->y - c2->min->y) < Epsilon){
        d1 = c1->x;
        d2 = c2->x;
    }
    else if (fabs(c1->y - c1->min->y) < Epsilon){
        if (c1->x - c1->min->x >Epsilon){
            return 1;
        }
        else {
            return -1;
        }
    }
    else if (fabs(c2->y - c2->min->y) < Epsilon){
        if (c2->x - c2->min->x >Epsilon){
            return -1;
        }
        else {
            return 1;
        }
    }
    else{
        d1 = (c1->x - c1->min->x) / (c1->y - c1->min->y);
        d2 = (c2->x - c2->min->x) / (c2->y - c2->min->y);
    }

    if (fabs(d1 - d2) < Epsilon){
        return 0;
    }
    else if (d1 - d2 < -Epsilon){
        return -1;
    }
    else{
        return 1;
    }

}

int is_convex_polygon(int numbers, ...) {
    if (numbers < 6 || numbers & 1){
        return -1;
    }
    va_list argv;
    va_start(argv, numbers);
    cell *minimum = (cell *) calloc(1, sizeof(cell));
    if (minimum == NULL){
        va_end(argv);
        return -1;
    }
    cell **cells = (cell **) calloc(numbers / 2, sizeof(cell *));
    if (cells == NULL){
        va_end(argv);
        free(minimum);
        return -1;
    }
    for (int i = 0; i < numbers / 2; i++){
        double x = va_arg(argv, double);
        double y = va_arg(argv, double);
        cells[i] = (cell *) calloc(1, sizeof(cell));
        if (cells[i] == NULL){
            free(minimum);
            for (int j = 0; j < i; j++){
                if (cells[j]){
                    free(cells[j]);
                }
            }
            free(cells);
            va_end(argv);
            return -1;
        }
        cells[i]->x = x;
        cells[i]->y = y;
        cells[i]->min = minimum;
        if (!i){
            minimum->x = x;
            minimum->y = y;
        }
        else{
            if (minimum->y - y > 0){
                minimum->x = x;
                minimum->y = y;
            }
        }
    }
    qsort(cells, numbers / 2, sizeof(cell *), compare);

    int res = all_one_side(numbers / 2, cells);
    free(minimum);
    for (int i = 0; i < numbers / 2; i++){
        if (cells[i]){
            free(cells[i]);
        }
    }
    free(cells);
    va_end(argv);
    return res;
}

double polynomial_at_point(double x0, int n, ...) {
    if (n < 0){
        return NAN;
    }
    va_list argv;
    va_start(argv, n);
    double res = 0;
    double cof = 0;
    for (int i = 0; i <= n; i++){
        res *= x0;
        cof = va_arg(argv, double);
        res += cof;
    }
    va_end(argv);
    return res;
}

void add_long_numbers(int *result, const int *num1, const int *num2, int base, int len) {
    int carry = 0;
    for (int i = len - 1; i >= 0; --i) {
        result[i] = num1[i] + num2[i] + carry;
        carry = result[i] / base;
        result[i] %= base;
    }
}

int is_caprecara(int base, int const *number, int len){
    int *squared = (int *) calloc(2 * len, sizeof(int));
    if (squared == NULL){
        return -1;
    }
    int shift;
    int index;
    for (int i = len - 1; i >= 0; --i){
        index = len + i;
        shift = 0;
        for (int j = len - 1; j >= 0; --j){
            squared[index] = squared[index] + number[i] * number[j] + shift;
            shift = squared[index] / base;
            squared[index] = squared[index] % base;
            index--;
        }
        while (shift != 0){
            squared[index] = (squared[index] + shift);
            shift = squared[index] / base;
            squared[index] = squared[index] % base;
            index--;
        }
    }
//    for (int i = 0; i < len * 2; i++){
//        printf("%d", squared[i]);
//    }

    int t = 1;
    for (int i = 0; i < len; i++){
        if (number[i] != squared[i + len]){
            t = 0;
            break;
        }
    }
    if (t){
        for (int i = 0; i < len; i++){
            if (squared[i]){
                t = 0;
                break;
            }
        }
    }
    if (t){
        free(squared);
        return 1;
    }
    int *temp = (int *) calloc(2 * len, sizeof(int));
    if (temp == NULL){
        free(squared);
        return -1;
    }
    int *result = (int *) calloc(2 * len, sizeof(int));
    if (result == NULL){
        free(squared);
        free(temp);
        return -1;
    }
    for (int i = 1; i < len * 2; i++) {
        for (int f = 0; f < len * 2; f++){
            temp[f] = 0;
        }
        for (int f = 0; f < len * 2; f++){
            result[f] = 0;
        }
        int zero = 1;
        for (int j = 0; j < i; j++) {
            temp[len * 2 - i + j] = squared[j];
            if (temp[len * 2 - i + j]){
                zero = 0;
            }
        }

        if (zero){
            continue;
        }
        zero = 1;

        for (int j = i; j < len * 2; j++) {
            result[j] = squared[j];
            if (squared[j]){
                zero = 0;
            }
        }
        if (zero){
            continue;
        }
        add_long_numbers(result, temp, result, base, len * 2);

        int equal = 1;
        for (int j = 0; j < len; j++) {
            if (result[len + j] != number[j]) {
                equal = 0;
                break;
            }
        }
        if (equal){
            free(squared);
            free(temp);
            free(result);
            return 1;
        }
    }

    free(squared);
    free(temp);
    free(result);
    return 0;
}

int number_caprecara(char **ans, int *size, int base, int n, ...){
    if (n <= 0){
        return 1;
    }
    int index_ans = 0;
    va_list argv;
    va_start(argv, n);
    int size_num = 2;
    int *number = (int *) calloc(size_num, sizeof(int));
    if (number == NULL){
        va_end(argv);
        return 1;
    }
    for (int i = 0; i < n; i++){
        for (int f = 0; f < size_num; f++){
            number[f] = 0;
        }
        char *num = va_arg(argv, char *);
        int len;
        int flag = 0;
        for (len = 0; num[len]; len++){
            if (len >= size_num){
                size_num *= 2;
                int *temp = (int *) realloc(number, size_num * sizeof(int));
                if (temp == NULL){
                    va_end(argv);
                    free(number);
                    return 1;
                }
                number = temp;
            }
            number[len] = dtn(num[len]);
            if (number[len] >= base || !isalnum(num[len])){
                flag = 1;
                break;
            }
        }
        if (flag){
            continue;
        }
        int res = is_caprecara(base, number, len);
        if (res > 0){
            for (int j = 0; j < len; j++){
                if (index_ans >= *size){
                    *size *= 2;
                    char *temp = (char *) realloc(*ans, *size * sizeof(char));
                    if (temp == NULL){
                        va_end(argv);
                        free(number);
                        return 1;
                    }
                    *ans = temp;
                }
                (*ans)[index_ans] = num[j];
                index_ans++;
            }
            if (index_ans >= *size){
                *size *= 2;
                char *temp = (char *) realloc(*ans, *size * sizeof(char));
                if (temp == NULL){
                    va_end(argv);
                    free(number);
                    return 1;
                }
                *ans = temp;
            }
            (*ans)[index_ans] = ' ';
            index_ans++;
        }
        else if (res < 0){
            free(number);
            va_end(argv);
            return 1;
        }

    }
    if (index_ans >= *size){
        *size *= 2;
        char *temp = (char *) realloc(*ans, *size * sizeof(char));
        if (temp == NULL){
            va_end(argv);
            free(number);
            return 1;
        }
        *ans = temp;
    }
    (*ans)[index_ans] = '\0';

    va_end(argv);
    free(number);
    return 0;
}