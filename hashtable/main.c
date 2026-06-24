#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

node** hashtable_create();
int hashtable_hash(char* key);
void hashtable_put(node** hashtable, char* key, int value);

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
node** hashtable_create() {
    node** hashtable = (node**)malloc(sizeof(sizeof(node*) * 30));
    if (!hashtable) return NULL;
    *hashtable = 0;
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

static node* hashtable_newNode(key, value) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) return;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}