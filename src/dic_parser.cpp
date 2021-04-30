#include "ONEGIN_lib.h"
#include "hash_table_structures.h"


StrArr ParseDicFile(const char* file_name) {
    assert(file_name);

    StrArr str_arr = FileToStrArr(file_name);
    if (!str_arr.n_strs)

}
