#ifndef HASH_TABLE
#define HASH_TABLE

#include "ONEGIN_lib.h"
#include "list.h"
#include "hash_table_structures.h"
#include "dic_parser.h"

const size_t FNV_OFFSET_BASICS       = 14695981039346656037;
const size_t FNV_PRIME               = 1099511628211;
const size_t HASH_CONST              = 12;
const size_t MAX_WORD_LEN            = 100000;
const int    POLYNOMIAL_HASH_P       = 257;
const size_t DEFAULT_N_BUCKETS       = 2011;
const size_t DEFAULT_N_ELEMS         = 0;
const double DEFAULT_MAX_LOAD_FACTOR = 0.75;


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

    int  Construct();
    void Set(size_t n_elems, size_t n_buckets, double max_load_factor, List*  buckets, HashT (*hash_function)(const char*));
    void Destruct();

    HashTableElemT* Find(const char* req_word);
    int             Rehash(size_t new_n_buckets);
    int             Insert(const HashTableElemT new_elem);

    HashT (*GetHash)(const char*);
};


HashT Constant(const char* c_str);

HashT FirstChar(const char* c_str);

HashT ASCII_Sum(const char* c_str);

HashT Polynomial(const char* c_str);

HashT FNVA1a(const char* c_str);


#endif /* "hash_table.h" */
