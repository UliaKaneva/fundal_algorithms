#ifndef LAB2_3_2_H
#define LAB2_3_2_H

#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#define p 4
#define N 3
#define A {1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0}

typedef struct Vector {
    int n;
    int *array;
} Vector;

typedef struct Array {
    int size;
    int capacity;
    Vector **vectors;
} Array;

Vector *create_vector(int n, const int *data);

Array *create_array();

void del_vector(Vector *vec);

void del_array(Array *arr);

int add_in_array(Array *arr, Vector *vec);

double cubic_norm(Vector *vec);

double p_norm(Vector *vec);

double matrix_norm(Vector *vec);

int max_vector(int n, Array ***res, int num_func, int num_vectors, ...);


#endif //LAB2_3_2_H
