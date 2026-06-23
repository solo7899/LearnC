
#include "dynamicArray.h"

typedef struct darray {
    int* data;
    size_t size;
    size_t capacity;
} darray;

darray* darray_create(size_t capacity) {
    darray* arr = malloc(sizeof(darray));
    if (!arr) return NULL;
    arr->data = malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

void darray_destroy(darray* arr) {
    if (!arr) return;
    free(arr->data);
    free(arr);
}

void darray_push(darray* arr, int value) {
    if (!arr) return;
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size++] = value;
}

int darray_pop(darray* arr, int* out) {
    if (!arr || arr->size == 0) return 1;
    *out = arr->data[--arr->size];
    return 0;
}

void darray_print(darray* arr) {
    if (!arr) return;
    for (size_t i = 0; i < arr->size; i++) printf("%d ", arr->data[i]);
    printf("\n");
}