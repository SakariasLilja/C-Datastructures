#include <stdio.h>

#include "slds.h"

int main() {
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
    return 0;
}