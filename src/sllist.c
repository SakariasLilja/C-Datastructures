#include "slds.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
} Node;

List* list_init() {
    List list = {NULL, NULL, 0};

    List *mem = malloc(sizeof(List));
    if (mem == NULL) {
        return NULL;
    }

    const void* src = (const void*) &list;
    memcpy(mem, src, sizeof(List));

    return mem;
}

void list_free(List *list) {
    Node *current = list->head;

    // Free the nodes of list
    while(current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void list_print(List *list) {
    Node *current = list->head;
    printf("(");

    // Loop over each node
    while(current != NULL) {
        int val = current->value;
        printf("%d", val);
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }

    printf(")\n");
}

int list_append(List *list, int value) {
    Node *last = list->last;
    List *list_ptr = list;

    Node node = {last, NULL, value};
    const void* node_ptr = (const void*) &node;

    Node *mem = malloc(sizeof(Node));
    if (mem == NULL) {
        return 0;
    }

    memcpy(mem, node_ptr, sizeof(Node));

    if (last == NULL) {
        list_ptr->head = mem;
        list_ptr->last = mem;
    } 
    else {
        last->next = mem;
    }
    
    list_ptr->size++;
    return 1;
}