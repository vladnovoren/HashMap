#include "test_hash_table.h"





void TestHashTable(const char* dic_file_name) {
    assert(dic_file_name);

    Dic dic = ParseDicFile(dic_file_name);
    HashTable hash_table = {};
    HashTableAlloc(&hash_table);
    for (size_t word_num = 0; word_num < dic.n_elems; word_num++)
        HashTableInsert(&hash_table, dic.elems[word_num]);
    
    for (size_t word_num = 0; word_num < dic.n_elems; word_num++) {
        HashTableElemT* found = HashTableFind(&hash_table, dic.elems[word_num].req_word);
        printf("word: %s, translation: %s\n", found->req_word, found->translation);
    }

    HashTableDestruct(&hash_table);
    DicDestruct(&dic);
}
