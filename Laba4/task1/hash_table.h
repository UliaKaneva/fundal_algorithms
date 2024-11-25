#ifndef LAB2_HASH_TABLE_H
#define LAB2_HASH_TABLE_H

#include "../../Laba3/task4/strings.h"

typedef struct Node {
    String *key;
    int cash_key;
    String *value;
    struct Node *next;
    int num_next;
} Node;

typedef struct hash_table {
    int HASHSIZE;
    Node **data;
    int min;
    int max;
    int numbers;

} hash_table;

int hash_func(String *str);

hash_table *create_hash_table(int hash_size);

Node *create_Node(String *key, String *value, int hash);

void delete_Node(Node *node);

void delete_hash_table(hash_table *table);

int add_node_in_table(hash_table *table, String *key, String *value, int hash_add);

String *find(hash_table *table, String *key);

int need_to_rehash(hash_table const *table);

int rehash(hash_table **table_old);

#endif //LAB2_HASH_TABLE_H
