#include "hash_table.h"



size_t HashTable_GetBucketNum(HashTable* hash_table, const HashT hash) {
    assert(hash_table);

    return hash % hash_table->n_buckets;
}


void HashTable_Set(HashTable* hash_table, List* buckets, size_t n_buckets, size_t n_elems, double max_load_factor, HashT (*get_hash)(const char*)) {
    assert(hash_table);
    assert(get_hash);

    hash_table->buckets = buckets;
    hash_table->n_buckets = n_buckets;
    hash_table->n_elems = n_elems;
    hash_table->max_load_factor = max_load_factor;
    hash_table->get_hash = get_hash;
}


int HashTable_Alloc(HashTable* hash_table) {
    List* buckets = (List*)calloc(HASH_TABLE_DEFAULT_N_BUCKETS, sizeof(List));
    assert(buckets);

    int alloc_res = 0;
    for (size_t bucket_num = 0; bucket_num < HASH_TABLE_DEFAULT_N_BUCKETS; bucket_num++)
        if ((alloc_res = List_Alloc(buckets + bucket_num)))
            return alloc_res;

    HashTable_Set(hash_table, buckets,
                              HASH_TABLE_DEFAULT_N_BUCKETS,
                              HASH_TABLE_DEFAULT_N_ELEMS,
                              HASH_TABLE_DEFAULT_MAX_LOAD_FACTOR,
                              HASH_TABLE_DEFAULT_GET_HASH);
    
    return 0;
}


void HashTable_Destruct(HashTable* hash_table) {
    assert(hash_table);

    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; bucket_num++)
        List_Destruct(hash_table->buckets + bucket_num);
    free(hash_table->buckets);
    *hash_table = {};
}


HashTableElemT HashTable_Find(HashTable* hash_table, const HashTableElemT elem) {
    assert(hash_table);

    size_t bucket_num = HashTable_GetBucketNum(hash_table, elem.hash);
    return List_Find(hash_table->buckets + bucket_num, elem.req_word);
}


HashTableElemT HashTable_Find(HashTable* hash_table, const char* req_word) {
    assert(hash_table);
    assert(req_word);

    size_t bucket_num = HashTable_GetBucketNum(hash_table, hash_table->get_hash(req_word));
    return List_Find(hash_table->buckets + bucket_num, req_word);
}


int HashTable_Rehash(HashTable* hash_table, size_t new_n_buckets) {
    assert(hash_table);

    List* new_buckets = (List*)calloc(new_n_buckets, sizeof(List));
    if (!new_buckets)
        return HASH_TABLE_ALLOC_ERROR;

    int alloc_res = 0;
    for (size_t bucket_num = 0; bucket_num < new_n_buckets; bucket_num++)
        if ((alloc_res = List_Alloc(new_buckets + bucket_num)) != LIST_NO_ERRORS)
            return alloc_res;

    size_t new_bucket_num = 0;
    for (size_t old_bucket_num = 0; old_bucket_num < hash_table->n_buckets; old_bucket_num++) {
        for (size_t old_elem_num = 0; old_elem_num < hash_table->buckets[old_bucket_num].n_elems; old_elem_num++) {
            new_bucket_num = HashTable_GetBucketNum(hash_table, hash_table->buckets[old_bucket_num].elems[old_elem_num].hash);
            if (List_Insert(new_buckets + new_bucket_num, hash_table->buckets[old_bucket_num].elems[old_elem_num]) != LIST_NO_ERRORS)
                return HASH_TABLE_LIST_ERROR;
        }
    }

    HashTable old_hash_table = *hash_table;
    HashTableDestruct(hash_table);
    *hash_table = old_hash_table;
    hash_table->buckets   = new_buckets;
    hash_table->n_buckets = new_n_buckets;

    return HASH_TABLE_NO_ERRORS;
}


int HashTableCheckRehash(HashTable* hash_table, size_t new_n_elems) {
    assert(hash_table);

    if (new_n_elems * 100 > hash_table->n_buckets * hash_table->max_load_factor)
        return HashTableRehash(hash_table, new_n_elems * HASH_TABLE_INC_N_ELEMS_MUL);

    return HASH_TABLE_NO_ERRORS;
}


int HashTableInsert(HashTable* hash_table, const DicElement new_elem) {
    assert(hash_table);

    HashTableElemT new_hash_table_elem = {new_elem.req_word, new_elem.translation, hash_table->get_hash(new_elem.req_word)};
    HashTableElemT* found = HashTableFind(hash_table, new_hash_table_elem);
    if (found)
        return HASH_TABLE_NO_ERRORS;

    int check_rehash_res = HashTableCheckRehash(hash_table, hash_table->n_elems + 1);
    if (check_rehash_res != HASH_TABLE_NO_ERRORS)
        return check_rehash_res;
    ++hash_table->n_elems;

    size_t bucket_num = HashTableGetBucketNum(hash_table, new_hash_table_elem.hash);
    if (!ListInsert(hash_table->buckets + bucket_num, new_hash_table_elem))
        return HASH_TABLE_LIST_ERROR;
    
    return HASH_TABLE_NO_ERRORS;
}
