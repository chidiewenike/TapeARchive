#include "list.h"

/*
   Creates a list with the specified default capacity (@capacity).
 */
LIST* list_init(int capacity) {
    LIST* result = malloc(sizeof(LIST));
    result->count = 0;
    result->capacity = capacity;
    result->data = malloc(sizeof(void*) * capacity);

    return result;
}

/*
   Frees up the list, with the option to free up the elements with the @deep parameter.
 */
void list_dispose(LIST* list, bool deep) {
    /* Running data */
    int index;

    /* Free elements */
    if (deep) {
        for (index = 0; index < list->capacity; index++) {
            free(*(list->data + index));
        }
    }

    /* Free list */
    free(list->data);
    free(list);
}

/*
   Gives the number of items (@target) found in the list with the 
   comparator (@comparator).
 */  
int list_contains(LIST* list, void* target, int (*comparator) (void*, void*)) {
    int index;
    int count = 0;
    
    for (index = 0; index < list->count; index++) {
        if (comparator(*(list->data + index), target) == 0) count++;
    }

    return count;
}

/*
   Removes an item from the index (@index) given and returns it.
 */
void* list_remove(LIST* list, int index) {
    /* Running data */
    int jndex;
    void* result = *(list->data + index);

    /* Print to stderr if index out of bounds */
    if (index < 0 || index >= list->count) {
        fprintf(stderr, "List Error: Index (%d) is out of bounds. (%d)", 
                index, list->count);
        return NULL;
    }

    /* Drop count */
    list->count -= 1;

    /* Shift */
    for (jndex = index; jndex < list->count - 1; jndex++) {
        *(list->data + jndex) = *(list->data + jndex + 1);
    }

    return result;
}

void _list_expand(LIST* list) {
    list->capacity = list->capacity * 2;
    list->data = realloc(list->data, sizeof(void*) * list->capacity);
}

/*
   Adds an element (@element) to the list at the specific index (@index).
 */
void list_add(LIST* list, void* element, int index) {
    /* Running data */
    int jndex;
    int bound;

    /* Print to stderr if index out of bounds */
    if (index < 0 || index > list->count) {
        bound = list->count + 1;
        fprintf(stderr, "List Error: Index (%d) out of bounds. (%d)", index, bound);
        return;
    }

    /* Expand if needed */
    list->count += 1;
    if (list->count == list->capacity) _list_expand(list);

    /* Shift */
    for (jndex = index + 1; jndex < list->count; jndex++) {
        *(list->data + jndex) = *(list->data + jndex - 1);
    }

    /* Add */
    *(list->data + index) = element;
}

/*
   Adds an element (@element) to the end of the list.
 */
void list_append(LIST* list, void* element) {
    list_add(list, element, list->count);
}
