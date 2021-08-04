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

bool operator== (const ListElemT& first, const ListElemT& second) {
    if (first.hash == second.hash && !strcmp(first.req_word, second.req_word) && !strcmp(first.translation, second.translation))
        return true;
    else
        return false;
}


#endif /* common_header.h */
