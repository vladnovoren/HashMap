#ifndef LIST_DUMP_H
#define LIST_DUMP_H

#include "list.h"

enum NodeTypes {
    USED,
    FREE
};


void PutList(List* list, const size_t head_phys_id, const size_t tail_phys_id, const char* color);

void List_Dump(List* list, FILE* log);

#endif /* list_dump.h */