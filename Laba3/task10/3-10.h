#ifndef LAB2_3_10_H
#define LAB2_3_10_H

#include "../task4/strings.h"

int get_opts(String **name_in, String **name_out, int argc, char **argv);

int print_indent(String *output, int level);

int parse_expression(FILE *input, String *output, int level);


#endif //LAB2_3_10_H
