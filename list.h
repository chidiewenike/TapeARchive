#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct listStruct {
    int count;
    int capacity;
    void** data;
} LIST;

LIST* list_init(int capacity);
void list_dispose(LIST* list, bool deep);
int list_contains(LIST* list, void* target, int (*comparator) (void*, void*));
void* list_remove(LIST* list, int index);
void list_add(LIST* list, void* element, int index);
void list_append(LIST* list, void* element);

#endif
