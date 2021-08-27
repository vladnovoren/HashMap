#include "hash_map.h"
#include "hash_map_err_gen.h"



size_t HashMap_GetBucketNum(const HashMap* hash_map, const HashT hash) {
    assert(hash_map);

    return hash % hash_map->n_buckets;
}


void HashMap_Set(HashMap* hash_map, List* buckets, size_t n_buckets,
                 size_t n_elems, double max_load_rate,
                 HashT (*get_hash)(const char*), bool rehash_required) {
    assert(hash_map);
    assert(get_hash);

    hash_map->buckets         = buckets;
    hash_map->n_buckets       = n_buckets;
    hash_map->n_elems         = n_elems;
    hash_map->max_load_rate   = max_load_rate;
    hash_map->get_hash        = get_hash;
    hash_map->rehash_required = rehash_required;
}


int HashMap_Alloc(HashMap* hash_map) {
    List* buckets = (List*)calloc(HASH_MAP_DEFAULT_N_BUCKETS, sizeof(List));
    if (!buckets)
        return HashMap_ReportErr(HASH_MAP_ALLOC_ERR);

    int alloc_res = 0;
    for (size_t i = 0; i < HASH_MAP_DEFAULT_N_BUCKETS; ++i) {
        alloc_res = List_Alloc(buckets + i);
        if (alloc_res)
            return HashMap_ReportErr(alloc_res);
    }

    HashMap_Set(hash_map, buckets,
                          HASH_MAP_DEFAULT_N_BUCKETS,
                          HASH_MAP_DEFAULT_N_ELEMS,
                          HASH_MAP_DEFAULT_MAX_LOAD_FACTOR,
                          HASH_MAP_DEFAULT_GET_HASH,
                          true);
    
    return HASH_MAP_NO_ERRS;
}


void HashMap_Destruct(HashMap* hash_map) {
    assert(hash_map);

    for (size_t i = 0; i < hash_map->n_buckets; ++i)
        List_Destruct(hash_map->buckets + i);

    free(hash_map->buckets);
    *hash_map = {};
}


const char* HashMap_Find(const HashMap* hash_map, const char* key,
                                                  const HashT hash) {
    assert(hash_map);

    size_t i = HashMap_GetBucketNum(hash_map, hash);

    return List_Find(hash_map->buckets + i, key);
}


const char* HashMap_Find(const HashMap* hash_map, const char* key) {
    return HashMap_Find(hash_map, key, hash_map->get_hash(key));
}


int HashMap_Rehash(HashMap* hash_map, size_t new_n_buckets) {
    assert(hash_map);

    List* new_buckets = (List*)calloc(new_n_buckets, sizeof(List));
    if (!new_buckets)
        return HashMap_ReportErr(HASH_MAP_ALLOC_ERR);

    for (size_t i = 0; i < new_n_buckets; ++i)
        if (List_Alloc(new_buckets + i))
            return HashMap_ReportErr(HASH_MAP_LIST_ERR);

    for (size_t i = 0; i < hash_map->n_buckets; ++i) {
        List old_bucket  = hash_map->buckets[i];
        for (size_t j  = old_bucket.head_phys_id;
                    j != LIST_INVALID_ID;
                    j  = List_GetNextPhysId(&old_bucket, j)) {
            size_t new_i = old_bucket.elems[j].data.hash % new_n_buckets;
            if (List_PushBack(new_buckets + new_i, old_bucket.elems[j].data))
                return HashMap_ReportErr(HASH_MAP_LIST_ERR);
        }
    }

    HashMap old_hash_map = *hash_map;
    HashMap_Destruct(hash_map);
    *hash_map            = old_hash_map;
    hash_map->buckets    = new_buckets;
    hash_map->n_buckets  = new_n_buckets;

    return HASH_MAP_NO_ERRS;
}


int HashMap_CheckRehash(HashMap* hash_map) {
    assert(hash_map);

    if (hash_map->n_elems   * 100 >
        hash_map->n_buckets * hash_map->max_load_rate)
        return HashMap_Rehash(hash_map, hash_map->n_elems * 2);

    return HASH_MAP_NO_ERRS;
}


int HashMap_Insert(HashMap* hash_map, const DicElem new_elem) {
    assert(hash_map);
    assert(hash_map->get_hash);

    if (HashMap_Find(hash_map, new_elem.key))
        return HASH_MAP_NO_ERRS;

    HashMapElemT new_hash_map_elem = {
        new_elem.key,
        new_elem.value,
        hash_map->get_hash(new_elem.key)};

    if (hash_map->rehash_required) {
        int check_rehash_res = HashMap_CheckRehash(hash_map);
        if (check_rehash_res)
            return HashMap_ReportErr(check_rehash_res);
    }

    ++hash_map->n_elems;

    size_t i = HashMap_GetBucketNum(hash_map, new_hash_map_elem.hash);
    if (List_PushBack(hash_map->buckets + i, new_hash_map_elem))
        return HashMap_ReportErr(HASH_MAP_LIST_ERR);

    return HASH_MAP_NO_ERRS;
}


void HashMap_Clear(HashMap* hash_map) {
    assert(hash_map);

    HashMap_Destruct(hash_map);
    HashMap_Alloc(hash_map);
}


int HashMap_ReportErr(const int err_code) {
    assert(err_code < HASH_MAP_N_ERR_TYPES);

    fprintf(stderr, "HashMap: %s\n", HASH_MAP_ERR_MSGS[err_code]);

    return err_code;
}
