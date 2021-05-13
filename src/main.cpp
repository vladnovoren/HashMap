#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "dic_parser.h"


int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("no dictionary file\n");
        return 1;
    }

    Dic dic = ParseDicFile(argv[1]);
    HashTable hash_table = {};
    hash_table.Construct();

    for (size_t str_num = 0; str_num < dic.size; str_num++) {
        hash_table.Insert({dic.data[str_num].req_word, dic.data[str_num].translation, 0});
    }

    FILE* csv_file = fopen("../gnuplot/polynomial.csv", "wb");
    for (size_t bucket_num = 0; bucket_num < hash_table.n_buckets; bucket_num++)
        fprintf(csv_file, "%zu;%zu\n", bucket_num + 1, hash_table.buckets[bucket_num].size);

    dic.Destruct();
    hash_table.Destruct();
    free(csv_file);

	return 0;
}
