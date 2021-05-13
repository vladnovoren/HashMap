#ifndef TEST_HASH_FUNCTIONS
#define TEST_HASH_FUNCTIONS

#include "hash_table.h"
#include "dic_parser.h"
#include "assert.h"

static const size_t N_FUNCS = 6;
static const size_t N_TESTS = 10000;

struct TestStruct {
    const char* file_name;
    HashT (*hash_function)(const char*);
};

void TestHashFunctions(const char* dic_file_name);


#endif /* test_hash_functions.h */
