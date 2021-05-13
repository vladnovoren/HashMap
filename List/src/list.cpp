#include "list.h"



ListElemT* List::Find(const char *c_str) {
    assert(c_str);

    for (size_t pos = 0; pos < this->size; pos++) {
        if (!strcmp(c_str, this->data[pos].req_word))
            return this->data + pos;
    }

    return nullptr;
}


int List::CheckAndUpdateCapacity() {
    size_t new_capacity = 0;
    if (this->size * SIZE_CAPACITY_DIFF * SIZE_CAPACITY_DIFF < this->capacity && this->size || this->size == this->capacity) {
        new_capacity        = this->size * SIZE_CAPACITY_DIFF;
        ListElemT* tmp_data = (ListElemT*)realloc(this->data, new_capacity * sizeof(ListElemT));
        if (tmp_data) {
            this->data     = tmp_data;
            this->capacity = new_capacity;
        } else
            return LIST_UNABLE_TO_ALLOC;
    }

    return 0;
}


ListElemT* List::Insert(const ListElemT elem) {
	ListElemT* found = this->Find(elem.req_word);
	if (found)
        return found;

    if (this->CheckAndUpdateCapacity())
        return nullptr;

	this->data[this->size] = elem;

	return this->data + this->size++;
}


int List::Construct() {
    ListElemT* data = (ListElemT*)calloc(START_LIST_CAPACITY, sizeof(ListElemT));
    if (!data)
        return LIST_UNABLE_TO_ALLOC;

    this->size     = START_LIST_SIZE;
    this->capacity = START_LIST_CAPACITY;
    this->data     = data;

    return 0;
}


void List::Destruct() {
    free(this->data);
    this->capacity = 0;
    this->size     = 0;
}
