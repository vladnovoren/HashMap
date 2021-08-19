#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include "list_config.h"


static const size_t LIST_DEFAULT_N_ELEMS  = 0;
static const size_t LIST_DEFAULT_CAPACITY = 8;
static const size_t LIST_CAPACITY_CHECK   = 4;
static const size_t LIST_CAPACITY_MUL     = 2;
static const size_t LIST_INVALID_ID       = 18446744073709551615ULL;


struct ListNode {
    ListElemT data;
    size_t prev_phys_id;
    size_t cur_phys_id;
    size_t next_phys_id;
    bool is_used;
};

struct List {
    size_t n_elems;
    size_t capacity;
    ListNode* elems;
    size_t head_phys_id;
    size_t tail_phys_id;
    size_t free_phys_id;
};

enum ListErrors {
    LIST_NO_ERRORS,
    LIST_ALLOC_ERROR,
    LIST_ABSENCE_OF_REQUIRED_ELEM
};

const ListElemT EMPTY_LIST_ELEM = {};


void      List_ConnectNodes(List* list, const size_t first_phys_id, const size_t second_phys_id);

void      List_ConnectArray(List* list, const size_t begin_phys_id, const size_t end_phys_id);

int       List_CheckAndUpdateCapacity(List* list);

int       List_PushFront(List* list, const ListElemT new_elem, size_t* phys_id = nullptr);

int       List_PushBack(List* list, const ListElemT new_elem, size_t* phys_id = nullptr);

int       List_Alloc(List* list);

void      List_Destruct(List* list);

int       List_Clear(List* list);

int       List_GetPhysId(List* list, size_t logic_id, size_t* phys_id);

int       List_GetByLogicId(List* list, size_t logic_id, ListElemT* found);

int       List_GetByPhysId(List* list, const size_t phys_id, ListElemT* found);

int       List_InsertBefore(List* list, const size_t phys_id, const ListElemT new_elem);

int       List_InsertAfter(List* list, const size_t phys_id, const ListElemT new_elem);

int       List_EraseByPhysId(List* list, size_t phys_id);

int       List_EraseByLogicId(List* list, size_t logic_id);

int       List_PopFront(List* list);

int       List_PopBack(List* list);

ListElemT List_Find(List* list, ListElemT elem, size_t* phys_id = nullptr, size_t* logic_id = nullptr);



#endif /* list.h */
