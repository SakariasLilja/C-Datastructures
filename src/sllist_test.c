#include "sltest.h"
#include "slds.h"

#include <stdio.h>
#include <time.h>

void linkedListTest() {
    List *list = list_init();

    int values[] = {4, 2};

    for (int i = 0; i < 2; i++) {
        if( list_append(list, values[i]) ) {
            printf("Successfully added %d\n", values[i]);
        }
        else {
            printf("Error\n");
        }
    }

    printf("\n");

    list_print(list);

    list_free(list);
}

void linkedListPerformance() {
    List *list = list_init();

    printf("Appending 10^4 elements...\n");
    clock_t ticks = clock();

    for (long i = 0; i < 10000; i++) {
        list_append(list, 1);
    }

    ticks = clock() - ticks;
    float ms = (((float)ticks)/CLOCKS_PER_SEC) * 1000;
    printf("Appending elements took %f ms.\n", ms);
    list_free(list);
}