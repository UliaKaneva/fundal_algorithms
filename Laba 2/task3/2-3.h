#ifndef LAB2_2_3_H
#define LAB2_2_3_H

#include "../../Laba3/task4/strings.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


int find_in_own_file(String *substring, String *ans, char *name_file);

int find_in_files(char *substr, char **answer, int *size, int numbers_files, ...);


#endif //LAB2_2_3_H
