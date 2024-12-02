#include "2-3.h"

int find_in_own_file(String *substring, String *ans, char *name_file) {
    FILE *file = fopen(name_file, "r");
    if (file == NULL) {
        if (add_chars(ans, name_file) || add_chars(ans, ": Error this file\n")) {
            return 1;
        }
        return 0;
    }
    String *temp = create(name_file);
    if (temp == NULL) {
        fclose(file);
        return 1;
    }
    if (concatenation(ans, temp)) {
        delete(temp);
        fclose(file);
        return 1;
    }
    delete(temp);
    if (add(ans, ':')) {
        fclose(file);
        return 1;
    }
    int *pi;
    if (count_suffiks(&pi, substring)) {
        fclose(file);
        return 1;
    }
    int start_len = ans->length;
    int index_buf = 0;
    int index_symbol = 0;
    int index_str = 1;
    int memory[2] = {0, 0};
    char c;
    while ((c = (char) fgetc(file)) != EOF) {
        ++index_symbol;
        if (c == substring->data[index_buf]) {
            if (index_buf == 0) {
                memory[0] = index_str;
                memory[1] = index_symbol;
            }
            ++index_buf;
            if (index_buf == substring->length) {
                if (add(ans, ' ') || add_number(ans, memory[0]) || add(ans, ' ') ||
                    add_number(ans, memory[1]) || add(ans, ';')) {
                    fclose(file);
                    return 1;
                }
                index_buf = 0;
            }
        } else {
            while (index_buf != 0 && substring->data[index_buf] != c){
                for (int i = 0; i < index_buf - pi[index_buf - 1]; i++){
                    memory[1] += 1;
                    if (substring->data[i] == '\n'){
                        memory[0] += 1;
                        memory[1] = 1;
                    }
                }
                index_buf = pi[index_buf - 1];

            }
            if (substring->data[index_buf] == c){
                ++index_buf;
            }

        }
//        if (index_buf == 0){
//            if (c == substring->data[index_buf]){
//                memory[0] = index_str;
//                memory[1] = index_symbol;
//                ++index_buf;
//            }
//        }
//        else if (index_buf == substring->length){
//            if (add(ans, ' ') || add_number(ans, memory[0]) || add(ans, ' ') ||
//                add_number(ans, memory[1]) || add(ans, ';')) {
//                fclose(file);
//                return 1;
//            }
//            index_buf = 0;
//            if (c == substring->data[index_buf]){
//                memory[0] = index_str;
//                memory[1] = index_symbol;
//                ++index_buf;
//            }
//        }
//        else {
//            if (c == substring->data[index_buf]){ ++index_buf; }
//            else {
//                index_buf = 0;
//                if (c == substring->data[index_buf]){
//                    memory[0] = index_str;
//                    memory[1] = index_symbol;
//                    ++index_buf;
//                }
//            }
//        }
        if (c == '\n') {
            ++index_str;
            index_symbol = 0;
        }
    }
    if (index_buf == substring->length) {
        if (add(ans, ' ') || add_number(ans, memory[0]) || add(ans, ' ') ||
            add_number(ans, memory[1]) || add(ans, ';')) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    if (start_len == ans->length) {
        if (add_chars(ans, " There is not a single occurrence.")) {
            return 1;
        }
    }

    if (add(ans, '\n')) {
        return 1;
    }
    return 0;
}

int find_in_files(char *substr, char **answer, int *size, int numbers_files, ...) {
    if (numbers_files <= 0) {
        return 0;
    }
    String *substring = create(substr);
    if (substring == NULL) {
        return 1;
    }
    String *ans = create("");
    if (ans == NULL) {
        delete(substring);
        return 1;
    }
    va_list argv;
    va_start(argv, numbers_files);
    for (int i = 0; i < numbers_files; ++i) {
        char *arg = va_arg(argv, char *);
        if (find_in_own_file(substring, ans, arg)) {
            delete(substring);
            delete(ans);
            va_end(argv);
            return 1;
        }
    }
    for (int i = 0; ans->length >= i; ++i) {
        if (*size <= i) {
            *size *= 2;
            char *temp = (char *) realloc(*answer, *size);
            if (temp == NULL) {
                delete(substring);
                delete(ans);
                va_end(argv);
                return 1;
            }
            *answer = temp;
        }
        (*answer)[i] = ans->data[i];
    }
    delete(substring);
    delete(ans);
    va_end(argv);
    return 0;
}

int count_suffiks(int **pi, String *str) {
    *pi = (int *) calloc(str->length, sizeof(int));
    if (*pi == NULL) {
        return 1;
    }
    int j = 0;
    int i = 1;
    (*pi)[0] = 0;
    while (i < str->length) {
        if (str->data[j] == str->data[i]) {
            (*pi)[i] = j + 1;
            ++i;
            ++j;
        } else {
            if (!j) {
                (*pi)[i] = 0;
                ++i;
            } else {
                j = (*pi)[j - 1];
            }
        }
    }
    return 0;
}
