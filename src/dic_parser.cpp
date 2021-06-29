#include "ONEGIN_lib.h"
#include "hash_table_structures.h"
#include "dic_parser.h"


int DicAlloc(Dic* dic, size_t n_elems) {
    DicElement* elems = (DicElement*)calloc(n_elems, sizeof(DicElement));
    if (!elems)
        return DIC_UNABLE_TO_ALLOC;

    dic->elems   = elems;
    dic->n_elems = n_elems;

    return 0;
}


void DicDestruct(Dic* dic) {
    DestructStrArr(&dic->dic_file_buf);
    free(dic->elems);
}


Dic ParseDicFile(const char* file_name) {
    assert(file_name);

    StrArr dic_file_buf = FileToStrArr(file_name);
    if (!dic_file_buf.n_strs)
        return EMPTY_DIC;

    Dic dic = EMPTY_DIC;
    if (DicAlloc(&dic, dic_file_buf.n_strs))
        return dic;

    bool is_legal_format = true;
    size_t str_err_num = 0;
    for (size_t str_num = 0; str_num < dic_file_buf.n_strs; str_num++) {
        char* req_word_end = strchr(dic_file_buf.arr[str_num].c_str, '=');
        if (!*req_word_end) {
            is_legal_format = false;
            str_err_num = str_num;
            break;
        }

        char* translation_end = strchr(req_word_end, '\r');
        if (!translation_end) {
            is_legal_format = false;
            str_err_num = str_num;
            break;
        }

        *translation_end = '\0';
        *req_word_end = '\0';
        dic.elems[str_num].req_word = dic_file_buf.arr[str_num].c_str;
        dic.elems[str_num].translation = ++req_word_end;
    }

    if (!is_legal_format) {
        printf("dic::\nstr_num %zu: wrong format\n", str_err_num + 1);
        DestructStrArr(&dic_file_buf);
        return EMPTY_DIC;
    }

    dic.dic_file_buf = dic_file_buf;
    dic.n_elems = dic_file_buf.n_strs;

    return dic;
}
