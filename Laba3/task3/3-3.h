#ifndef LAB2_3_3_H
#define LAB2_3_3_H

#include <stdio.h>


typedef struct Employee {
    unsigned int id;
    char *name;
    char *surname;
    double salary;
} Employee;

typedef struct Employees {
    Employee **data;
    int index;
    int size;
} emp;

int compare_revers(const void *a, const void *b);

int create(emp *element);

int compare(const void *a, const void *b);

int data_reading(FILE *input, emp *ans);

void delete(emp *element);

typedef enum kOpts {
    OPT_A, OPT_D
} kOpts;


int GetOpts(int argc, char **argv, kOpts *option, char *names[], int sizes[]);

int add(char **array, int *size, int i, char element);

#endif //LAB2_3_3_H
