#include "slds.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
        Node *next = current->right;
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
        current = current->right;
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
        last->right = mem;
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
        head->left = mem;
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
        current = current->right;
    }

    return 0;
}

List* list_reverse(List *list) {
    List *list_ptr = list;
    Node *current = list->head;

    while(current != NULL) {
        Node *next = current->right;
        
        // Swap references around
        current->right = current->left;
        current->left = next;

        current = next;
    }

    // Swap list head and last references around
    Node *head = list->head;
    list_ptr->head = list->last;
    list_ptr->last = head;

    return list_ptr;
}

List* list_sort(List *list, int(*compar)(const void*, const void*)) {
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
        next = current->right;
        // Loop through list
        while (next != NULL) {
            int currVal = current->value;
            int nextVal = next->value;

            // Check differences
            if (compar((void*) &currVal, (void*) &nextVal) > 0) {
                // Perform swap
                swapped = 1;
                current->value = nextVal;
                next->value = currVal;
            }
            current = next;
            next = next->right;
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

int list_get(List *list, unsigned int i) {
    unsigned int size = list->size;
    if (i >= size) {
        return 0;
    }

    unsigned int index = 0;
    Node *current = list->head;
    while(index < i) {
        current = current->right;
        index++;
    }

    int value = current->value;
    return value;
}

int list_rmh(List *list) {
    Node *head = list->head;

    // List is empty
    if(head == NULL) {
        return 0;
    }

    int headVal = head->value;

    // List is size 1
    if(head == list->last) {
        list->head = NULL;
        list->last = NULL;
    }
    else {
        Node *nHead = head->right;
        nHead->left = NULL; // Remove reference to head
        list->head = nHead; // Set new head
    }

    free(head); // Free memory of head
    list->size--; // Decrease size of list

    return headVal;
}

int list_rml(List *list) {
    Node *last = list->last;

    // List is empty
    if(last == NULL) {
        return 0;
    }

    int lastVal = last->value;

    // List is size 1
    if(last == list->head) {
        list->head = NULL;
        list->last = NULL;
    }
    else {
        Node *newLast = last->left;
        newLast->right = NULL;
        list->last = newLast;
    }

    free(last); // Free memory of last
    list->size--; // Decrease size of list

    return lastVal;
}

int list_rmi(List *list, unsigned int i) {
    List *l = list;
    Node *current = list->head;
    if (current == NULL) {
        return 0;
    }

    unsigned int size = list->size;
    if(i >= size) {
        return 0;
    }

    if(i == 0) {
        return list_rmh(list);
    }

    if(i == size - 1) {
        return list_rml(list);
    }


    unsigned int index = 0;
    while(index < i) {
        current = current->right;
        index++;
    }

    Node *prev = current->left;
    Node *next = current->right;
    int value = current->value;

    prev->right = next;
    next->left = prev;
    l->size--;
    free(current);

    return value;
}

int list_insert(List *list, int value, unsigned int i) {
    List *l = list;
    Node *current = list->head;
    if (current == NULL) {
        return 0;
    }

    unsigned int size = l->size;
    if(i >= size) {
        return 0; // Index out of bounds
    }

    // Check if prepend or append could work
    if(i == 0) {
        return list_prepend(list, value);
    }

    if(i == size - 1) {
        return list_append(list, value);
    }

    // ALlocate memory for the new node
    Node *mem = malloc(sizeof(Node));
    if (mem == NULL) {
        return 0;
    }
    
    // Set memory of node
    Node n = {NULL, NULL, value};
    void *src = (void*) &n;
    memcpy(mem, src, sizeof(Node));

    // Loop through to index
    unsigned int index = 0;
    while(index < i) {
        current = current->right;
        index++;
    }

    // Assign references
    Node *prev = current->left;
    mem->left = prev;
    mem->right = current;
    prev->right = mem;
    current->left = mem;

    l->size++;

    return 1;
}

int list_contains(List *list, int value) {
    Node *current = list->head;
    while(current != NULL) {
        if(value == current->value) {
            return 1;
        }
        current = current->right;
    }

    return 0;
}

int* list_getIf(List *list, int value) {
    Node *current = list->head;
    while(current != NULL) {
        int *currentValue = &current->value;
        if(value == *currentValue) {
            return currentValue;
        }
        current = current->right;
    }

    return NULL;
}

List* list_concat(List *dest, List *src) {
    if(src->head == NULL) {
        return dest;
    }

    if(dest->head == NULL) {
        dest->head = src->head;
        dest->last = src->last;
        src->head = NULL;
        src->last = NULL;
        return dest;
    }

    Node *mid1 = dest->last;
    Node *mid2 = src->head;
    mid1->right = mid2;
    mid2->left = mid1;
    dest->last = src->last;
    src->head = NULL;
    src->last = NULL;
    return dest;
}

int list_removeIf(List *list, int value) {
    Node *current = list->last;
    if(current == NULL) {
        return 0;
    }

    if(value == current->value) {
        list_rml(list);
        return 1;
    }

    current = list->head;
    if(value == current->value) {
        list_rmh(list);
        return 1;
    }

    current = current->right;
    while(current != NULL) {
        if(value == current->value) {
            Node *prev = current->left;
            Node *next = current->right;
            prev->right = next;
            next->left = prev;
            list->size--;
            free(current);
            return 1;
        }
        current = current->right;
    }

    return 0;
}