#ifndef LIST_H
#define LIST_H

#include "ONEGIN_lib.h"
#include "hash_structures.h"


static const int SIZE_CAPACITY_DIFF = 2;

enum ListStates {
    UNABLE_TO_ALLOC = 1,
    ELEM_FOUND
};


typedef HashTableElemT ListElemT;

struct List {
	ListElemT* data;
	size_t     size;
	size_t     capacity;

	const char* Find(const char*  elem);
	int         Insert(const ListElemT* elem);
	int         CheckAndUpdateCapacity();
};


#endif /* list.h */
