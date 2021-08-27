#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H


#include <stddef.h>
#include <string.h>

typedef size_t HashT;

typedef struct HashMapElemT {
    const char* key;
    const char* value;
    HashT       hash;
} HashMapElemT;

typedef HashMapElemT ListElemT;

#define true 1
#define false 0


#endif /* common_header.h */
