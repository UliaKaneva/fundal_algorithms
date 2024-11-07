#include <stdio.h>
#include <stdlib.h>
#include "3-3.h"


int main(int argc, char **argv) {
    kOpts opt;
    int sizes[2] = {2, 2};
    char *names[2];
    names[0] = (char *) malloc(sizes[0] * sizeof(char));
    if (!names[0]) {
        printf("Memory allocation error");
        return 1;
    }
    names[1] = (char *) malloc(sizes[1] * sizeof(char));
    if (!names[1]) {
        free(names[0]);
        printf("Memory allocation error");
        return 1;
    }
    if (GetOpts(argc, argv, &opt, names, sizes)) {
        for (int i = 0; i <= 1; i++) {
            free(names[i]);
        }
        printf("%s", "Incorrect option");
        return 1;
    }
    emp *ans = (emp *) malloc(sizeof(emp));
    if (!ans){
        free(names[0]);
        free(names[1]);
        printf("Memory allocation error");
        return 1;
    }

    if (create(ans)) {
        free(ans);
        free(names[0]);
        free(names[1]);
        printf("Memory allocation error");
        return 1;
    }
    FILE *input = fopen(names[0], "r");
    if (!input) {
        printf("Incorrect file %s", names[0]);
        free(names[0]);
        delete(ans);
        return 1;
    }
    free(names[0]);
    if (data_reading(input, ans)) {
        fclose(input);
        free(names[1]);
        delete(ans);
        printf("Memory allocation error");
        return 1;
    }

    fclose(input);
    if (opt) {
        qsort((void *) ans->data, ans->index, sizeof(Employee *), compare);
    } else {
        qsort((void *) ans->data, ans->index, sizeof(Employee *), compare_revers);
    }

    FILE *output = fopen(names[1], "w");
    if (!output) {
        printf("Incorrect file %s", names[1]);
        free(names[1]);
        delete(ans);
        return 1;
    }
    free(names[1]);
    for (int i = 0; i < ans->index; i++) {
        fprintf(output, "%d %s %s %lf\n", ans->data[i]->id, ans->data[i]->name, ans->data[i]->surname,
                ans->data[i]->salary);
    }

    fclose(output);
    delete(ans);
    return 0;
}