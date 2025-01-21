#include "slds.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set_upsize(Set *set) {
    unsigned int oldSize = set->buckets;
    unsigned int newSize = 2 * oldSize;

    // Initialize new list array
    List **n_lists = calloc(newSize, sizeof(List*));
    if(n_lists == NULL) {
        return 0;
    }

    // Initialize new lists
    for(unsigned int i = 0; i < newSize; i++) {
        n_lists[i] = list_init();
        // Check if list was initialized properly
        if(n_lists[i] == NULL) {
            for(unsigned int j = 0; j < i; j++) {
                list_free(n_lists[j]);
            }
            free(n_lists);
            return 0;
        }
    }

    List **oldLists = set->lists;

    // Add elements to new hash set
    for(unsigned int i = 0; i < oldSize; i++) {
        Node *current = oldLists[i]->head;
        while(current != NULL) {
            int value = current->value;
            list_append(n_lists[value % newSize], value);
            Node *next = current->right;
            free(current);
            current = next;
        }
        free(oldLists[i]);
    }

    free(oldLists);
    set->lists = n_lists;
    set->buckets = newSize;

    return 1;
}

int set_downsize(Set *set) {
    unsigned int oldSize = set->buckets;
    unsigned int newSize = oldSize / 2;

    // Initialize new list array
    List **newLists = calloc(newSize, sizeof(List*));
    if(newLists == NULL) {
        return 0;
    }

    // Initialize new lists
    for(unsigned int i = 0; i < newSize; i++) {
        newLists[i] = list_init();
        // Check if list was initialized properly
        if(newLists[i] == NULL) {
            for(unsigned int j = 0; j < i; j++) {
                list_free(newLists[j]);
            }
            free(newLists);
            return 0;
        }
    }

    List **oldLists = set->lists;

    // Add elements to new hash set
    for(unsigned int i = 0; i < oldSize; i++) {
        Node *current = oldLists[i]->head;
        while(current != NULL) {
            int value = current->value;
            list_append(newLists[value % newSize], value);
            Node *next = current->right;
            free(current);
            current = next;
        }
        free(oldLists[i]);
    }

    free(oldLists);
    set->lists = newLists;
    set->buckets = newSize;
    
    return 1;
}

Set* set_init() {
    // Initialize memory for hash set
    Set *mem = malloc(sizeof(Set));
    if(mem == NULL) {
        return NULL;
    }

    // Initialize list array
    List **lists = calloc(16, sizeof(List*));
    if(lists == NULL) {
        free(mem);
        return NULL;
    }

    // Initialize lists
    for(int i = 0; i < 16; i++) {
        lists[i] = list_init();
        // Check if list was initialized properly
        if(lists[i] == NULL) {
            for(int j = 0; j < i; j++) {
                list_free(lists[j]);
            }
            free(lists);
            free(mem);
            return NULL;
        }
    }

    // Make set and move into heap
    Set set = {lists, 0, 16};
    memcpy(mem, (const void*) &set, sizeof(Set));

    return mem;
}

void set_free(Set *set) {
    unsigned int buckets = set->buckets;
    List **lists = set->lists;

    // Free lists
    for(unsigned int i = 0; i < buckets; i++) {
        List *current = lists[i];
        if(current != NULL) {
            list_free(current);
        }
    }

    // Free rest
    free(lists);
    free(set);
}

void set_print(Set *set) {
    List **lists = set->lists;
    unsigned int count = 0;
    unsigned int entries = set->entries;
    unsigned int buckets = set->buckets;
    printf("{");
    for(unsigned int i = 0; i < buckets; i++) {
        Node *current = lists[i]->head;
        while(current != NULL) {
            printf("%d", current->value);
            count++;
            if(count < entries) {
                printf(", ");
            }
            current = current->right;
        }
    }
    printf("}\n");
}

int set_add(Set *set, int value) {
    unsigned int index = value % set->buckets;
    List **lists = set->lists;
    Node *current = lists[index]->head;
    while(current != NULL) {
        if(value == current->value) {
            return 0;
        }
        current = current->right;
    }

    if(!list_append(lists[index], value)) {
        return 0;
    }

    set->entries++;
    if(set->buckets == set->entries) {
        return set_upsize(set);
    }

    return 1;
}

int set_contains(Set *set, int value) {
    unsigned int index = value % set->buckets;
    List **lists = set->lists;
    Node *current = lists[index]->head;
    while(current != NULL) {
        if(value == current->value) {
            return 1;
        }
        current = current->right;
    }

    return 0;
}

int set_remove(Set *set, int value) {
    unsigned int index = value % set->buckets;
    List **lists = set->lists;
    int success = list_removeIf(lists[index], value);
    if(!success) {
        return 0;
    }

    set->entries--;
    if(16 < set->buckets && 4 * set->entries <= set->buckets) {
        return set_downsize(set);
    }

    return 1;
}