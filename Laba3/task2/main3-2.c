#include <stdio.h>
#include "3-2.h"


void print_vector(Vector *vec){
    for (int i = 0; i < vec->n; i++){
        printf("%d ", vec->array[i]);
    }
    printf("\n");
}

void print_array(Array *arr){
    for (int i = 0; i < arr->size; i++){
        print_vector(arr->vectors[i]);
    }
    printf("\n");
}



int main(){
    Array **res = NULL;
    int num_f = 3;
    int vec1[N] = {1, 5, 4};
    int vec2[N] = {6, 5, 3};
    int vec3[N] = {3, 5, 6};
    int vec4[N] = {1, 8, 1};
    Vector *v1 = create_vector(N, vec1);
    if (v1 == NULL) {
        return 1;
    }
    Vector *v2 = create_vector(N, vec2);
    if (v2 == NULL) {
        del_vector(v1);
        return 1;
    }
    Vector *v3 = create_vector(N, vec3);
    if (v3 == NULL) {
        del_vector(v1);
        del_vector(v2);
        return 1;
    }
    Vector *v4 = create_vector(N, vec4);
    if (v4 == NULL) {
        del_vector(v1);
        del_vector(v2);
        del_vector(v3);
        return 1;
    }

    if (max_vector(N, &res, num_f, 4, cubic_norm, matrix_norm, p_norm, v1, v2, v3, v4)){
        del_vector(v1);
        del_vector(v2);
        del_vector(v3);
        del_vector(v4);
        if (res != NULL){
            for (int i = 0; i < num_f; i++){
                del_array(res[i]);
            }
            free(res);
        }
    }
    del_vector(v1);
    del_vector(v2);
    del_vector(v3);
    del_vector(v4);

    for (int i = 0; i < num_f; i++){
        printf("Function %d: \n", i + 1);
        print_array(res[i]);
    }
    for (int i = 0; i < num_f; i++){
        del_array(res[i]);
    }
    free(res);

    return 0;
}