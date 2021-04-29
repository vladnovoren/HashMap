#ifndef HASH_STRUCTURES_H
#define HASH_STRUCTURES_H


typedef size_t HashT;

struct HashTableElemT {
    const char* req_word;
    const char* translation;
    HashT       hash;
};


#endif /* hash_structures.h */
