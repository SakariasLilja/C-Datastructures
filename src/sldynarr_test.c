#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int ascending(const void* value1, const void* value2) {
    const int *v1 = value1;
    const int *v2 = value2;

    const int v1v = *v1;
    const int v2v = *v2;
    
    if(v1v < v2v) {
        return -1;
    }

    if(v1v > v2v) {
        return 1;
    }

    return 0;
}

float* dynarrAddPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring dynamic array add performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        DynArr *arr = dynarr_init();
        clock_t ticks = clock();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            dynarr_add(arr, 0);
        }
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F / (float)ARR[i];
        dynarr_free(arr);
    }
    printf("Done!\n");

    return times;
}

float* dynarrInsertPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring dynamic array insert performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        DynArr *arr = dynarr_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            dynarr_add(arr, 0);
        }
        clock_t ticks = clock();
        dynarr_insert(arr, 1, 0);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        dynarr_free(arr);
    }
    printf("Done!\n");

    return times;
}

float* dynarrSortPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring dynamic array sort performance...\n");
    srand(1);
    for(int i = 0; i < TEST_SIZE; i++) {
        DynArr *arr = dynarr_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            dynarr_add(arr, rand());
        }
        clock_t ticks = clock();
        dynarr_qsort(arr, ascending);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        dynarr_free(arr);
    }
    printf("Done!\n");

    return times;
}