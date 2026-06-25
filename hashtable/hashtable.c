#include "hashtable.h"

#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* key;
    int value;
    node* next;
};

// implementing a simple hash table using list
node** hashtable_create() {
    node** hashtable = (node**)calloc(30, sizeof(node*));
    if (!hashtable) return NULL;
    return hashtable;
}

// hashing functionality to get the index
// making it private
static int hashtable_hash(char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31) + key[i];
        hash %= 30;
    }
    return hash;
}

void hashtable_put(node** hashtable, char* key, int value) {
    int index = hashtable_hash(key);
    node* current = hashtable + index;

    if (!current) {
        current = hashtable_newNode(key, value);
        if (!current) return;
        hashtable[index] = current;
        return;
    }

    do {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    } while (current->next);

    current->next = hashtable_newNode(key, value);
}

static node* hashtable_newNode(char* key, int value) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) return NULL;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

node* hashtable_read(node** hashtable, char* key) {
    int index = hashtable_hash(key);
    node* current = hashtable[index];
    while (current) {
        if (strcmp(current->key, key) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void hastable_destroy(node** hastable) {
    for (int i = 0; i < 30; i++) {
        node* current = hastable[i];
        while (current) {
            node* next = current->next;
            free(current);
            current = next;
        }
    }
}