#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void warmup() {
    List *list = list_init();
    for(unsigned int i = 0; i < ARR[TEST_SIZE - 1] * 10; i++) {
        list_append(list, 0);
    }
    list_free(list);
}

int sortAscending(const void *value1, const void *value2) {
    const int *v1 = value1;
    const int *v2 = value2;
    if(*v1 > *v2) {
        return 1;
    }

    return 0;
}

int performanceTest(float*(*func)()) {
    warmup();
    float *times = (*func)();

    if (times == NULL) {
        return 0;
    }

    printf("The times are:\n");

    for(int i = 0; i < TEST_SIZE; i++) {
        printf("%6u: %3.3f ms\n", ARR[i], times[i]);
    }
    free(times);

    return 1;
}

float* listAddPerformance() {
    float *times = calloc(TEST_SIZE, sizeof(float));
    if (times == NULL) {
        return NULL;
    }

    printf("Measuring list append performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        List *list = list_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            list_append(list, 0);
        }
        clock_t ticks = clock();
        list_append(list, 1);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");
    
    return times;
}

float* listSortPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    srand(0);
    
    printf("Measuring list sort performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        List *list = list_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            list_append(list, rand());
        }
        clock_t ticks = clock();
        list_sort(list, sortAscending);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");

    return times;
}

float* listReversePerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));
    
    if(times == NULL) {
        return NULL;
    }

    srand(0);

    printf("Measuring list reverse performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        List *list = list_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            list_append(list, rand());
        }
        clock_t ticks = clock();
        list_reverse(list);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");

    return times;
}

float* listGetPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring list get performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        List *list = list_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            list_append(list, 0);
        }
        clock_t ticks = clock();
        list_get(list, ARR[i] - 2);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");

    return times;
}