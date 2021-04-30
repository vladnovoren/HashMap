#ifndef LIST_H
#define LIST_H

#include "ONEGIN_lib.h"
#include "hash_table_structures.h"


static const int    SIZE_CAPACITY_DIFF  = 2;
static const size_t START_LIST_SIZE     = 0;
static const size_t START_LIST_CAPACITY = 8;

enum ListStates {
	LIST_NO_ERRORS,
    LIST_UNABLE_TO_ALLOC
};


typedef HashTableElemT ListElemT;

struct List {
	ListElemT* data;
	size_t     size;
	size_t     capacity;

	int        Construct();
	void       Destruct();
	ListElemT* Find(const char* c_str);
	ListElemT* Insert(const ListElemT elem);
	int        CheckAndUpdateCapacity();
};


#endif /* list.h */
