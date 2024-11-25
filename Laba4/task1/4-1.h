#ifndef LAB2_4_1_H
#define LAB2_4_1_H

#include "hash_table.h"
#include <stdlib.h>
#include <math.h>

int GetOpts(int argc, char **argv, String *str);
int replace_macros(FILE *file, String *buf);

typedef enum mod_reading {
    start_read, read_name_macros, read_value_macros, read
} mod_reading;

#endif //LAB2_4_1_H
