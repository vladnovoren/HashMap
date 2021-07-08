#include "hash_table.h"


size_t HashTableGetBucketNum(HashTable* hash_table, const char* req_word) {
    assert(hash_table);
    assert(req_word);

    return hash_table->get_hash(req_word) % hash_table->n_buckets;
}


void HashTableSet(HashTable* hash_table, List* buckets, size_t n_buckets, size_t n_elems, double max_load_factor, HashT (*get_hash)(const char*)) {
    assert(hash_table);
    assert(get_hash);

    hash_table->buckets = buckets;
    hash_table->n_buckets = n_buckets;
    hash_table->n_elems = n_elems;
    hash_table->max_load_factor = max_load_factor;
    hash_table->get_hash = get_hash;
}


int HashTableAlloc(HashTable* hash_table) {
    List* buckets = (List*)calloc(HASH_TABLE_DEFAULT_N_BUCKETS, sizeof(List));
    assert(buckets);

    int alloc_res = 0;
    for (size_t bucket_num = 0; bucket_num < HASH_TABLE_DEFAULT_N_BUCKETS; bucket_num++)
        if ((alloc_res = ListAlloc(buckets + bucket_num)))
            return alloc_res;

    HashTableSet(hash_table, buckets,
                             HASH_TABLE_DEFAULT_N_BUCKETS,
                             HASH_TABLE_DEFAULT_N_ELEMS,
                             HASH_TABLE_DEFAULT_MAX_LOAD_FACTOR,
                             HASH_TABLE_DEFAULT_GET_HASH);
    
    return 0;
}


void HashTableDestruct(HashTable* hash_table) {
    assert(hash_table);

    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; bucket_num++)
        ListDestruct(hash_table->buckets + bucket_num);
    free(hash_table->buckets);
    *hash_table = {};
}


HashTableElemT* HashTableFind(HashTable* hash_table, const char* req_word) {
    assert(hash_table);
    assert(req_word);

    size_t bucket_num = HashTableGetBucketNum(hash_table, req_word);
    return ListFind(hash_table->buckets + bucket_num, req_word);
}


int HashTableRehash(HashTable* hash_table, size_t new_n_buckets) {
    assert(hash_table);

    List* new_buckets = (List*)calloc(new_n_buckets, sizeof(List));
    assert(new_buckets);

    size_t new_bucket_num = 0;
    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; bucket_num++) {
        for (size_t elem_num = 0; elem_num < hash_table->buckets[bucket_num].n_elems; elem_num++) {
            new_bucket_num = hash_table->buckets[bucket_num].elems[elem_num].hash % new_n_buckets;
            if (!ListInsert(new_buckets + new_bucket_num, hash_table->buckets[bucket_num].elems[elem_num]))
                return HASH_TABLE_LIST_ERROR;
        }
    }

    hash_table->buckets   = new_buckets;
    hash_table->n_buckets = new_n_buckets;

    return HASH_TABLE_NO_ERRORS;
}


int HashTableCheckRehash(HashTable* hash_table) {
    assert(hash_table);

    if (hash_table->n_elems * 100 > hash_table->n_buckets * hash_table->max_load_factor)
        return HashTableRehash(hash_table, hash_table->n_elems * HASH_TABLE_INC_N_ELEMS_MUL);
    
    return HASH_TABLE_NO_ERRORS;
}


int HashTableInsert(HashTable* hash_table, const HashTableElemT new_elem) {
    assert(hash_table);

    HashTableElemT* found = HashTableFind(hash_table, new_elem.req_word);
    if (found)
        return HASH_TABLE_NO_ERRORS;

    ++hash_table->n_elems;
    int check_rehash_res = HashTableCheckRehash(hash_table);
    if (check_rehash_res != HASH_TABLE_NO_ERRORS)
        return check_rehash_res;

    size_t bucket_num = HashTableGetBucketNum(hash_table, new_elem.req_word);
    if (!ListInsert(hash_table->buckets + bucket_num, new_elem))
        return HASH_TABLE_LIST_ERROR;
    
    return HASH_TABLE_NO_ERRORS;
}
