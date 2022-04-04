#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H


#include <stddef.h>
#include <string.h>

typedef size_t HashT;


typedef struct HashMapElemT {
    char* key;
    char* value;
    HashT hash;
} HashMapElemT;

typedef HashMapElemT ListElemT;


#endif /* common_header.h */
