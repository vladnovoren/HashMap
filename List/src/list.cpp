#include "list.h"

const char* List::Find(const char *c_str) {
    assert(c_str);

    for (size_t pos = 0; pos < this->size; pos++) {
        if (c_str == this->data[pos].req_word)
            return req_word;
    }

    return nullptr;
}


int List::CheckAndUpdateCapacity() {
    size_t new_capacity = 0;
    if (this->size * SIZE_CAPACITY_DIFF < this->capacity && this->size || this->size == this->capacity) {
        new_capacity       = this->size * SIZE_CAPACITY_DIFF;
        ListElemT* tmp_data = (ListElemT*)realloc(this->data, new_capacity);
        if (!tmp_data)
            return UNABLE_TO_ALLOC;
        else {
            this->data      = tmp_data;
            this->capacity = new_capacity;
        }
    }

    return 0;
}


int List::Insert(const ListElemT* elem) {
	assert(elem);

	const char* found = this->Find(elem->req_word);
	if (found)
	    return ELEM_FOUND;

	int check_size_res = this->CheckSize();
    if (check_size_res)
        return check_size_res;

	this->data[this->size++] = *elem;

	return 0;
}
