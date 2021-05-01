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

    for (size_t i = 0; i < dic.size; i++) {
        HashTableElemT* found = hash_table.Find(dic.data[i].req_word);
//        if (found)
//            printf("req_word: %s, translation: %s\n", dic.data[i].req_word, found->translation);
//        else
//            printf("translation of \"%s\" word not found\n", dic.data[i].req_word);
    }

    dic.Destruct();
    hash_table.Destruct();

	return 0;
}
