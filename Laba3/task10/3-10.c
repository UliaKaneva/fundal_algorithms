#include "3-10.h"

int get_opts(String **name_in, String **name_out, int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    *name_in = create(argv[1]);
    if (*name_in == NULL) {
        return 1;
    }
    *name_out = create(argv[2]);
    if (*name_out == NULL) {
        delete(*name_in);
        return 1;
    }
    return 0;
}

int print_indent(String *output, int level) {
    for (int i = 0; i < level; ++i) {
        if (add(output, '|')) {
            return 1;
        }
    }
    return 0;
}

int parse_expression(FILE *input, String *output, int level) {
    int in_word = 0;
    int ch;

    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\r') continue;
        if (ch == '\n') {
            if (in_word){
                if (add(output, '\n')) {
                    return 1;
                }
            }
            in_word = 0;
            if (concatenation_char(output, "---------------\n")) {
                return 1;
            }
        } else if (ch == '(') {
            if (in_word) {
                if (add(output, '\n')) {
                    return 1;
                }
            }
            in_word = 0;
            level++;
            if (parse_expression(input, output, level)) {
                return 1;
            }
            level--;

        } else if (ch == ')') {
            if (in_word) {
                if (add(output, '\n')) {
                    return 1;
                }
            }
            return 0;
        } else if (ch == ',') {
            if (in_word) {
                if (add(output, '\n')) {
                    return 1;
                }
            }
            in_word = 0;
        } else if (ch != ' ') {
            if (!in_word){
                if (print_indent(output, level)) {
                    return 1;
                }
                in_word = 1;
            }
            if (add(output, ch)) {
                return 1;
            }
        }
    }
    return 0;
}
