#include "test_hash_table.h"



void LoadDicToHashTable(HashTable* hash_table, const DicBuf* dic_buf) {
    assert(hash_table);

    for (size_t word_num = 0; word_num < dic_buf->n_elems; word_num++) {
        if (HashTable_Insert(hash_table, dic_buf->elems[word_num]) != HASH_TABLE_NO_ERRORS)
            printf("FATAL ERROR!\n");
    }
}


void OutputBucketsSizes(HashTable* hash_table, const char* function_name, FILE* buckets_sizes_log, FILE* dispersions_log) {
    assert(hash_table);
    assert(buckets_sizes_log);
    assert(dispersions_log);
    assert(function_name);

    double sqrs_sum = 0,
           average  = 0;
    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; ++bucket_num) {
        average  += hash_table->buckets[bucket_num].n_elems;
        sqrs_sum += pow(hash_table->buckets[bucket_num].n_elems, 2);
        fprintf(buckets_sizes_log, "%zu;%zu\n", bucket_num, hash_table->buckets[bucket_num].n_elems);
    }
    average  /= hash_table->n_buckets;
    sqrs_sum /= hash_table->n_buckets;
    fprintf(dispersions_log, "%s;%lg\n", function_name, sqrt(sqrs_sum - average * average));
}


void TestHashFunction(const HashFunctionInfo* hash_function_info, const DicBuf* dic_buf, FILE* dispersions_log) {
    assert(hash_function_info);
    assert(dic_buf);
    assert(dispersions_log);

    char* buckets_sizes_log_name = (char*)calloc(strlen(hash_function_info->hash_function_name) + CSV_SUFF_LEN, sizeof(char));
    strcat(buckets_sizes_log_name, hash_function_info->hash_function_name);
    strcat(buckets_sizes_log_name, CSV_SUFF);

    FILE* buckets_sizes_log = OpenFile(buckets_sizes_log_name, "wb");
    if (!buckets_sizes_log)
        return;

    HashTable hash_table = {};
    HashTable_Alloc(&hash_table);
    hash_table.rehash_required = false;
    hash_table.get_hash = hash_function_info->hash_function;
    LoadDicToHashTable(&hash_table, dic_buf);
    OutputBucketsSizes(&hash_table, hash_function_info->hash_function_name, buckets_sizes_log, dispersions_log);
    HashTable_Destruct(&hash_table);
    
    fclose(buckets_sizes_log);
}


void TestHashFunctions(const char* dic_file_name, const char* gnuplot_path) {
    assert(dic_file_name);
    assert(gnuplot_path);

    if (chdir(gnuplot_path)) {
        printf("error: unable to enter entered gnuplot directory\n");
        return;
    }

    FILE* dispersions_log = OpenFile(DISPERSIONS_LOG_NAME, "wb");
    if (!dispersions_log)
        return;

    DicBuf dic_buf = DicBuf_ParseDicFile(dic_file_name);
    for (size_t func_num = 0; func_num < N_FUNCTIONS; ++func_num) {
		TestHashFunction(HASH_FUNCTIONS_INFO + func_num, &dic_buf, dispersions_log);
    }

    DicBuf_Destruct(&dic_buf);

    fclose(dispersions_log);
}


void TestSpeed(const char* dic_file_name) {
    assert(dic_file_name);

    DicBuf dic_buf = DicBuf_ParseDicFile(dic_file_name);
    HashTable hash_table;
    HashTable_Alloc(&hash_table);
    LoadDicToHashTable(&hash_table, &dic_buf);
    HashTable_Destruct(&hash_table);
    DicBuf_Destruct(&dic_buf);
}
