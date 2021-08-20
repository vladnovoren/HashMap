#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "ONEGIN_lib.h"
#include "dic_parser.h"
#include "hash_functions.h"
#include "common_header.h"
#include "list.h"

const size_t  HASH_TABLE_DEFAULT_N_BUCKETS               = 2011;
const size_t  HASH_TABLE_DEFAULT_N_ELEMS                 = 0;
const int     HASH_TABLE_INC_N_ELEMS_MUL                 = 2;
const int     HASH_TABLE_DEFAULT_MAX_LOAD_FACTOR         = 75;
HashT (*const HASH_TABLE_DEFAULT_GET_HASH) (const char*) = Crc32Hash;

enum HashTable_States {
    HASH_TABLE_NO_ERRORS,
    HASH_TABLE_ALLOC_ERROR,
    HASH_TABLE_LIST_ERROR
};

typedef size_t HashT;

struct HashTable {
    List*  buckets;
    size_t n_buckets;
    size_t n_elems;
    int    max_load_factor;
    HashT  (*get_hash)(const char*);
    bool   rehash_required;
};

struct HashTableElemLoc {
    size_t bucket_num;
    size_t list_phys_id;
};


bool             operator==(const ListElemT& first, const ListElemT& second);

bool             operator!=(const ListElemT& first, const ListElemT& second);

size_t           HashTable_GetBucketNum(const HashTable* hash_table, const HashT hash);

void             HashTable_Set(HashTable* hash_table, List* buckets, size_t n_buckets,
                               size_t n_elems, double max_load_factor,
                               HashT (*get_hash)(const char*), bool rehash_required);

int              HashTable_Alloc(HashTable* hash_table);

void             HashTable_Destruct(HashTable* hash_table);

HashTableElemLoc HashTable_Find(const HashTable* hash_table, const HashTableElemT elem);

HashTableElemLoc HashTable_Find(const HashTable* hash_table, const char* req_word);

int              HashTable_Rehash(HashTable* hash_table, size_t new_n_buckets);

int              HashTable_CheckRehash(HashTable* hash_table);

bool             HashTable_IsValidLoc(const HashTableElemLoc* loc);

int              HashTable_Insert(HashTable* hash_table, const DicElement new_elem);

int              HashTable_Erase(HashTable* hash_table, const HashTableElemLoc* loc);

int              HashTable_Erase(HashTable* hash_table, const DicElement elem);

void             HashTable_Clear(HashTable* hash_table);


#endif /* "hash_table.h" */
