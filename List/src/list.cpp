#include "list.h"



ListElemT* ListFind(List* list, const char *c_str) {
    assert(list);
    assert(c_str);

    for (size_t pos = 0; pos < list->n_elems; pos++) {
        if (!strcmp(c_str, list->elems[pos].req_word))
            return list->elems + pos;
    }
   
    return nullptr;
}


int ListCheckAndUpdateCapacity(List* list) {
    size_t new_capacity = 0;
    if (list->n_elems * LIST_CAPACITY_CHECK < list->capacity && list->n_elems || list->n_elems == list->capacity) {
        new_capacity = list->n_elems * LIST_CAPACITY_MUL;
        ListElemT* tmp_elems = (ListElemT*)realloc(list->elems, new_capacity * sizeof(ListElemT));
        if (tmp_elems) {
            list->elems    = tmp_elems;
            list->capacity = new_capacity;
        } else
            return LIST_UNABLE_TO_ALLOC;
    }

    return 0;
}


ListElemT* ListInsert(List* list, const ListElemT elem) {
    assert(list);

	ListElemT* found = ListFind(list, elem.req_word);
	if (found)
        return found;

    if (ListCheckAndUpdateCapacity(list))
        return nullptr;

	list->elems[list->n_elems] = elem;

	return list->elems + list->n_elems++;
}


int ListAlloc(List* list) {
    ListElemT* elems = (ListElemT*)calloc(LIST_DEFAULT_CAPACITY, sizeof(ListElemT));
    if (!elems)
        return LIST_UNABLE_TO_ALLOC;

    list->elems    = elems;
    list->n_elems  = LIST_DEFAULT_SIZE;
    list->capacity = LIST_DEFAULT_CAPACITY;

    return 0;
}


void ListDestruct(List* list) {
    free(list->elems);
    *list = {};
}
