#include "list_dump.h"


int main(int arc, char* argv[]) {
    List list = {};
    List_Alloc(&list);
    size_t id = 0;
    int val = 0;
    for (size_t i = 0; i < 5; ++i)
        List_PushBack(&list, val++, &id);
        
    List_InsertAfter(&list, 1, 8);
    List_InsertAfter(&list, 4, 9);
    List_InsertBefore(&list, 5, 10);

    List_InsertAfter(&list, 7, 11);
    List_InsertBefore(&list, 7, 12);

    size_t phys_id = 0, logic_id = 0;
    List_Find(&list, 21, &phys_id, &logic_id);
    printf("phys_id: %zu, logic_id: %zu\n", phys_id, logic_id);

    FILE* log = fopen(argv[1], "wb");
    List_Dump(&list, log);
    fclose(log);
    return 0;
}
