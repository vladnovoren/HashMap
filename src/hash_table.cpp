#include "hash_table.h"


HashT PolynomialHash(const char* c_str) {
	static HashT p_powers[MAX_WORD_LEN] = {};
	if (!p_powers[0]) {
		p_powers[0] = 1;
		for (size_t pos = 1; pos < MAX_WORD_LEN; pos++)
			p_powers[pos] = p_powers[pos - 1] * POLYNOMIAL_HASH_P;
	}

	HashT symb_num = 0;
	HashT hash     = 0;
	while (c_str[symb_num]) {
        hash += p_powers[symb_num] * c_str[symb_num];
        symb_num++;
    }

	return hash;
}


HashT GetHash(const char* c_str) {
    return PolynomialHash(c_str);
}

int HashTable::Construct() {
    List* buckets = (List*)calloc(DEFAULT_N_BUCKETS, sizeof(List));
    if (!buckets)
        return HASH_TABLE_UNABLE_TO_ALLOC;

    this->Set(DEFAULT_N_ELEMS, DEFAULT_N_BUCKETS, DEFAULT_MAX_LOAD_FACTOR, buckets);

    for (size_t bucket_num = 0; bucket_num < this->n_buckets; bucket_num++) {
        int construct_res = buckets[bucket_num].Construct();
        if (construct_res)
            return HASH_TABLE_LIST_ERROR;
    }

    return HASH_TABLE_NO_ERRORS;
}


void HashTable::Set(size_t n_elems, size_t n_buckets, double max_load_factor, List*  buckets) {
    this->n_elems         = n_elems;
    this->n_buckets       = n_buckets;
    this->max_load_factor = max_load_factor;
    this->buckets         = buckets;
}


void HashTable::Destruct() {
    for (size_t bucket_num = 0; bucket_num < this->n_buckets; bucket_num++)
        this->buckets[bucket_num].Destruct();

    free(this->buckets);
}


HashTableElemT* HashTable::Find(const char* req_word) {
    assert(req_word);

    HashT pos = GetHash(req_word) % this->n_buckets;

    return this->buckets[pos].Find(req_word);
}


int HashTable::Rehash() {
    size_t new_n_buckets = this->n_buckets * 2;
    List* new_buckets    = (List*)calloc(new_n_buckets, sizeof(List));
    if (!new_buckets)
        return HASH_TABLE_UNABLE_TO_ALLOC;

    for (size_t bucket_num = 0; bucket_num < this->n_buckets; bucket_num++) {
        if (this->buckets[bucket_num].Construct())
            return HASH_TABLE_UNABLE_TO_ALLOC;

        for (size_t elem_num = 0; elem_num < this->buckets[bucket_num].size; elem_num++) {
            HashT new_pos            = this->buckets[bucket_num].data[elem_num].hash % new_n_buckets;
            HashTableElemT* inserted = new_buckets[new_pos].Insert(this->buckets[bucket_num].data[elem_num]);
            if (!inserted)
                return HASH_TABLE_LIST_ERROR;
        }
        this->buckets[bucket_num].Destruct();
    }

    this->Destruct();
    this->n_buckets = new_n_buckets;
    this->buckets   = new_buckets;

    return HASH_TABLE_NO_ERRORS;
}


int HashTable::Insert(const HashTableElemT new_elem) {
    const HashTableElemT* found = this->Find(new_elem.req_word);
    if (!found) {
        if ((double)(this->n_elems + 1) / this->n_buckets > this->max_load_factor) {
            int rehash_res = this->Rehash();
            if (rehash_res)
                return rehash_res;
        }
        HashT pos = GetHash(new_elem.req_word) % this->n_buckets;
        ListElemT* inserted = this->buckets[pos].Insert(new_elem);
        if (!inserted)
            return HASH_TABLE_LIST_ERROR;
    }

    return HASH_TABLE_NO_ERRORS;
}
