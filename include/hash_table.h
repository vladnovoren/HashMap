#ifndef HASH_TABLE
#define HASH_TABLE

#include "ONEGIN_lib.h"
#include "list.h"
#include "hash_table_structures.h"
#include "dic_parser.h"


const size_t MAX_WORD_LEN            = 100000;
const int    POLYNOMIAL_HASH_P       = 257;
const size_t DEFAULT_N_BUCKETS       = 2011;
const size_t DEFAULT_N_ELEMS         = 0;
const double DEFAULT_MAX_LOAD_FACTOR = 0.95;


enum HashTableStates {
    HASH_TABLE_NO_ERRORS,
    HASH_TABLE_UNABLE_TO_ALLOC,
    HASH_TABLE_LIST_ERROR
};


struct HashTableState {
    int    err_code;
    size_t broken_list_num;
};

struct HashTable {
    size_t         n_elems;
    size_t         n_buckets;
    double         max_load_factor;
    List*          buckets;
    HashTableState state;


    HashTableElemT* Find(const char* req_word);
    int             Rehash();
    int             Insert(const HashTableElemT new_elem);
};


int            HashTableAlloc();

void           HashTableDestruct();

void           HashTableSet(size_t n_elems, size_t n_buckets, double max_load_factor, List*  buckets);

int            HashTableInsert(const HashTableElemT new_elem);

HashTableElemT HashTableFind(const char* req_word);

int            HashTableRehash();


HashT PolynomialHash(const char* c_str);

HashT GetHash(const char* c_str);


#endif /* "hash_table.h" */
