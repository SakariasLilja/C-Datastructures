#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int TEST_SIZE = 10;
unsigned int ARR[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

void warmup() {
    List *list = list_init();
    for(unsigned int i = 0; i < ARR[TEST_SIZE - 1]; i++) {
        list_append(list, 0);
    }
    list_free(list);
}

int listPerformanceTest(float*(*func)()) {
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

    printf("Measuring list performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        List *list = list_init();
        clock_t ticks = clock();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            list_append(list, 0);
        }
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");
    
    return times;
}

float* listSortPerformance() {
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    return times;
}