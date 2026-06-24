#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

node* hashtable_create();

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
