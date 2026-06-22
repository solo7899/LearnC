#include <stdio.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} darray;

darray* darray_create(size_t capacity);
void darray_destroy(darray* arr);
void darray_push(darray* arr, int value);

int main() {
    printf("dynamic array\n");
    return 0;
}

darray* darray_create(size_t capacity) {
    darray* arr = malloc(sizeof(darray));
    if (!arr) return NULL;
    arr->data = malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}
