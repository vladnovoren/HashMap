#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H


#include <cstddef>

typedef size_t HashT;

struct HashTableElemT {
    const char* req_word;
    const char* translation;
    HashT       hash;
};

typedef HashTableElemT ListElemT;


#endif /* common_header.h */
