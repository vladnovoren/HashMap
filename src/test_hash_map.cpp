#include "test_hash_map.h"



int LoadDicToHashMap(HashMap* hash_map, const DicBuf* dic_buf) {
    assert(hash_map);
    assert(dic_buf);
    assert(dic_buf->n_elems);

    for (size_t word_num = 0; word_num < dic_buf->n_elems; word_num++) {
        int ins_res = HashMap_Insert(hash_map, dic_buf->elems[word_num]);
        if (ins_res)
            return ins_res;
    }

    return 0;
}


void OutputBucketsSizes(HashMap* hash_map, const char* func_name,
                        FILE* buckets_sizes_log, FILE* dispersions_log) {
    assert(hash_map);
    assert(buckets_sizes_log);
    assert(dispersions_log);
    assert(func_name);

    double sqrs_sum = 0,
           average  = 0;

    for (size_t bucket_num = 0; bucket_num < hash_map->n_buckets;
              ++bucket_num) {
        average  += hash_map->buckets[bucket_num].n_elems;
        sqrs_sum += pow(hash_map->buckets[bucket_num].n_elems, 2);
        fprintf(buckets_sizes_log, "%zu;%zu\n",
                bucket_num, hash_map->buckets[bucket_num].n_elems);
    }

    average  /= hash_map->n_buckets;
    sqrs_sum /= hash_map->n_buckets;
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

    HashMap hash_map = {};
    HashMap_Alloc(&hash_map);
    hash_map.rehash_required = false;
    hash_map.get_hash = hash_func_info->hash_func;

    LoadDicToHashMap(&hash_map, dic_buf);
    OutputBucketsSizes(&hash_map, hash_func_info->hash_func_name,
                       sizes_log, disp_log);
    HashMap_Destruct(&hash_map);
    
    fclose(sizes_log);
}


void TestHashFuncs(const char* dic_file_name, const char* gnuplot_path) {
    assert(dic_file_name);
    assert(gnuplot_path);

    if (chdir(gnuplot_path)) {
        printf("err: unable to enter entered gnuplot directory\n");
        return;
    }

    FILE* dispersions_log = OpenFile(DISPERSIONS_LOG_NAME, "wb");
    if (!dispersions_log)
        return;

    DicBuf dic_buf = {};
    DicBuf_ParseDicFile(&dic_buf, dic_file_name);
    for (size_t func_num = 0; func_num < N_FUNCS; ++func_num) {
		TestHashFunc(HASH_FUNCS_INFO + func_num, &dic_buf, dispersions_log);
    }

    DicBuf_Destruct(&dic_buf);

    fclose(dispersions_log);
}


void PrepareAlignedRequests(StrArr* src) {
    assert(src);

    StrArr aligned = AllocStrArr(src->n_strs);
    for (size_t i = 0; i < aligned.n_strs; ++i) {
        aligned.arr[i] = AllocStr(63);
        strncpy(aligned.arr[i].c_str, src->arr[i].c_str, 63);
    }
    DestructStrArr(src);
    *src = aligned;
}


void Search(const HashMap* hash_map, const StrArr* requests) {
    assert(hash_map);
    assert(requests);

    clock_t start_t = clock();
    for (size_t i = 0; i < 10000; ++i)
        for (size_t word_num = 0; word_num < requests->n_strs; ++word_num)
            HashMap_Find(hash_map, requests->arr[word_num].c_str);

    clock_t end_t  = clock();
    printf("search time: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
}


int TestSpeed(const char* dic_file_name, const char* requests_file_name) {
    assert(dic_file_name);
    assert(requests_file_name);

    StrArr requests = FileToStrArr(requests_file_name);
    if (!requests.n_strs)
        return 1;

    PrepareAlignedRequests(&requests);

    DicBuf dic_buf  = {};
    int parse_res = DicBuf_ParseDicFile(&dic_buf, dic_file_name);
    if (parse_res)
        return parse_res;

    HashMap hash_map = {};
    int alloc_res = HashMap_Alloc(&hash_map);
    if (alloc_res)
        return alloc_res;

    int load_res = LoadDicToHashMap(&hash_map, &dic_buf);
    if (load_res)
        return load_res;

    Search(&hash_map, &requests);

    HashMap_Destruct(&hash_map);
    DicBuf_Destruct(&dic_buf);
    DestructStrArr(&requests);

    return 0;
}
