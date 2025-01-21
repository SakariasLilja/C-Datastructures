#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float* setAddPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring set add performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        Set *set = set_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            set_add(set, (int)j);
        }
        clock_t ticks = clock();
        set_add(set, -1);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        set_free(set);
    }
    printf("Done!\n");

    return times;
}

float* setSearchPerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    srand(1);

    printf("Measuring set search performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        Set *set = set_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            set_add(set, rand());
        }
        clock_t ticks = clock();
        set_contains(set, rand());
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        set_free(set);
    }
    printf("Done!\n");

    return times;
}

float* setRemovePerformance() {
    warmup();
    float *times = calloc(TEST_SIZE, sizeof(float));

    if(times == NULL) {
        return NULL;
    }

    printf("Measuring set remove performance...\n");
    for(int i = 0; i < TEST_SIZE; i++) {
        Set *set = set_init();
        for(unsigned int j = 0; j < ARR[i]; j++) {
            set_add(set, (int)j);
        }
        clock_t ticks = clock();
        set_remove(set, 1);
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        set_free(set);
    }
    printf("Done!\n");

    return times;
}