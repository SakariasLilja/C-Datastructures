#include "slds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DynArr* dynarr_init() {
    // Allocate memory for DynArr
    DynArr *mem = malloc(sizeof(DynArr));
    if(mem == NULL) {
        return NULL;
    }

    // Allocate memory for array
    int *values = malloc(2 * sizeof(int));
    if (values == NULL) {
        free(mem);
        return NULL;
    }

    // Set base-value of dyn arr
    DynArr arr = {values, 0, 2};
    void *src = (void*) &arr;
    memcpy(mem, src, sizeof(DynArr));

    return mem;
}

void dynarr_free(DynArr *arr) {
    int *values = arr->values;
    free(values);
    free(arr);
}

void dynarr_print(DynArr *arr) {
    unsigned int size = arr->size;
    int *values = arr->values;
    printf("[");
    for(unsigned int i = 0; i < size; i++) {
        printf("%d", values[i]);
        if(i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * @brief Helper method for increasing the capacity of a dynamic array
 * 
 * @param arr The array to resize
 */
DynArr* incrCapacity(DynArr *arr) {
    DynArr *a = arr;
    int *values = a->values;
    unsigned int newSize = a->capacity;
    newSize = (3 * newSize) / 2;

    // Reallocate memory
    values = realloc(values, newSize * sizeof(int));
    if (values == NULL) {
        return NULL;
    }
    a->values = values;
    a->capacity = newSize;

    return a;
}

DynArr* dynarr_add(DynArr *arr, int value) {
    DynArr *a = arr;

    // Check to increase capacity
    unsigned int size = arr->size;
    unsigned int capacity = arr->capacity;
    if(size == capacity) {
        a = incrCapacity(arr);
    }

    // Reallocation of memory is wrong
    if(a == NULL) {
        return NULL;
    }

    // Insert value
    int *values = a->values;
    values[size] = value;
    a->size++;

    return arr;
}

DynArr* dynarr_addAll(DynArr *arr, const int *src, unsigned int size) {
    unsigned int i = 0;

    while(i < size) {
        dynarr_add(arr, src[i]);
        if (arr == NULL) {
            return NULL;
        }
        i++;
    }

    return arr;
}

DynArr* dynarr_insert(DynArr *arr, int value, unsigned int index) {
    unsigned int size = arr->size;
    if(index >= size) {
        return NULL;
    }

    unsigned int capacity = arr->capacity;
    if(size == capacity) {
        incrCapacity(arr);
    }

    if(arr == NULL) {
        return NULL;
    }

    DynArr *a = arr;
    int *values = arr->values;

    unsigned int i;
    for(i = size; i > index; i--) {
        values[i] = values[i-1];
    }
    values[i] = value;
    a->size++;

    return arr;
}

int dynarr_get(DynArr *arr, unsigned int index) {
    unsigned int size = arr->size;
    if(index >= size) {
        return 0;
    }

    int *values = arr->values;

    return values[index];
}

int dynarr_replace(DynArr *arr, int value, unsigned int index) {
    unsigned int size = arr->size;
    if(index >= size) {
        return 0;
    }

    int *values = arr->values;
    int oldVal = values[index];
    values[index] = value;

    return oldVal;
}

unsigned int dynarr_indexof(DynArr *arr, int value) {
    int *values = arr->values;
    unsigned int size = arr->size;
    for(unsigned int i = 0; i < size; i++) {
        if(value == values[i]) {
            return i;
        }
    }

    return size;
}

int dynarr_remove(DynArr *arr, unsigned int index) {
    unsigned int size = arr->size;
    if(index >= size) {
        return -1;
    }

    DynArr *a = arr;
    int *values = arr->values;
    int out = values[index];

    for(unsigned int i = index; i < size; i++) {
        values[i] = values[i+1];
    }
    a->size--;

    return out;
}

DynArr* dynarr_qsort(DynArr *arr, int(*compar)(const void*, const void*)) {
    unsigned int size = arr->size;
    int *values = arr->values;
    qsort(values, size, sizeof(int), compar);

    return arr;
}