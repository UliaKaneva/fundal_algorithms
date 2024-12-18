#include "3-2.h"


Vector *create_vector(int n, const int *data) {
    Vector *res = (Vector *) calloc(1, sizeof(Vector));
    if (res == NULL) {
        return NULL;
    }
    res->array = (int *) calloc(n, sizeof(int));
    if (res->array == NULL) {
        free(res);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        res->array[i] = data[i];
    }
    res->n = n;
    return res;
}

Array *create_array() {
    Array *res = (Array *) calloc(1, sizeof(Array));
    if (res == NULL) {
        return NULL;
    }
    res->capacity = 8;
    res->vectors = (Vector **) calloc(res->capacity, sizeof(Vector *));
    if (res->vectors == NULL) {
        free(res);
        return NULL;
    }
    res->size = 0;
    return res;
}

void del_vector(Vector *vec) {
    if (vec != NULL) {
        if (vec->array != NULL) {
            free(vec->array);
        }
        free(vec);
    }
}

void del_array(Array *arr) {
    if (arr != NULL) {
        if (arr->vectors != NULL) {
            for (int i = 0; i < arr->size; i++) {
                del_vector(arr->vectors[i]);
            }
            free(arr->vectors);
        }
        free(arr);
    }
}

int add_in_array(Array *arr, Vector *vec) {
    if (arr->capacity <= arr->size) {
        arr->capacity *= 2;
        Vector **temp = (Vector **) realloc(arr->vectors, sizeof(Vector *) * arr->capacity);
        if (temp == NULL) {
            return 1;
        }
        arr->vectors = temp;
    }
    Vector *t = create_vector(vec->n, vec->array);
    if (t == NULL) {
        return 1;
    }
    arr->vectors[arr->size++] = t;
    return 0;
}

double cubic_norm(Vector *vec) {
    double res = 0.0;
    for (int i = 0; i < vec->n; i++) {
        res = (res < fabs((double) vec->array[i])) ? fabs((double) vec->array[i]) : res;
    }
    return res;
}

double p_norm(Vector *vec) {
    double res = 0.0;
    for (int i = 0; i < vec->n; i++) {
        res += fabs(pow(vec->array[i], p));
    }
    return pow(res, 1.0 / p);
}

double matrix_norm(Vector *vec) {
    double res = 0.0;
    double a[N * N] = A;
    for (int i = 0; i < vec->n; i++) {
        double xi = 0.0;
        for (int j = 0; j < vec->n; j++) {
            xi += a[i * N + j] * vec->array[j];
        }
        res += xi * vec->array[i];
    }
    return sqrt(res);
}


int max_vector(int n, Array ***res, int num_func, int num_vectors, ...) {
    if (n <= 0 || num_vectors <= 0 || num_func <= 0 || res == NULL) {
        return 1;
    }
    *res = (Array **) calloc(num_func, sizeof(Array *));
    if (*res == NULL) {
        return 1;
    }
    typedef double (*func_ptr)(Vector *);
    func_ptr *functions = (func_ptr *) malloc(num_func * sizeof(func_ptr));
    if (functions == NULL) {
        return 1;
    }
    va_list argv;
    va_start(argv, num_vectors);
    for (int i = 0; i < num_func; i++) {
        func_ptr arg = va_arg(argv, func_ptr);
        functions[i] = arg;
    }
    for (int i = 0; i < num_vectors; i++) {
        Vector *arg = va_arg(argv, Vector *);
        for (int j = 0; j < num_func; j++) {
            if ((*res)[j] == NULL) {
                (*res)[j] = create_array();
                if ((*res)[j] == NULL) {
                    free(functions);
                    va_end(argv);
                    return 1;
                }
                if (add_in_array((*res)[j], arg)) {
                    free(functions);
                    va_end(argv);
                    return 1;
                }
            } else {
                double n1 = functions[j]((*res)[j]->vectors[0]);
                double n2 = functions[j](arg);
                if (fabs(n1 - n2) < 1e-15) {
                    if (add_in_array((*res)[j], arg)) {
                        free(functions);
                        va_end(argv);
                        return 1;
                    }
                } else if (n2 > n1) {
                    for (int d = 0; (*res)[j]->size > d; d++) {
                        del_vector((*res)[j]->vectors[d]);
                    }
                    (*res)[j]->size = 0;
                    if (add_in_array((*res)[j], arg)) {
                        free(functions);
                        va_end(argv);
                        return 1;
                    }

                }
            }
        }
    }
    va_end(argv);
    free(functions);

    return 0;
}