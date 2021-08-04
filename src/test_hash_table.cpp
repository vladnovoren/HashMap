#include "test_hash_table.h"


void LoadDicToHashTable(HashTable* hash_table, const DicBuf dic_buf) {
    assert(hash_table);

    for (size_t word_num = 0; word_num < dic_buf.n_elems; word_num++) {
        if (HashTable_Insert(hash_table, dic_buf.elems[word_num]) != HASH_TABLE_NO_ERRORS)
            printf("FATAL ERROR!\n");
    }
}


void OutputBucketsSizes(HashTable* hash_table, FILE* log) {
    assert(hash_table);
    assert(log);

    for (size_t bucket_num = 0; bucket_num < hash_table->n_buckets; ++bucket_num)
        fprintf(log, "%zu;%zu\n", bucket_num, hash_table->buckets[bucket_num].n_elems);
}


void TestHashFunction(HashT (*const hash_function) (const char*), const char* file_name, const DicBuf dic_buf) {
    assert(file_name);
    assert(hash_function);

    FILE* log = OpenFile(file_name, "wb");
    if (!log)
        return;
    
    HashTable hash_table = {};
    HashTable_Alloc(&hash_table);
    hash_table.get_hash = hash_function;
    LoadDicToHashTable(&hash_table, dic_buf);
    OutputBucketsSizes(&hash_table, log);
    HashTable_Destruct(&hash_table);
    
    fclose(log);
}


void TestHashTable(const char* dic_file_name) {
    assert(dic_file_name);

    DicBuf dic_buf = DicBuf_ParseDicFile(dic_file_name);
    TestHashFunction(ConstantHash, "../gnuplot/ConstantHash.csv", dic_buf);
    TestHashFunction(FirstCharHash, "../gnuplot/FirstCharHash.csv", dic_buf);
    TestHashFunction(ASCII_SumHash, "../gnuplot/ASCII_SumHash.csv", dic_buf);
    TestHashFunction(PolynomialHash, "../gnuplot/PolynomialHash.csv", dic_buf);
    TestHashFunction(FNVA1aHash, "../gnuplot/FNVA1aHash.csv", dic_buf);
    TestHashFunction(strlen, "../gnuplot/strlenHash.csv", dic_buf);
    DicBuf_Destruct(&dic_buf);
}
