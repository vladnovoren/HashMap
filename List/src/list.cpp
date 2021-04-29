#include "list.h"


template<typename ListT>
ListT* List<ListT>::Find(const ListT* elem) {
	assert(elem);

	for (size_t node_num = 0; node_num < this->n_elems; node_num++)
	    if (this->arr[node_num] == *elem)
	        return this->arr + node_num;

	return nullptr;
}


template<typename ListT>
int List<ListT>::CheckSize() {
    size_t new_capacity = 0;
    if (this->size * SIZE_CAPACITY_DIFF < this->capacity && this->size || this->size == this->capacity) {
        new_capacity   = this->size * SIZE_CAPACITY_DIFF;
        ListT* tmp_arr = realloc(this->arr, new_capacity);
        if (!tmp_arr)
            return UNABLE_TO_ALLOC;
        else {
            this->arr      = tmp_arr;
            this->capacity = new_capacity;
        }
    }

    return 0;
}


template<typename ListT>
int List<ListT>::Insert(const ListT* elem) {
	assert(elem);

	ListT* found = this->Find(elem);
	if (found)
	    return found;

	int check_size_res = this->CheckSize();
    if (check_size_res)
        return check_size_res;

	this->arr[this->size++] = *elem;

	return 0;
}



