#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H


#include <cstddef>
#include <cstring>

typedef size_t HashT;

struct HashTableElemT {
    const char* req_word;
    const char* translation;
    HashT       hash;
};

typedef HashTableElemT ListElemT;

bool operator==(const ListElemT& first, const ListElemT& second);

bool operator!=(const ListElemT& first, const ListElemT& second);


#endif /* common_header.h */
