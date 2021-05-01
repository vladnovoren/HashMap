#include "ONEGIN_lib.h"
#include "hash_table_structures.h"
#include "dic_parser.h"


int Dic::Construct(size_t size) {
    DicElement* data = (DicElement*)calloc(size, sizeof(DicElement));
    if (!data)
        return DIC_UNABLE_TO_ALLOC;

    this->data = data;
    this->size = size;

    return 0;
}


void Dic::Destruct() {
    free((void*)this->data->req_word);
    free(this->data);
}


Dic ParseDicFile(const char* file_name) {
    assert(file_name);

    StrArr str_arr = FileToStrArr(file_name);
    if (!str_arr.n_strs)
        return EMPTY_DIC;

    Dic dic = {};
    if (dic.Construct(str_arr.n_strs))
        return dic;

    for (size_t str_num = 0; str_num < str_arr.n_strs; str_num++) {
        char* req_word_end = strchr(str_arr.arr[str_num].c_str, '=');
        if (!*req_word_end) {
            printf("dic::\nstr_num %zu: wrong format\n", str_num);
            return EMPTY_DIC;
        }
        char* translation_end = strchr(req_word_end, '\r');
        if (!translation_end) {
            printf("dic::\nstr_num %zu: wrong format\n", str_num);
            return EMPTY_DIC;
        }
        *translation_end = '\0';
        *req_word_end = '\0';
        dic.data[str_num].req_word    = str_arr.arr[str_num].c_str;
        dic.data[str_num].translation = ++req_word_end;
    }
    free(str_arr.arr);

    return dic;
}
