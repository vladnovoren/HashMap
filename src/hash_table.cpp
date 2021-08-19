#include "hash_table.h"



bool operator==(const ListElemT& first, const ListElemT& second) {
    if (!first.req_word || !second.req_word)
        return !first.req_word && !second.req_word;

    if (!strcmp(first.req_word, second.req_word))
        return true;
    else
        return false;
}


bool operator!=(const ListElemT& first, const ListElemT& second) {
    return !(first == second);
}


size_t HashTable_GetBucketNum(HashTable* hash_table, const HashT hash) {
    assert(hash_table);

    return hash % hash_table->n_buckets;
}


void HashTable_Set(HashTable* hash_table, List* buckets, size_t n_buckets, size_t n_elems, double max_load_factor, HashT (*get_hash)(const char*), bool rehash_required) {
    assert(hash_table);
    assert(get_hash);

    hash_table->buckets = buckets;
    hash_table->n_buckets = n_buckets;
    hash_table->n_elems = n_elems;
    hash_table->max_load_factor = max_load_factor;
    hash_table->get_hash = get_hash;
    hash_table->rehash_required = rehash_required;
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
                              HASH_TABLE_DEFAULT_GET_HASH, true);
    
    return 0;
}


void HashTable_Destruct(HashTable* hash_table) {
    assert(hash_table);

    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; bucket_num++)
        List_Destruct(hash_table->buckets + bucket_num);
    free(hash_table->buckets);
    *hash_table = {};
}


HashTableElemLoc HashTable_Find(HashTable* hash_table, const HashTableElemT elem) {
    assert(hash_table);

    size_t bucket_num   = HashTable_GetBucketNum(hash_table, elem.hash);
    size_t list_phys_id = List_Find(hash_table->buckets + bucket_num, elem);
    return {bucket_num, list_phys_id};
}


HashTableElemLoc HashTable_Find(HashTable* hash_table, const char* req_word) {
    return HashTable_Find(hash_table, {req_word, nullptr, hash_table->get_hash(req_word)});
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
    List   old_bucket = {};
    for (size_t old_bucket_num = 0; old_bucket_num < hash_table->n_buckets; ++old_bucket_num) {
        old_bucket = hash_table->buckets[old_bucket_num];
        for (size_t phys_id = old_bucket.head_phys_id; phys_id != LIST_INVALID_ID; phys_id = List_GetNextPhysId(&old_bucket, phys_id)) {
            new_bucket_num = old_bucket.elems[phys_id].data.hash % new_n_buckets;
            if (List_PushBack(new_buckets + new_bucket_num, old_bucket.elems[phys_id].data) != LIST_NO_ERRORS)
                return HASH_TABLE_LIST_ERROR;
        }
    }

    HashTable old_hash_table = *hash_table;
    HashTable_Destruct(hash_table);
    *hash_table = old_hash_table;
    hash_table->buckets   = new_buckets;
    hash_table->n_buckets = new_n_buckets;

    return HASH_TABLE_NO_ERRORS;
}


int HashTable_CheckRehash(HashTable* hash_table) {
    assert(hash_table);

    if (hash_table->n_elems * 100 > hash_table->n_buckets * hash_table->max_load_factor)
        return HashTable_Rehash(hash_table, hash_table->n_elems * HASH_TABLE_INC_N_ELEMS_MUL);

    return HASH_TABLE_NO_ERRORS;
}


bool HashTable_IsValidLoc(const HashTableElemLoc* loc) {
    assert(loc);
    return loc->list_phys_id != LIST_INVALID_ID;
}


int HashTable_Insert(HashTable* hash_table, const DicElement new_elem) {
    assert(hash_table);

    HashTableElemT new_hash_table_elem = {new_elem.req_word, new_elem.translation, hash_table->get_hash(new_elem.req_word)};
    HashTableElemLoc found_loc = HashTable_Find(hash_table, new_hash_table_elem);
    if (HashTable_IsValidLoc(&found_loc))
        return HASH_TABLE_NO_ERRORS;

    if (hash_table->rehash_required) {
        int check_rehash_res = HashTable_CheckRehash(hash_table);
        if (check_rehash_res != HASH_TABLE_NO_ERRORS)
            return check_rehash_res;
    }
    ++hash_table->n_elems;

    size_t bucket_num = HashTable_GetBucketNum(hash_table, new_hash_table_elem.hash);
    if (List_PushBack(hash_table->buckets + bucket_num, new_hash_table_elem) != LIST_NO_ERRORS)
        return HASH_TABLE_LIST_ERROR;

    return HASH_TABLE_NO_ERRORS;
}


int HashTable_Erase(HashTable* hash_table, const HashTableElemLoc* loc) {
    assert(hash_table);

    return List_EraseByPhysId(hash_table->buckets + loc->bucket_num, loc->list_phys_id);
}


int HashTable_Erase(HashTable* hash_table, const DicElement elem) {
    assert(hash_table);

    HashTableElemLoc found_loc = HashTable_Find(hash_table, elem.req_word);
    if (HashTable_IsValidLoc(&found_loc))
        return HASH_TABLE_NO_ERRORS;
    else
        return HashTable_Erase(hash_table, &found_loc);
}
