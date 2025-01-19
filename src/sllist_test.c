#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int listPerformanceTest(float*(*func)()) {
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