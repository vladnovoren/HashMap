#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"


int main () {
    const HashTableElemT dic[8] = {
            {"hello", "привет", 0},
            {"apple", "яблоко", 0},
            {"laptop", "ноутбук", 0},
            {"phone", "телефон", 0},
            {"application", "приложение", 0},
            {"keyboard", "клавиатура", 0},
            {"mouse", "мышь", 0},
            {"display", "отображать", 0}
    };
    HashTable hash_table = {};
    hash_table.Construct();
//    for (size_t i = 0; i < 8; i++)
//        hash_table.Insert(dic + i);

    for (size_t i = 0; i < 8; i++) {
        HashTableElemT* found = hash_table.Find(dic[i].req_word);
        if (found)
            printf("req_word: %s, translation: %s\n", dic[i].req_word, found->translation);
        else
            printf("translation of \"%s\" word not found\n", dic[i].req_word);
    }

    hash_table.Destruct();
	return 0;
}
