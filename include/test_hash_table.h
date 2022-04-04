#ifndef TEST_HASH_TABLE_H
#define TEST_HASH_TABLE_H

#include "hash_table.h"
#include "dic_parser.h"
#include "math.h"
#include "unistd.h"

static const char * const  DISPERSIONS_LOG_NAME = "dispersions.csv";
static const char * const  CSV_SUFF             = ".csv";
static const size_t CSV_SUFF_LEN         = strlen(CSV_SUFF);


void LoadDicToHashTable(HashTable* hash_table, const DicBuf* dic_buf);

void OutputBucketsSizes(HashTable* hash_table, const char* function_name, FILE* buckets_sizes_log, FILE* dispersions_log);

void TestHashFunction(const HashFunctionInfo* hash_function_info, const DicBuf* dic_buf, FILE* dispersions_log);

void TestHashFunctions(const char* dic_file_name, const char* gnuplot_path);

void Search(const HashTable* hash_table, const StrArr* requests);

void TestSpeed(const char* dic_file_name, const char* requests_file_name);


#endif /* test_hash_table.h */
