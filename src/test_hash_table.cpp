#include "test_hash_table.h"


void TestHashTable(const char* dic_file_name) {
    assert(dic_file_name);

    DicBuf dic = DicBuf_ParseDicFile(dic_file_name);
    HashTable hash_table = {};
    HashTable_Alloc(&hash_table);
    for (size_t word_num = 0; word_num < dic.n_elems; word_num++) {
        if (HashTable_Insert(&hash_table, dic.elems[word_num]) != HASH_TABLE_NO_ERRORS)
            printf("FATAL ERROR!\n");
    }
    
    char* req = (char*)calloc(100, sizeof(char));
    while (true) {
        scanf("%s", req);
        if (!strcmp("q", req))
            break;
        HashTableElemT found = HashTable_Find(&hash_table, req);
        if (found == EMPTY_LIST_ELEM)
            printf("not found\n");
        else
            printf("translation: %s\n", found.translation);
    }   

    free(req);
    HashTable_Destruct(&hash_table);
    DicBuf_Destruct(&dic);
}
