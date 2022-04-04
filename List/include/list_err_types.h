#ifndef LIST_ERR_TYPES
#define LIST_ERR_TYPES

const size_t LIST_N_ERR_TYPES = 4;

enum List_ErrTypes {
    LIST_NO_ERRS,
    LIST_ALLOC_ERR,
    LIST_INVALID_LOGIC_ID,
    LIST_INVALID_PHYS_ID
};

#endif /* list_err_types.h */
