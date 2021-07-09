#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "ONEGIN_lib.h"
#include "dic_parser.h"
#include "hash_functions.h"
#include "list.h"


const size_t HASH_TABLE_DEFAULT_N_BUCKETS                = 2011;
const size_t HASH_TABLE_DEFAULT_N_ELEMS                  = 0;
const int    HASH_TABLE_INC_N_ELEMS_MUL                  = 2;
const int    HASH_TABLE_DEFAULT_MAX_LOAD_FACTOR          = 75;
HashT (*const HASH_TABLE_DEFAULT_GET_HASH) (const char*) = PolynomialHash;


enum HashTableStates {
    HASH_TABLE_NO_ERRORS,
    HASH_TABLE_UNABLE_TO_ALLOC,
    HASH_TABLE_LIST_ERROR
};

typedef size_t HashT;

struct HashTable {
    List*  buckets;
    size_t n_buckets;
    size_t n_elems;
    int max_load_factor;
    HashT (*get_hash)(const char*);
};



inline size_t HashTableGetBucketNum(HashTable* hash_table, const HashT hash);

void HashTableSet(HashTable* hash_table, List* buckets, size_t n_buckets, size_t n_elems, double max_load_factor, HashT (*get_hash)(const char*));

int HashTableAlloc(HashTable* hash_table);

void HashTableDestruct(HashTable* hash_table);

HashTableElemT* HashTableFind(HashTable* hash_table, const HashTableElemT elem);

HashTableElemT* HashTableFind(HashTable* hash_table, const char* req_word);

int HashTableRehash(HashTable* hash_table, size_t new_n_buckets);

inline int HashTableCheckRehash(HashTable* hash_table, size_t new_n_elems);

int HashTableInsert(HashTable* hash_table, const DicElement new_elem);




#endif /* "hash_table.h" */
