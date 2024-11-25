#include <ctype.h>
#include <limits.h>
#include "3-3.h"
#include "stdio.h"
#include "stdlib.h"


int save_add_char(char **array, int *size, int i, char element) {
    if (i >= *size) {
        *size *= 2;
        char *temp = (char *) realloc(*array, *size * sizeof(char));
        if (temp == NULL) { return 1; }
        *array = temp;
    }
    (*array)[i] = element;
    return 0;
}

int compare_str(const void *a, const void *b) {
    char *str1 = (char *) a;
    char *str2 = (char *) b;
    if (!str1 && !str2) {
        return 0;
    }
    if (!str1) {
        return 1;
    }
    if (!str2) {
        return -1;
    }
    int i;
    for (i = 0; str1[i] && str2[i]; i++) {
        if (str1[i] > str2[i]) {
            return -1;
        }
        if (str1[i] < str2[i]) {
            return 1;
        }
    }
    if (!str2[i] && !str1[i]) {
        return 0;
    }
    if (str2[i]) {
        return 1;
    } else {
        return -1;
    }
}

int compare(const void *a, const void *b) {
    Employee *elem1 = *(Employee **)a;
    Employee *elem2 = *(Employee **)b;
    double e = 0.000000001;
    int ans = (elem1->salary - elem2->salary > e) ? 1 : ((elem1->salary - elem2->salary < -e) ? -1 : 0);
    if (ans) {
        return ans;
    }
    ans = compare_str((void *) elem1->surname, (void *) elem2->surname);
    if (ans) {
        return ans;
    }
    ans = compare_str((void *) elem1->name, (void *) elem2->name);
    if (ans) {
        return ans;
    }
    return (int) (elem1->id - elem2->id);
}

int compare_revers(const void *a, const void *b) {
    return -compare(a, b);
}

int add_em(emp *array, Employee *element) {
    if (array->size <= array->index) {
        array->size *= 2;
        Employee **temp = (Employee **) realloc(array->data, array->size * sizeof(Employee *));
        if (temp == NULL) { return 1; }
        array->data = temp;
    }
    array->data[array->index] = element;
    array->index = array->index + 1;
    return 0;
}

int create(emp *element) {
    element->size = 32;
    element->data = (Employee **) malloc(element->size * sizeof(Employee *));
    if (!element->data) {
        return 1;
    }
    element->index = 0;
    return 0;
}

void delete(emp *element) {
    if (element->data) {
        for (int i = 0; i < element->index; i++) {
            if (element->data[i]) {
                free(element->data[i]->name);
                free(element->data[i]->surname);
                free(element->data[i]);
            }
        }
        free(element->data);
    }
    free(element);
}

int GetOpts(int argc, char **argv, kOpts *option, char *names[], int sizes[]) {
    if (argc != 4) {
        return 1;
    }
    const char *proceeding_option = argv[1];
    if (proceeding_option[0] == '/' || proceeding_option[0] == '-') {
        int h = 0;
        while (proceeding_option[h++]) {
            if (h > 2) return 1;
        }
        switch (proceeding_option[1]) {
            case 'a':
                *option = OPT_A;
                break;
            case 'd':
                *option = OPT_D;
                break;
            default:
                return 1;
        }
    } else
        return 1;
    for (int i = 2; i < 4; i++) {
        int j = 0;
        for (j = 0; argv[i][j]; j++) {
            if (save_add_char(&(names[i - 2]), &(sizes[i - 2]), j, argv[i][j])) {
                return 1;
            }
        }
        if (save_add_char(&(names[i - 2]), &(sizes[i - 2]), j, '\0')) { return 1; }
    }
    return 0;
}

int data_reading(FILE *input, emp *ans) {
    char c = ' ';
    while (c != EOF) {
        Employee *ptr = (Employee *) malloc(sizeof(Employee));
        if (!ptr) {
            return 1;
        }
        int f = 1;
        ptr->id = 0;
        for (c = (char) fgetc(input); c != ' ' && c != EOF; c = (char) fgetc(input)) {
            if (isdigit(c)) {
                unsigned v_number = ptr->id;
                ptr->id *= 10;
                if (ptr->id / 10 != v_number) {
                    f *= 0;
                    break;
                }
                if (ptr->id > UINT_MAX - (c - '0')) {
                    f *= 0;
                    break;
                }
                ptr->id += c - '0';
            } else {
                f *= 0;
                break;
            }
        }
        if (!f) {
            free(ptr);
            while (c != '\n' && c != EOF) {
                c = (char) fgetc(input);
            }
            continue;
        }
        int size_ptr = 8;
        ptr->name = (char *) malloc(size_ptr * sizeof(char));
        if (!ptr->name) {
            free(ptr);
            return 1;
        }
        int index = 0;
        for (c = (char) fgetc(input); c != ' ' && c != EOF; c = (char) fgetc(input)) {
            if (isalpha(c)) {
                if (save_add_char(&(ptr->name), &size_ptr, index++, c)) {
                    free(ptr->name);
                    free(ptr);
                    return 1;
                }
            } else {
                f *= 0;
                break;
            }
        }
        if (f) {
            if (save_add_char(&(ptr->name), &size_ptr, index, '\0')) {
                free(ptr->name);
                free(ptr);
                return 1;
            }
        }
        if (!f || !ptr->name[0]) {
            free(ptr->name);
            free(ptr);
            while (c != '\n' && c != EOF) {
                c = (char) fgetc(input);
            }
            continue;
        }
        size_ptr = 8;
        ptr->surname = (char *) malloc(size_ptr * sizeof(char));
        if (!ptr->surname) {
            free(ptr->name);
            free(ptr);
            return 1;
        }
        index = 0;
        for (c = (char) fgetc(input); c != ' ' && c != EOF; c = (char) fgetc(input)) {
            if (isalpha(c)) {
                if (save_add_char(&(ptr->surname), &size_ptr, index++, c)) {
                    free(ptr->surname);
                    free(ptr->name);
                    free(ptr);
                    return 1;
                }
            } else {
                f *= 0;
                break;
            }
        }
        if (f) {
            if (save_add_char(&(ptr->surname), &size_ptr, index, '\0')) {
                free(ptr->surname);
                free(ptr->name);
                free(ptr);
                return 1;
            }
        }
        if (!f || !ptr->surname[0]) {
            free(ptr->surname);
            free(ptr->name);
            free(ptr);
            while (c != '\n' && c != EOF) {
                c = (char) fgetc(input);
            }
            continue;
        }
        int index_point = 0;
        int flag = 0;
        double fraction_part = 0.1;
        for (c = (char) fgetc(input); c != ' ' && c != EOF; c = (char) fgetc(input)) {
            if (isdigit(c)) {
                index_point += 1;
                if (flag) {
                    ptr->salary += (c - '0') * fraction_part;
                    fraction_part *= 0.1;
                } else {
                    ptr->salary *= 10;
                    ptr->salary += (c - '0');
                }
            } else if (c == '\r') {
                continue;
            } else if (c == '.' && !flag && index_point) {
                index_point += 1;
                flag = 1;
            } else if (c != '\n') {
                f *= 0;
                break;
            } else {
                break;
            }

        }
        if (!f) {
            free(ptr->surname);
            free(ptr->name);
            free(ptr);
            while (c != '\n' && c != EOF) {
                c = (char) fgetc(input);
            }
            continue;
        }
        if (add_em(ans, ptr)) {
            free(ptr->name);
            free(ptr->surname);
            free(ptr);
            return 1;
        }
    }
    return 0;
}