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

    // printf("\n----------\n");

    // ListElemT cur_elem = {};
    // for (size_t bucket_num = 0; bucket_num < hash_table.n_buckets; ++bucket_num) {
    //     for (size_t phys_id = hash_table.buckets[bucket_num].head_phys_id; phys_id != LIST_INVALID_ID; phys_id = hash_table.buckets[bucket_num].elems[phys_id].next_phys_id) {
    //         cur_elem = hash_table.buckets[bucket_num].elems[phys_id].data;
    //         printf("bucket_num: %zu, req_word: %s, translation: %s, hash: %zu\n", bucket_num, cur_elem.req_word, cur_elem.translation, cur_elem.hash);
    //     }
    // }
    
    // char* req = (char*)calloc(100, sizeof(char));
    // while (true) {
    //     scanf("%s", req);
    //     if (!strcmp("q", req))
    //         break;
    //     HashTableElemT found = HashTable_Find(&hash_table, req);
    //     if (found == EMPTY_LIST_ELEM)
    //         printf("not found\n");
    //     else
    //         printf("translation: %s\n", found.translation);
    // }

    HashTable_Destruct(&hash_table);
    DicBuf_Destruct(&dic);
}
