#include <stdlib.h>

#ifndef D_ARRAY

#define D_ARRAY 1

typedef struct darray darray;
darray* darray_create(size_t capacity);
void darray_destroy(darray* arr);
void darray_push(darray* arr, int value);
int darray_pop(darray* arr, int* out);
void darray_print(darray* arr);

#endif