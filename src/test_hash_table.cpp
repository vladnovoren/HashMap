#include "test_hash_table.h"



void LoadDicToHashTable(HashTable* hash_table, const DicBuf* dic_buf) {
    assert(hash_table);

    for (size_t word_num = 0; word_num < dic_buf->n_elems; word_num++) {
        if (HashTable_Insert(hash_table, dic_buf->elems[word_num]))
            printf("FATAL ERROR!\n");
    }
}


void OutputBucketsSizes(HashTable* hash_table, const char* func_name,
                        FILE* buckets_sizes_log, FILE* dispersions_log) {
    assert(hash_table);
    assert(buckets_sizes_log);
    assert(dispersions_log);
    assert(func_name);

    double sqrs_sum = 0,
           average  = 0;

    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets;
              ++bucket_num) {
        average  += hash_table->buckets[bucket_num].n_elems;
        sqrs_sum += pow(hash_table->buckets[bucket_num].n_elems, 2);
        fprintf(buckets_sizes_log, "%zu;%zu\n",
                bucket_num, hash_table->buckets[bucket_num].n_elems);
    }

    average  /= hash_table->n_buckets;
    sqrs_sum /= hash_table->n_buckets;
    fprintf(dispersions_log, "%s;%lg\n",
            func_name, sqrt(sqrs_sum - average * average));
}


void TestHashFunc(const HashFuncInfo* hash_func_info, const DicBuf* dic_buf,
                                                      FILE* disp_log) {
    assert(hash_func_info);
    assert(dic_buf);
    assert(disp_log);

    char* sizes_log_name = (char*)calloc(strlen(hash_func_info->hash_func_name)
                                         + CSV_SUFF_LEN, sizeof(char));
    strcat(sizes_log_name, hash_func_info->hash_func_name);
    strcat(sizes_log_name, CSV_SUFF);

    FILE* sizes_log = OpenFile(sizes_log_name, "wb");
    if (!sizes_log)
        return;

    HashTable hash_table = {};
    HashTable_Alloc(&hash_table);
    hash_table.rehash_required = false;
    hash_table.get_hash = hash_func_info->hash_func;

    LoadDicToHashTable(&hash_table, dic_buf);
    OutputBucketsSizes(&hash_table, hash_func_info->hash_func_name,
                       sizes_log, disp_log);
    HashTable_Destruct(&hash_table);
    
    fclose(sizes_log);
}


void TestHashFuncs(const char* dic_file_name, const char* gnuplot_path) {
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
    for (size_t func_num = 0; func_num < N_FUNCS; ++func_num) {
		TestHashFunc(HASH_FUNCS_INFO + func_num, &dic_buf, dispersions_log);
    }

    DicBuf_Destruct(&dic_buf);

    fclose(dispersions_log);
}


void Search(const HashTable* hash_table, const StrArr* requests) {
    assert(hash_table);
    assert(requests);

    for (size_t i = 0; i < 10000; ++i) {
        for (size_t word_num = 0; word_num < requests->n_strs; ++word_num) {
            HashTable_Find(hash_table, (const char*)requests->arr[word_num].c_str);
        }
    }
}


void TestSpeed(const char* dic_file_name, const char* requests_file_name) {
    assert(dic_file_name);
    assert(requests_file_name);

    StrArr requests = FileToStrArr(requests_file_name);
    DicBuf dic_buf = DicBuf_ParseDicFile(dic_file_name);
    HashTable hash_table;
    HashTable_Alloc(&hash_table);
    LoadDicToHashTable(&hash_table, &dic_buf);
    Search(&hash_table, &requests);
    HashTable_Destruct(&hash_table);
    DicBuf_Destruct(&dic_buf);
    DestructStrArr(&requests);
}
