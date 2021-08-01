#include "test_hash_table.h"


void TestHashTable(const char* dic_file_name) {
    assert(dic_file_name);

    Dic dic = ParseDicFile(dic_file_name);
    HashTable hash_table = {};
    HashTableAlloc(&hash_table);
    for (size_t word_num = 0; word_num < dic.n_elems; word_num++)
        HashTableInsert(&hash_table, dic.elems[word_num]);
    
    char* req = (char*)calloc(100, sizeof(char));
    while (true) {
        scanf("%s", req);
        if (!strcmp("q", req))
            break;
        HashTableElemT* found = HashTableFind(&hash_table, req);
        if (!found)
            printf("not found\n");
        else
            printf("translation: %s\n", HashTableFind(&hash_table, req)->translation);
    }

    HashTableDestruct(&hash_table);
    DicDestruct(&dic);
}
