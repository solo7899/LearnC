#include <stdio.h>

#include "hashtable.h"

int main() {
    // test functionalities
    node** ht = hashtable_create();

    hashtable_put(ht, "key1", 12);
    hashtable_put(ht, "key2", 30);

    node* key1 = hashtable_read(ht, "key1");
    printf("Value for key1: %d \n", key1->value);

    node* key2 = hashtable_read(ht, "key2");
    printf("Value for key2: %d \n", key2->value);

    hashtable_destroy(ht);

    return 0;
}
