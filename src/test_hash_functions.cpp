#include "test_hash_functions.h"


void TestHashFunctions(const char* dic_file_name) {
    assert(dic_file_name);

    Dic dic = ParseDicFile(dic_file_name);
    HashTable hash_table = {};
    hash_table.Construct();

    const TestStruct hash_functions[N_FUNCS] = {
        {"ASCII_Sum", ASCII_Sum},
        {"Constant", Constant},
        {"FirstChar", FirstChar},
        {"FNVA1a", FNVA1a},
        {"Polynomial", Polynomial},
        {"strlen", strlen}
    };

    for (size_t str_num = 0; str_num < N_TESTS; str_num++) {
        size_t word_num = rand() % dic.size;
        hash_table.Insert({dic.data[word_num].req_word, dic.data[word_num].translation, 0});
    }

    for (size_t func_num   = 0; func_num < N_FUNCS; func_num++) {
        hash_table.GetHash = hash_functions[func_num].hash_function;
        hash_table.Rehash();
        char* csv_full_path = (char*)calloc(32, sizeof(char));
        strcat(csv_full_path, "../gnuplot/");
        strcat(csv_full_path, hash_functions[func_num].file_name);
        strcat(csv_full_path, ".csv");
        FILE* csv_file = fopen(csv_full_path, "wb");
        
        for (size_t bucket_num = 0; bucket_num < hash_table.n_buckets; bucket_num++)
            fprintf(csv_file, "%zu;%zu\n", bucket_num + 1, hash_table.buckets[bucket_num].size);

        char* gpi_full_path = (char*)calloc(64, sizeof(char));
        strcat(gpi_full_path, "../gnuplot/");
        strcat(gpi_full_path, hash_functions[func_num].file_name);
        strcat(gpi_full_path, ".gpi");

        system(gpi_full_path);
        
        free(gpi_full_path);
        free(csv_full_path);
        fclose(csv_file);
    }

    system("../gnuplot/strlen_scaled.gpi");
    system("../gnuplot/FirstCharScaled.gpi");

    hash_table.Destruct();
    dic.Destruct();
}
