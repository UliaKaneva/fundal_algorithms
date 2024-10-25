#ifndef LAB2_2_8_H
#define LAB2_2_8_H


int len(char const str[]);

int bill_in_column(int radix, char *number1, char *number2, char **result, int *size);

int number_validation(char const *number, int radix);

int save_add(char **ans, int *size, int i, char element);

int sum_in_radix(int radix, char **ans, int *size, int count, ...);

#define add(array, size, i, element, type) do{\
    if ((i) >= (size)) {\
        (size) *= 2;\
        type *temp = (type *) realloc((array), (size) * sizeof(type));\
        if (temp == NULL) { return 1; }\
        (array) = temp;\
    }\
    (array)[(i)] = (element); } while(0)

#define dtn(digit) ((int) (((digit) >= '0' && (digit) <= '9') ? ((digit) - '0') : \
((digit) - 'A' + 10 - 32 * ((digit) >= 'a' && (digit) <= 'z'))))

#define ntd(number, radix) ((char) 48 + number + 39 * (!!((number) / 10)))

#endif //LAB2_2_8_H
