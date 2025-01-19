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
    } 
    else {
        last->next = mem;
    }
    
    list_ptr->last = mem;
    list_ptr->size++;
    return 1;
}

int list_prepend(List *list, int value) {
    Node *head = list->head;
    List *list_ptr = list;

    Node node = {NULL, head, value};
    const void *node_ptr = (const void*) &node;

    Node *mem = malloc(sizeof(Node));
    if (mem == NULL) {
        return 0;
    }

    memcpy(mem, node_ptr, sizeof(Node));

    if (head == NULL) {
        list_ptr->last = mem;
    }
    else {
        head->prev = mem;
    }

    list_ptr->head = mem;
    list_ptr->size++;
    return 1;
}

int list_replace(List *list, int target, int value) {
    Node *current = list->head;

    while(current != NULL) {
        if (current->value == target) {
            current->value = value;
            return 1;
        }
        current = current->next;
    }

    return 0;
}

List* list_reverse(List *list) {
    List *list_ptr = list;
    Node *current = list->head;

    while(current != NULL) {
        Node *next = current->next;
        
        // Swap references around
        current->next = current->prev;
        current->prev = next;

        current = next;
    }

    // Swap list head and last references around
    Node *head = list->head;
    list_ptr->head = list->last;
    list_ptr->last = head;

    return list_ptr;
}

List* list_sort(List *list, unsigned char ascending) {
    int mask = ascending ? 1 : -1; // Flipping value for difference check between values
    // Initialize pointers
    List *l = list;
    Node *current;
    Node *next;
    // Check if values have been swapped during run
    char swapped = 0;
    do {
        swapped = 0;
        // Assign starting values
        current = l->head;
        next = current->next;
        // Loop through list
        while (next != NULL) {
            int currVal = current->value;
            int nextVal = next->value;

            // Check differences
            if (currVal * mask > nextVal * mask) {
                // Perform swap
                swapped = 1;
                current->value = nextVal;
                next->value = currVal;
            }
            current = next;
            next = next->next;
        }
    } while (swapped); // No values were swapped during run --> sorted

    return l;
}

int list_addAll(List *list, const int *arr, unsigned int size) {
    for(unsigned int i = 0; i < size; i++) {
        int success = list_append(list, arr[i]);
        if (!success) {
            list_free(list);
            return 0;
        }
    }

    return 1;
}