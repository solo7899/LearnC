#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

node* hashtable_create();
int hashtable_hash(char* key);

int main() {
    printf("hashtables...\n");
    return 0;
}

typedef struct node {
    char* key;
    int value;
    node* next;
};

// implementing a simple hash table using list
node* hashtable_create() {
    node* hashtable = malloc(sizeof(sizeof(node) * 30));
    if (!hashtable) return NULL;
    return hashtable;
}

// hashing functionality to get the index
int hashtable_hash(char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31) + key[i];
        hash %= 30;
    }
    return hash;
}
