#include "list.h"

int main() {
    size_t id = 0;
    List list = {};
    List_Alloc(&list);
    for (size_t k = 0; k < 1000; k++) {
        for (size_t i = 0; i < 1000; i++)
            List_PushFront(&list, 1, &id);
        for (size_t i = 0; i < 999; i++)
            List_EraseByLogicId(&list, 0);
        for (size_t i = 0; i < 999; i++)
            List_InsertAfter(&list, 0, 1);
        for (size_t i = 0; i < 999; i++)
            List_InsertBefore(list, 1, 1);
        List_Clear(&list);
    }
    List_Destruct(&list);
    return 0;
}
