#ifndef LAB2_STRINGS_H
#define LAB2_STRINGS_H

typedef struct String {
    int length;
    char *data;
    int size_data;
} String;

String *create(char *str);

void clear(String *str);

int compare(const void *s1, const void *s2);

int equality(String *str1, String *str2);

int copy(String *dest, String *src);

int copy_to_new(String *dest, String *src);

void delete(String *str);

int concatenation(String *to, String *from);

int add(String *str, char to_add);

#endif //LAB2_STRINGS_H
