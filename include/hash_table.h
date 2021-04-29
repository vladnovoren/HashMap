#ifndef HASH_TABLE
#define HASH_TABLE

#include "ONEGIN_lib.h"
#include "list.h"
#include "hash_structures.h"


const size_t MAX_WORD_LEN      = 100;
const int    POLYNOMIAL_HASH_P = 257;


struct HashTable {
    size_t n_elems;
    size_t n_buckets;
    size_t max_load_factor;
    List*  buckets;

    const char* Find(const char* req_word);
    int Rehash();
    int Insert(HashTableElemT* new_elem);
};


HashT PolynomialHash(const char* c_str);

HashT GetHash(const char* c_str);


#endif /* "hash_table.h" */
