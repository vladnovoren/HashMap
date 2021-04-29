#include "hash_table.h"


HashT PolynomialHash(const char* c_str) {
	static HashT p_powers[MAX_WORD_LEN] = {};
	if (!p_powers[0]) {
		p_powers[0] = 1;
		for (size_t pos = 1; pos < MAX_WORD_LEN; pos++)
			p_powers[pos] = p_powers[pos - 1] * POLYNOM_HASH_P;
	}

	HashT symb_num = 0;
	HashT hash     = 0;
	while (c_str[symb_num])
		hash += p_powers[symb_num++];

	return hash;
}


HashT GetHash(const char* c_str) {
    return PolynomialHash(c_str);
}


const char* HashTable::Find(const char* req_word) {
    assert(req_word);

    HashT pos = GetHash(req_word) % this->n_buckets;

    return this->buckets[pos].Find(req_word);
}


int HashTable::Rehash() {
    size_t new_n_buckets = this->n_buckets * 2;
    List* new_buckets = (List*)calloc(new_n_buckets, sizeof(List));
    if (!new_buckets)
        return UNABLE_TO_ALLOC;

    for (size_t bucket_num = 0; bucket_num < this->n_buckets; bucket_num++) {
        for (size_t elem_num = 0; elem_num < this->buckets[bucket_num].size; elem_num++) {

        }
    }
}


int HashTable::Insert(HashTableElemT *new_elem) {
    assert(new_elem);

    HashT pos = GetHash(new_elem->req_word) % this->n_buckets;
    const char* found = this->Find(new_elem->req_word);
    if (found)
        return ELEM_FOUND;

    this->n_elems++;

    return 0;
}
