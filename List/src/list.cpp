#include "list.h"


void List_ConnectNodes(List* list, const size_t first_phys_id, const size_t second_phys_id) {
    assert(list);

    list->elems[first_phys_id].next_phys_id = second_phys_id;
    list->elems[second_phys_id].prev_phys_id = first_phys_id;
}


void List_ConnectArray(List* list, const size_t begin_phys_id, const size_t end_phys_id) {
    assert(list);

    list->elems[begin_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[begin_phys_id].cur_phys_id = begin_phys_id;
    for (size_t phys_id = begin_phys_id + 1; phys_id <= end_phys_id; phys_id++) {
        list->elems[phys_id].cur_phys_id = phys_id;
        List_ConnectNodes(list, phys_id - 1, phys_id);
    }
    list->elems[end_phys_id].next_phys_id = LIST_INVALID_ID;
}


int List_Alloc(List* list) {
    assert(list);

    list->elems = (ListNode*)calloc(LIST_DEFAULT_CAPACITY, sizeof(ListNode));
    if (!list->elems)
        return LIST_ALLOC_ERROR;

    list->n_elems  = LIST_DEFAULT_N_ELEMS;
    list->capacity = LIST_DEFAULT_CAPACITY;
    List_ConnectArray(list, 0, list->capacity - 1);
    list->head_phys_id = LIST_INVALID_ID;
    list->tail_phys_id = LIST_INVALID_ID;
    list->free_phys_id = 0;

    return LIST_NO_ERRORS;
}


int List_CheckAndUpdateCapacity(List* list) {
    assert(list);

    if (list->n_elems == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        ListNode* new_elems = (ListNode*)realloc(list->elems, sizeof(ListNode) * new_capacity);
        if (!new_elems)
            return LIST_ALLOC_ERROR;
        list->elems = new_elems;
        list->capacity = new_capacity;
        list->free_phys_id = list->n_elems;
        List_ConnectArray(list, list->n_elems, list->capacity - 1);
    }

    return LIST_NO_ERRORS;
}


size_t List_GetNextPhysId(List* list, size_t phys_id) {
    assert(list);

    return list->elems[phys_id].next_phys_id;
}


size_t List_GetPrevPhysId(List* list, size_t phys_id) {
    assert(list);

    return list->elems[phys_id].prev_phys_id;
}


int List_PushFront(List* list, const ListElemT new_elem, size_t* phys_id) {
    assert(list);

    int check_res = 0;
    if ((check_res = List_CheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = List_GetNextPhysId(list, list->free_phys_id);
    if (list->n_elems)
        List_ConnectNodes(list, list->free_phys_id, list->head_phys_id);
    else
        list->tail_phys_id = list->free_phys_id;
    list->head_phys_id = list->free_phys_id;
    list->free_phys_id = new_free_phys_id;
    list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[list->tail_phys_id].next_phys_id = LIST_INVALID_ID;
    list->elems[list->head_phys_id].data = new_elem;
    list->elems[list->head_phys_id].is_used = true;
    if (list->free_phys_id != LIST_INVALID_ID)
        list->elems[list->free_phys_id].prev_phys_id = LIST_INVALID_ID;
    ++list->n_elems;
    if (phys_id)
        *phys_id = list->head_phys_id;

    return LIST_NO_ERRORS;
}


int List_PushBack(List* list, const ListElemT new_elem, size_t* phys_id) {
    assert(list);

    int check_res = 0;
    if ((check_res = List_CheckAndUpdateCapacity(list)) != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = List_GetNextPhysId(list, list->free_phys_id);
    if (list->n_elems)
        List_ConnectNodes(list, list->tail_phys_id, list->free_phys_id);
    else
        list->head_phys_id = list->free_phys_id;
    list->tail_phys_id = list->free_phys_id;
    list->free_phys_id = new_free_phys_id;
    list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
    list->elems[list->tail_phys_id].next_phys_id = LIST_INVALID_ID;
    list->elems[list->tail_phys_id].data = new_elem;
    list->elems[list->tail_phys_id].is_used = true;
    if (new_free_phys_id != LIST_INVALID_ID)
        list->elems[new_free_phys_id].prev_phys_id = LIST_INVALID_ID;
    ++list->n_elems;
    if (phys_id)
        *phys_id = list->tail_phys_id;

    return LIST_NO_ERRORS;
}


int List_GetPhysId(List* list, size_t logic_id, size_t* phys_id) {
    assert(list);
    assert(phys_id);

    if (logic_id >= list->n_elems)
        return LIST_ABSENCE_OF_REQUIRED_ELEM;

    *phys_id = list->head_phys_id;
    while (logic_id) {
        *phys_id = List_GetNextPhysId(list, *phys_id);
        --logic_id;
    }
    
    return LIST_NO_ERRORS;
}


int List_GetByLogicId(List* list, size_t logic_id, ListElemT* found) {
    assert(list);
    assert(found);

    size_t phys_id = 0;
    int get_phys_id_res = List_GetPhysId(list, logic_id, &phys_id);
    if (get_phys_id_res != LIST_NO_ERRORS)
        return get_phys_id_res;

    *found = list->elems[phys_id].data;
    return LIST_NO_ERRORS;
}


int List_GetByPhysId(List* list, const size_t phys_id, ListElemT* found) {
    assert(list);
    assert(found);

    if (list->elems[phys_id].is_used && phys_id < list->capacity)
        *found = list->elems[phys_id].data;
    else
        return LIST_ABSENCE_OF_REQUIRED_ELEM;

    return LIST_NO_ERRORS;
}


int List_EraseByPhysId(List* list, size_t phys_id) {
    assert(list);

    if (phys_id >= list->capacity)
        return LIST_ABSENCE_OF_REQUIRED_ELEM;
    
    if (list->n_elems == 1) {
        List_ConnectNodes(list, list->head_phys_id, list->free_phys_id);
        list->free_phys_id = list->head_phys_id;
        list->head_phys_id = list->tail_phys_id = LIST_INVALID_ID;
    } else if (phys_id == list->head_phys_id) {
        size_t new_head_phys_id = List_GetNextPhysId(list, list->head_phys_id);
        List_ConnectNodes(list, list->head_phys_id, list->free_phys_id);
        list->free_phys_id = list->head_phys_id;
        list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
        list->head_phys_id = new_head_phys_id;
        list->elems[list->head_phys_id].prev_phys_id = LIST_INVALID_ID;
    } else if (phys_id == list->tail_phys_id) {
        size_t new_tail_phys_id = List_GetPrevPhysId(list, list->tail_phys_id);
        List_ConnectNodes(list, list->tail_phys_id, list->free_phys_id);
        list->free_phys_id = list->tail_phys_id;
        list->elems[list->free_phys_id].prev_phys_id = LIST_INVALID_ID;
        list->tail_phys_id = new_tail_phys_id;
        list->elems[list->tail_phys_id].next_phys_id = LIST_INVALID_ID;
    } else {
        List_ConnectNodes(list, List_GetPrevPhysId(list, phys_id), List_GetNextPhysId(list, phys_id));
        List_ConnectNodes(list, phys_id, list->free_phys_id);
        list->free_phys_id = phys_id;
        list->elems[list->free_phys_id].prev_phys_id = LIST_INVALID_ID;
    }
    list->elems[list->free_phys_id].is_used = false;
    --list->n_elems;

    return LIST_NO_ERRORS;
}


int List_InsertBefore(List* list, const size_t phys_id, const ListElemT new_elem) {
    assert(list);

    if (phys_id >= list->capacity || !list->elems)
        return LIST_ABSENCE_OF_REQUIRED_ELEM;

    if (phys_id == list->head_phys_id)
        return List_PushFront(list, new_elem);
    
    int check_res = List_CheckAndUpdateCapacity(list);
    if (check_res != LIST_NO_ERRORS)
        return check_res;

    size_t new_free_phys_id = List_GetNextPhysId(list, list->free_phys_id);
    size_t prev_phys_id = List_GetPrevPhysId(list, phys_id);
    list->elems[list->free_phys_id].data = new_elem;
    list->elems[list->free_phys_id].is_used = true;
    List_ConnectNodes(list, prev_phys_id, list->free_phys_id);
    List_ConnectNodes(list, list->free_phys_id, phys_id);
    list->free_phys_id = new_free_phys_id;
    if (list->free_phys_id != LIST_INVALID_ID)
        list->elems[list->free_phys_id].prev_phys_id = LIST_INVALID_ID;
    ++list->n_elems;

    return LIST_NO_ERRORS;
}


int List_InsertAfter(List* list, const size_t phys_id, const ListElemT new_elem) {
    assert(list);

    if (phys_id >= list->capacity || !list->elems)
        return LIST_ABSENCE_OF_REQUIRED_ELEM;
    
    if (phys_id == list->tail_phys_id)
        return List_PushBack(list, new_elem);
    
    int check_res = List_CheckAndUpdateCapacity(list);
    if (check_res != LIST_NO_ERRORS)
        return check_res;
    
    size_t new_free_phys_id = List_GetNextPhysId(list, list->free_phys_id);
    size_t next_phys_id = List_GetNextPhysId(list, phys_id);
    list->elems[list->free_phys_id].data = new_elem;
    list->elems[list->free_phys_id].is_used = true;
    List_ConnectNodes(list, phys_id, list->free_phys_id);
    List_ConnectNodes(list, list->free_phys_id, next_phys_id);
    list->free_phys_id = new_free_phys_id;
    if (list->free_phys_id != LIST_INVALID_ID)
        list->elems[list->free_phys_id].prev_phys_id = LIST_INVALID_ID;
    ++list->n_elems;

    return LIST_NO_ERRORS;
}


int List_EraseByLogicId(List* list, size_t logic_id) {
    assert(list);

    size_t phys_id = 0;
    int get_phys_id_res = List_GetPhysId(list, logic_id, &phys_id);
    if (get_phys_id_res == LIST_NO_ERRORS)
        return List_EraseByPhysId(list, phys_id);
    else
        return get_phys_id_res;

    return LIST_NO_ERRORS;
}


void List_Destruct(List* list) {
    assert(list);

    free(list->elems);
    *list = {};
}


int List_Clear(List* list) {
    assert(list);

    List_Destruct(list);
    return List_Alloc(list);
}


size_t List_Find(List* list, const ListElemT elem) {
    assert(list);

    size_t phys_id = 0;

    if (list->n_elems) {
        phys_id = list->head_phys_id;
        while (phys_id != LIST_INVALID_ID) {
            if (list->elems[phys_id].data == elem)
                return phys_id;
            phys_id = List_GetNextPhysId(list, phys_id);
        }
    }

    return LIST_INVALID_ID;
}
