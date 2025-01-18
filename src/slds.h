typedef struct Node Node;
typedef struct List List;

struct Node {
    Node *prev;
    Node *next;
    int value;
};

struct List {
    Node *head;
    Node *last;
    int size;
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