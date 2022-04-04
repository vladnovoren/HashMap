#ifndef TEST_HASH_MAP_H
#define TEST_HASH_MAP_H

#include "hash_map.h"
#include "dic_parser.h"
#include <cmath>
#include <unistd.h>
#include <time.h>

static const char* const  DISPERSIONS_LOG_NAME = "dispersions.csv";
static const char* const  CSV_SUFF             = ".csv";
static const size_t CSV_SUFF_LEN         = strlen(CSV_SUFF);


int LoadDicToHashMap(HashMap* hash_map, const DicBuf* dic_buf);

void OutputBucketsSizes(HashMap* hash_map, const char* func_name, FILE* buckets_sizes_log, FILE* dispersions_log);

void TestHashFunc(const HashFuncInfo* hash_func_info, const DicBuf* dic_buf, FILE* dispersions_log);

void TestHashFuncs(const char* dic_file_name, const char* gnuplot_path);

void Search(const HashMap* hash_map, const StrArr* requests);

int TestSpeed(const char* dic_file_name, const char* requests_file_name);


#endif /* test_hash_map.h */
