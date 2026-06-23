#include <stdio.h>
#include <stdlib.h>

#include "dynamicArray.h"

int main() {
    // simple testing
    darray* arr = darray_create(10);
    if (!arr) {
        fprintf(stderr, "Failed to create dynamic array\n");
        return 1;
    }

    darray_push(arr, 1);
    darray_push(arr, 2);
    darray_push(arr, 3);

    printf("Dynamic array contents: ");
    darray_print(arr);

    int value;
    if (darray_pop(arr, &value) == 0) {
        printf("Popped value: %d\n", value);
    }

    darray_destroy(arr);
}
