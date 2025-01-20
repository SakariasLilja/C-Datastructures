#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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