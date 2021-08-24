#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H


#include <stddef.h>
#include <string.h>

typedef size_t HashT;

typedef struct HashTableElemT {
    const char* req_word;
    const char* translation;
    HashT       hash;
} HashTableElemT;

typedef HashTableElemT ListElemT;

#define true 1
#define false 0


#endif /* common_header.h */
