#ifndef HASHTABLE_H

#define HASHTABLE_H 1

typedef struct _node node;
typedef struct _node {
    char* key;
    int value;
    node* next;
} node;

node** hashtable_create();
void hashtable_put(node** hashtable, char* key, int value);
node* hashtable_read(node** hashtable, char* key);
void hashtable_destroy(node** hashtable);

#endif