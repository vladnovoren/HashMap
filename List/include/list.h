#ifndef LIST_H
#define LIST_H

#include "common_header.h"
#include "ONEGIN_lib.h"

static const int    LIST_CAPACITY_MUL     = 2;
static const int    LIST_CAPACITY_CHECK   = 4;
static const size_t LIST_DEFAULT_SIZE     = 0;
static const size_t LIST_DEFAULT_CAPACITY = 8;

enum ListStates {
	LIST_NO_ERRORS,
    LIST_UNABLE_TO_ALLOC
};


struct List {
	ListElemT* elems;
	size_t     n_elems;
	size_t     capacity;
};


ListElemT* ListFind(List* list, const char *c_str);

int ListCheckAndUpdateCapacity(List* list);

ListElemT* ListInsert(List* list, const ListElemT elem);

int ListAlloc(List* list);

void ListDestruct(List* list);


#endif /* list.h */
