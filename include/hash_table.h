#ifndef HASH_TABLE
#define HASH_TABLE

#include "ONEGIN_lib.h"
#include "list.h"


typedef size_t HashT;

const size_t MAX_WORD_LEN      = 100;
const int    POLYNOMIAL_HASH_P = 257;


struct HashTableElem {
    const char* src_word;
    const char* translate;
};

struct HashTable {
    size_t n_elems;
    size_t n_buckets;
    size_t max_load_factor;
    List<HashTableElem>* buckets;
};


HashT PolynomialHash(const char* c_str);

HashT GetHash(const char* c_str);


#endif /* "hash_table.h" */
