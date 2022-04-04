#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "ONEGIN_lib.h"
#include "dic_parser.h"
#include "hash_funcs.h"
#include "common_header.h"
#include "list.h"
#include "hash_map_err_types.h"

const size_t  HASH_MAP_DEFAULT_N_BUCKETS               = 2011;
const size_t  HASH_MAP_DEFAULT_N_ELEMS                 = 0;
const int     HASH_MAP_INC_N_ELEMS_MUL                 = 2;
const int     HASH_MAP_DEFAULT_MAX_LOAD_FACTOR         = 75;
HashT (*const HASH_MAP_DEFAULT_GET_HASH) (const char*) = Crc32Hash;


typedef size_t HashT;

struct HashMap {
    List*  buckets;
    size_t n_buckets;
    size_t n_elems;
    int    max_load_rate;
    HashT  (*get_hash)(const char*);
    bool   rehash_required;
};


size_t      HashMap_GetBucketNum(const HashMap* hash_map, 
                                   const HashT hash);

void        HashMap_Set(HashMap* hash_map, List*  buckets,
                                                 size_t n_buckets,
                                                 size_t n_elems,
                                                 double max_load_rate,
                                                 HashT (*get_hash)(const char*),
                                                 bool   rehash_required);

int         HashMap_Alloc(HashMap* hash_map);

void        HashMap_Destruct(HashMap* hash_map);

const char* HashMap_Find(const HashMap* hash_map, const char* key,
                                                        const HashT hash);

const char* HashMap_Find(const HashMap* hash_map, const char* key);

int         HashMap_Rehash(HashMap* hash_map, size_t new_n_buckets);

int         HashMap_CheckRehash(HashMap* hash_map);

int         HashMap_Insert(HashMap* hash_map, const DicElem new_elem);

void        HashMap_Clear(HashMap* hash_map);

int         HashMap_ReportErr(const int err_code);


#endif /* "hash_map.h" */
