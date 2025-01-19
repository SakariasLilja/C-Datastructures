# C Data Structures
> Author: Sakarias Lilja

### Contents:
1. Description
1. Doubly Linked Lists

## 1. Description
This program was made with the sole purpose to practice the declaration of the most common data structures present in programming. 

The code will not be copied from elsewhere, with the possible exception regarding the test-cases.

The data structures will not be made to work with all values with the use of pointers, instead they will be made to work with integers and have in-built print methods (may be subjected to change).

Performance of the data structures is measured in ms.

## 2. Doubly Linked Lists
The implemented version of linked lists are the doubly linked ones, as these provide more flexibility with operations. They can thus be used as linked lists, stacks and queues. They also contain a size property, which makes the size calculation a constant time operation.

### Performance characteristics:
* Searching: O(n)
* Appending/prepending: O(1)
* Get size: O(1)
* Sort (bubble sort): O(n^2)
* Remove first/last: O(1)
* Remove at index i: O(n)
