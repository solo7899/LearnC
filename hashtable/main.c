#include <stdio.h>

#include "hashtable.h"

int main() {
    // test functionalities
    node** ht = hashtable_create();
    hashtable_put(ht, "key1", 12);
    hashtable_put(ht, "key2", 30);
    printf("Value for key1: %s\n", hashtable_read(ht, "key1"));
    printf("Value for key2: %s\n", hashtable_read(ht, "key2"));
    hashtable_destroy(ht);

    return 0;
}
