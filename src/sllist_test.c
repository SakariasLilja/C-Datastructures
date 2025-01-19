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

    printf("The times are: [");

    for(int i = 0; i < 4; i++) {
        printf("%.3f ms", times[i]);
        if (i < 3) {
            printf(", ");
        }
    }
    free(times);
    printf("]\n");

    return 1;
}

float* listAddPerformance() {
    float *times = calloc(4, sizeof(float));
    if (times == NULL) {
        return NULL;
    }

    int repetitions[] = {100, 1000, 10000, 100000};

    printf("Measuring list performance...\n");
    for(int i = 0; i < 4; i++) {
        List *list = list_init();
        clock_t ticks = clock();
        for(int j = 0; j < repetitions[i]; j++) {
            list_append(list, 1);
        }
        ticks = clock() - ticks;
        times[i] = (((float)ticks)/CLOCKS_PER_SEC) * 1000.0F;
        list_free(list);
    }
    printf("Done!\n");
    
    return times;
}