#ifndef LAB2_2_1_H
#define LAB2_2_1_H

typedef enum kOpts {
    OPT_L, OPT_R, OPT_U, OPT_N, OPT_C
} kOpts;

#define add(array, size, i, element, type) do{\
    if ((i) >= (size)) {\
        (size) *= 2;\
        type *temp = (type *) realloc((array), (size) * sizeof(type));\
        if (temp == NULL) { return 1; }\
        (array) = temp;\
    }\
    (array)[(i)] = (element); } while(0)

int GetOpts(int argc, char **argv, kOpts *option, char ***input, int **size_i, int *sizes, unsigned int *number);

int HandlerL(char const str[]);

int HandlerR(char **str, char **ans, int *size);

int HandlerU(char **str, char **ans, int *size);

int HandlerN(char **str, char **ans, int *size);

int HandlerC(char **str, char **ans, int *size);


#endif //LAB2_2_1_H
