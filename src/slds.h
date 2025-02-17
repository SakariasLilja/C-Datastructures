#ifndef DS_H
#define DS_H

/**
 * @brief Node element for doubly linked lists.
 */
typedef struct Node Node;

/**
 * @brief Doubly linked list with constant time size determination
 * and constant time access to first and last elements.
 */
typedef struct List List;

/**
 * @brief A dynamically resized indexed array of integers.
 * Has a growth-factor of 1.5.
 */
typedef struct DynArr DynArr;

/**
 * @brief A hash set with separate chaining for collisions.
 * Has a load factor resizing of 1, and an initial capacity of 16.
 * Downsizes the the load factor reached 0.25.
 * Resizes by a factor of 2.
 */
typedef struct Set Set;

struct Node {
    struct Node *left;
    struct Node *right;
    int value;
};

struct List {
    struct Node *head;
    struct Node *last;
    unsigned int size;
};

struct DynArr {
    int *values;
    unsigned int size;
    unsigned int capacity;
};

struct Set {
    List **lists;
    unsigned int entries;
    unsigned int buckets;
};

/**
 * @brief Initializes a list to the heap
 * 
 * @param list The list to initialize
 * @return List* Pointer to the initialized list
 */
List* list_init();

/**
 * @brief Frees the list from the heap memory
 * 
 * @param list The list to free from the heap
 */
void list_free(List* list);

/**
 * @brief Appends an non-initialized element to a list
 * 
 * @param list The list onto which to append
 * @param value The appended value
 * @return int 1 if success, 0 else
 */
int list_append(List *list, int value);

/**
 * @brief Prints the contents of the list to the standard output
 * 
 * @param list The list whose contents to print
 */
void list_print(List *list);

/**
 * @brief Adds a value to the start of the list
 * 
 * @param list The list to modify
 * @param value The value to be added
 * @return int If the add was successful
 */
int list_prepend(List *list, int value);

/**
 * @brief Replaces the first instance of target with value
 * 
 * @param list The list to modify
 * @param target The target value
 * @param value The new value of target
 * @return int If the target was found and successfully replaced
 */
int list_replace(List *list, int target, int value);

/**
 * @brief Sorts the list with a with a given comparison function. Uses bubble sort ~ O(n^2).
 * 
 * @param list The list to sort
 * @param compar The comparison method
 * @return List* The sorted list
 */
List* list_sort(List *list, int(*compar)(const void*, const void*));

/**
 * @brief Reverses the order of the linked list
 * 
 * @param list List to reverse
 * @return List* The reversed list
 */
List* list_reverse(List *list);

/**
 * @brief Adds all the elements from the array to the given list
 * 
 * @param list The list to be modified
 * @param arr The array of elements
 * @param size The number of elements to add
 * @return int If the elements were added successfully
 */
int list_addAll(List *list, const int *arr, unsigned int size);

/**
 * @brief Returns the value at index i. If i > size the returned value is 0.
 * 
 * @param list The list to be read from
 * @param i The index of the wanted element
 * @return int The value of the node at index i
 */
int list_get(List *list, unsigned int i);

/**
 * @brief Removes the head element of the list. Returns 0 if list is empty.
 * 
 * @param list The list to be modified
 * @return int The value stored in the head node
 */
int list_rmh(List *list);

/**
 * @brief Removes the last element of the list. Returns 0 if list is empty.
 * 
 * @param list The list to be modified
 * @return int The value stored in the last node
 */
int list_rml(List *list);

/**
 * @brief Removes the element of the list at index i. If i > size the returned value is 0.
 * 
 * @param list The list to be modified
 * @param i The index of the element to remove
 * @return int The value stored at i
 */
int list_rmi(List *list, unsigned int i);

/**
 * @brief Inserts the value into the list at index i, i.e. the index of the inserted value will be i.
 * 
 * @param list The list to modify
 * @param value The value to be inserted
 * @param i The index of the value
 * @return int If the value was inserted successfully
 */
int list_insert(List *list, int value, unsigned int i);

/**
 * @brief Searches the list for the specified value
 * 
 * @param list The list to search
 * @param value The value to search for
 * @return int If the value was found
 */
int list_contains(List *list, int value);

/**
 * @brief Searches the list for the value and returns it
 * 
 * @param list The list for search
 * @param value The value to search for
 * @return int* Pointer to the value if found
 */
int* list_getIf(List *list, int value);

/**
 * @brief Concatenates src to dest and removes src's references to values
 * 
 * @param dst The destination list
 * @param src The source list
 * @return List* The concatenated list
 */
List* list_concat(List *dest, List *src);

/**
 * @brief Removes the first instance of this value from this list
 * 
 * @param list The list to modify
 * @param value The value to remove
 * @return int If the value was removed
 */
int list_removeIf(List *list, int value);

/**
 * @brief Initialises a dynamic array for use
 * 
 * @return DynArr* Address of the dynamic array
 */
DynArr* dynarr_init();

/**
 * @brief Frees the dynamic array from the memory
 * 
 * @param arr The array to free
 */
void dynarr_free(DynArr *arr);

/**
 * @brief Adds a value to the dynamic array
 * 
 * @param arr The dynamic array to modify
 * @param value The value to add
 * @return DynArr* The dynamic array
 */
DynArr* dynarr_add(DynArr *arr, int value);

/**
 * @brief Adds all the values from src to arr
 * 
 * @param arr The dynamic array to modify
 * @param src The source array of integers
 * @param size The size of the source array
 * @return DynArr* The dynamic array
 */
DynArr* dynarr_addAll(DynArr *arr, const int *src, unsigned int size);

/**
 * @brief Inserts a value into the dynamic array at an index
 * 
 * @param arr The dynamic array to modify
 * @param value The value to insert
 * @param index The index to insert the value into
 * @return DynArr* The dynamic array
 */
DynArr* dynarr_insert(DynArr *arr, int value, unsigned int index);

/**
 * @brief Gets the value at the index of the dynamic array
 * 
 * @param arr The dynamic array to search
 * @param index The index to read
 * @return int The value stored at the index
 */
int dynarr_get(DynArr *arr, unsigned int index);

/**
 * @brief Replaces a value at the index of the dynamic array
 * 
 * @param arr The array to modify
 * @param value The value to insert
 * @param index The index to replace
 * @return int The previous value at the index
 */
int dynarr_replace(DynArr *arr, int value, unsigned int index);

/**
 * @brief Gets the index of the first occurrence of a value in a dynamic array
 * 
 * @param arr The array to search
 * @param value The value to search for
 * @return unsigned int The index of the found element. Returns size if the value wasn't found.
 */
unsigned int dynarr_indexof(DynArr *arr, int value);

/**
 * @brief Removes an element from a dynamic array at a given index
 * 
 * @param arr The array to modify
 * @param index The index to remove
 * @return int The value stored at the index. Returns -1 if size was out of bounds.
 */
int dynarr_remove(DynArr *arr, unsigned int index);

/**
 * @brief Prints the contents of the dynamic array to the standard output
 * 
 * @param arr The array to print
 */
void dynarr_print(DynArr *arr);

/**
 * @brief Sorts the array using the in-built quicksort algorithm
 * 
 * @param arr The array to sort
 * @param compar The comparison function
 * @return DynArr* The sorted array
 */
DynArr* dynarr_qsort(DynArr *arr, int(*compar)(const void*, const void*));

/**
 * @brief Reverses the order of the elements in the dynamic array
 * 
 * @param arr The dynamic array to reverse
 * @return DynArr* The reversed dynamic array
 */
DynArr* dynarr_reverse(DynArr *arr);

/**
 * @brief Determines whether the dynamic array contains a given value
 * 
 * @param arr The dynamic array to search
 * @param value The value to look for
 * @return int If the value was found
 */
int dynarr_contains(DynArr *arr, int value);

/**
 * @brief Initializes a hash set for use
 * 
 * @return Set* The initialized hash set
 */
Set* set_init();

/**
 * @brief Frees the hash set from memory
 * 
 * @param set The hash set to free
 */
void set_free(Set *set);

/**
 * @brief Prints the hash set contents to the standard output
 * 
 * @param set The hash set to print
 */
void set_print(Set *set);

/**
 * @brief Tries to add a value to the hash set
 * 
 * @param set The hash set to modify
 * @param value The value to add
 * @return int If the value was added successfully
 */
int set_add(Set *set, int value);

/**
 * @brief Checks if the hash set contains a value
 * 
 * @param set The hash set to search
 * @param value The value to search for
 * @return int If the value was found
 */
int set_contains(Set *set, int value);

/**
 * @brief Removes an element from the hash set if it is contained
 * 
 * @param set The hash set to modify
 * @param value The value to remove
 * @return int If the value was deleted
 */
int set_remove(Set *set, int value);

#endif