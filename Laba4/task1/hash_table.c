#include "hash_table.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>


int hash_func(String *str) {
    int k = INT_MAX / 128 / 62;
    k = (k - 1) * 128;
    int hash_result = 0;
    if (str == NULL) {
        return -1;
    }
    for (int i = 0; i < str->length; i++) {
        hash_result =
                ((62 * hash_result) % k + (str->data[i] - 48 - 7 * (str->data[i] >= 'A') - 6 * (str->data[i] >= 'a'))) %
                k;


    }
    return hash_result;
}

hash_table *create_hash_table(int hash_size) {
    hash_table *res = (hash_table *) calloc(1, sizeof(hash_table));
    if (!res) {
        return NULL;
    }
    res->HASHSIZE = hash_size;
    res->data = (Node **) calloc(res->HASHSIZE, sizeof(Node *));
    if (!res->data) {
        free(res);
        return NULL;
    }
    res->numbers = 0;

    res->max = -1;
    res->min = -1;
    return res;
}

Node *create_Node(String *key, String *value, int hash) {
    Node *res = (Node *) calloc(1, sizeof(Node));
    if (!res) {
        return NULL;
    }
    res->key = create(key->data);
    if (res->key == NULL){
        delete_Node(res);
        return NULL;
    }
    res->cash_key = hash;
    if (res->cash_key < 0) {
        delete_Node(res);
        return NULL;
    }
    res->value = create(value->data);
    if (res->value == NULL){
        delete_Node(res);
        return NULL;
    }
    res->num_next = 0;
    res->next = NULL;

    return res;
}

void delete_Node(Node *node) {
    if (node){
        if (node->key){delete(node->key);}
        if (node->value) {delete(node->value);}
        free(node);
    }

}

void delete_hash_table(hash_table *table) {
    for (int i = 0; table->HASHSIZE > i; i++) {
        Node *ptr = table->data[i];
        while (ptr != NULL) {
            Node *temp = ptr;
            ptr = ptr->next;
            delete_Node(temp);
        }
        table->data[i] = NULL;
    }
    free(table->data);
    free(table);
}

int add_node_in_table(hash_table *table, String *key, String *value, int hash_add) {
    Node *new_node = create_Node(key, value, hash_add);
    if (new_node == NULL) {
        return 1;
    }
    table->numbers += 1;
    int hash = hash_add % table->HASHSIZE;
    if (table->data[hash] == NULL) {
        table->data[hash] = new_node;
    } else {
        Node *ptr = table->data[hash];
        while (ptr->next != NULL) {
            ptr->num_next += 1;
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }

    table->max = ((table->max == -1) || table->max < (table->data[hash]->num_next + 1)) ?
                 table->data[hash]->num_next + 1 : table->max;
    table->min = ((table->min == -1) || table->min > (table->data[hash]->num_next + 1)) ?
                 table->data[hash]->num_next + 1 : table->min;
    return 0;
}

String *find(hash_table *table, String *key) {
    int hash = hash_func(key) % table->HASHSIZE;
    Node *ptr = table->data[hash];
    while (ptr != NULL) {
        if (equality(ptr->key, key)) {
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return NULL;
}

int find_simple(int num) {
    int n = num + 1;
    while (1) {
        int flag = 1;
        for (int i = 2; i <= (int) sqrt(n); i++) {
            if (!(n % i)) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return n;
        }
        n++;
    }
}

int need_to_rehash(hash_table const *table) {
    return table->min * 2 <= table->max || table->numbers >= table->HASHSIZE * 0.75;
}

int rehash(hash_table **table_old) {
    hash_table *table = *table_old;
    int new_size = table->HASHSIZE;
    if (table->numbers > table->HASHSIZE) {
        new_size = table->numbers;
    }
    new_size = find_simple(new_size);
    hash_table *new_table = create_hash_table(new_size);
    if (new_table == NULL) {
        return 1;
    }
    for (int i = 0; table->HASHSIZE > i; i++) {
        Node *ptr = table->data[i];
        while (ptr != NULL) {
            if (add_node_in_table(new_table, ptr->key, ptr->value, ptr->cash_key)) {
                delete_hash_table(new_table);
                return 1;
            }
            ptr = ptr->next;
        }
    }
    delete_hash_table(*table_old);
    *table_old = new_table;
    return 0;
}