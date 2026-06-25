#ifndef HASHTABLE_H

#define HASHTABLE_H 1

typedef struct node node;

node** hashtable_create();
int hashtable_hash(char* key);
void hashtable_put(node** hashtable, char* key, int value);
static node* hashtable_newNode(char* key, int value);
node* hashtable_read(node** hashtable, char* key);
void hashtable_destroy(node** hashtable);

#endif