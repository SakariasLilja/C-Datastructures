struct Node;
typedef struct List List;

struct List {
    struct Node *head;
    struct Node *last;
    unsigned int size;
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
 * @brief Sorts the list in either ascending or descending order (O(n^2) complexity - bubble sort)
 * 
 * @param list The list to sort
 * @param ascending If the list is to be sorted ascending
 * @return List* The sorted list
 */
List* list_sort(List *list, unsigned char ascending);

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