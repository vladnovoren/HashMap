#ifndef LIST_ERROR_TYPES
#define LIST_ERROR_TYPES

const size_t LIST_N_ERROR_TYPES = 4;

enum List_ErrorTypes {
    LIST_NO_ERRORS,
    LIST_ALLOC_ERROR,
    LIST_INVALID_LOGIC_ID,
    LIST_INVALID_PHYS_ID
};

#endif /* list_error_types.h */
