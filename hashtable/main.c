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

    while (current->value && current->next) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    node* newNode = (node*)malloc(sizeof(node));
    if (!current->next) return;
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    current->next = newNode;
}