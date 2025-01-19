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

    printf("Appending 10^6 elements...\n");
    clock_t ticks = clock();

    for (long i = 0; i < 1000000L; i++) {
        list_append(list, 1);
    }

    ticks = clock() - ticks;
    printf("Appending elements took %f seconds.\n", ((float)ticks)/CLOCKS_PER_SEC);
    list_free(list);
}