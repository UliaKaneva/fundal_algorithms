#include "hash_table.h"
#include <stdio.h>
#include <ctype.h>
#include "4-1.h"


#define delete_all_struct do{ \
    delete(buffer_word_1);\
    delete(buffer_word_2);\
    delete(define_word);\
    delete_hash_table(table);\
    return 1;\
} while(0)


int GetOpts(int argc, char **argv, String *str) {
    if (argc != 2) { return 1; }

    int j;
    for (j = 0; argv[1][j]; j++) {
        if (add(str, argv[1][j])) {
            clear(str);
            return 1;
        }
    }

    return add(str, '\0');
}

int reading(hash_table *table, String *buf, String *buffer_word_1, char c) {
    String *res = find(table, buffer_word_1);
    if (res == NULL) {
        if (concatenation(buf, buffer_word_1)) {
            clear(buf); // Освобождаем память, выделенную для строки
            return 1;
        }
    } else {
        if (concatenation(buf, res)) {
            clear(buf); // Освобождаем память, выделенную для строки
            return 1;
        }
    }
    if (add(buf, c)) {
        clear(buf); // Освобождаем память, выделенную для строки
        return 1;
    }

    buffer_word_1->data[0] = '\0';
    buffer_word_1->length = 0;

    return 0;
}

int replace_macros(FILE *file, String *buf) {
    mod_reading mod = start_read;
    int cash;

    hash_table *table = create_hash_table(128);
    if (table == NULL) {
        return 1;
    }

    String *buffer_word_1 = create("");
    if (buffer_word_1 == NULL) {
        delete_hash_table(table);
        return 1;
    }

    String *buffer_word_2 = create("");
    if (buffer_word_2 == NULL) {
        delete_hash_table(table);
        delete(buffer_word_1);
        return 1;
    }

    String *define_word = create("#define");
    if (define_word == NULL) {
        delete_hash_table(table);
        delete(buffer_word_1);
        delete(buffer_word_2);
        return 1;
    }

    char c;
    while ((c = (char) fgetc(file)) != EOF) {
        if (isalnum(c)) {
            if (add(buffer_word_1, c)) {
                delete_all_struct;
            }
        } else if (c == ' ') {
            switch (mod) {
                case start_read:
                    if (equality(buffer_word_1, define_word)) {
                        mod = read_name_macros;
                    } else if (buffer_word_1->length != 0) {
                        mod = read;
                        if (need_to_rehash(table)) {
                            if (rehash(&table)) { delete_all_struct; }
                        }
                        if (reading(table, buf, buffer_word_1, c)) { delete_all_struct; }
                        break;
                    }
                    if (concatenation(buf, buffer_word_1)) { delete_all_struct; }
                    if (add(buf, c)) { delete_all_struct; }
                    buffer_word_1->data[0] = '\0';
                    buffer_word_1->length = 0;
                    break;
                case read_name_macros:
                    if (buffer_word_1->length != 0) {
                        if (copy(buffer_word_2, buffer_word_1)) {
                            delete_all_struct;
                        }
                        if (concatenation(buf, buffer_word_1)) {
                            delete_all_struct;
                        }
                        buffer_word_1->data[0] = '\0';
                        buffer_word_1->length = 0;
                        mod = read_value_macros;
                    }

                    if (add(buf, c)) {
                        delete_all_struct;
                    }
                    break;
                case read_value_macros:
                    if (buffer_word_1->length != 0) {
                        if (add(buffer_word_1, c)) {
                            delete_all_struct;
                        }
                    }
                    else{
                        if (add(buf, c)) {
                            delete_all_struct;
                        }
                    }
                    break;
                case read:
                    if (reading(table, buf, buffer_word_1, c)) {
                        delete_all_struct;
                    }
                    break;
            }
        } else if (c == '\n') {
            switch (mod) {
                case read_name_macros:
                    delete_all_struct;
                case read_value_macros:
                    cash = hash_func(buffer_word_2);
                    if (cash < 0) {
                        delete_all_struct;
                    }
                    if (add_node_in_table(table, buffer_word_2, buffer_word_1, cash)) {
                        delete_all_struct;
                    }
                    if (concatenation(buf, buffer_word_1)) {
                        delete_all_struct;
                    }
                    if (add(buf, c)) {
                        delete_all_struct;
                    }
                    buffer_word_1->data[0] = '\0';
                    buffer_word_2->data[0] = '\0';
                    buffer_word_1->length = 0;
                    buffer_word_2->length = 0;
                    mod = start_read;
                    break;
                case start_read:
                    if (buffer_word_1->length != 0) {
                        mod = read;
                        reading(table, buf, buffer_word_1, c);
                        buffer_word_1->data[0] = '\0';
                        buffer_word_1->length = 0;
                    }
                    if (add(buf, c)) {
                        delete_all_struct;
                    }
                    break;
                case read:
                    if (reading(table, buf, buffer_word_1, c)) {
                        delete_all_struct;
                    }
                    break;
            }
        } else {
            switch (mod) {
                case start_read:
                    if (add(buffer_word_1, c)) {
                        delete_all_struct;
                    }
                    break;
                case read_name_macros:
                    delete_all_struct;
                case read_value_macros:
                    if (add(buffer_word_1, c)) {
                        delete_all_struct;
                    }
                    break;
                case read:
                    if (reading(table, buf, buffer_word_1, c)) {
                        delete_all_struct;
                    }
                    break;
            }
        }
    }
    if (buffer_word_1->length != 0) {
        switch (mod) {
            case start_read:
                if (concatenation(buf, buffer_word_1)) { delete_all_struct; }
                break;
            case read_name_macros:
                delete_all_struct;
            case read_value_macros:
                cash = hash_func(buffer_word_2);
                if (cash < 0) { delete_all_struct; }
                if (add_node_in_table(table, buffer_word_2, buffer_word_1, cash)) {
                    delete_all_struct;
                }
                if (concatenation(buf, buffer_word_1)) { delete_all_struct; }
            case read:
                if (reading(table, buf, buffer_word_1, '\0')) { delete_all_struct; }
                break;
        }
    }
    delete(buffer_word_1);
    delete(buffer_word_2);
    delete(define_word);
    delete_hash_table(table);
    return 0;
}