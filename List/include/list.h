#ifndef LIST_H
#define LIST_H

#include "ONEGIN_lib.h"


static const int SIZE_CAPACITY_DIFF = 2;

enum ListErrors {
    UNABLE_TO_ALLOC = 1
};


template<typename ListT>
struct List {
	ListT* arr;
	size_t size;
	size_t capacity;

	ListT* Find  (const ListT* elem);
	int    Insert(const ListT* elem);
	int    CheckSize();
};






#endif /* list.h */