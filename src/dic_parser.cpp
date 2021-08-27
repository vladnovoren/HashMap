#include "ONEGIN_lib.h"
#include "dic_parser.h"


size_t Min(size_t a, size_t b) {
    return a < b ? a : b;
}


int DicBuf_Alloc(DicBuf* dic, size_t n_elems) {
    DicElem* elems = (DicElem*)calloc(n_elems, sizeof(DicElem));
    if (!elems)
        return DicBuf_ReportErr(DIC_BUF_UNABLE_TO_ALLOC);

    dic->elems   = elems;
    dic->n_elems = n_elems;

    return 0;
}


void DicBuf_Destruct(DicBuf* dic) {
    DestructStrArr(&dic->src);
    free(dic->elems);
}


int DicBuf_ParseDicFile(DicBuf* dic, const char* src_path) {
    assert(dic);
    assert(src_path);

    StrArr src = FileToStrArr(src_path);
    if (!src.n_strs)
        return DicBuf_ReportErr(DIC_BUF_STR_ARR_ERR);

    int alloc_res = DicBuf_Alloc(dic, src.n_strs);
    if (alloc_res)
        return alloc_res;

    bool is_legal_frmt = true;
    size_t str_num = 0;
    for (str_num = 0; str_num < src.n_strs; ++str_num) {
        char* key_end = strchr(src.arr[str_num].c_str, '=');
        if (!key_end) {
            is_legal_frmt = false;
            break;
        }
        char* cr = strchr(key_end, '\r');
        *cr = '\0';
        *key_end = '\0';
        dic->elems[str_num].key = (char*)calloc(64, sizeof(char));
        if (!dic->elems[str_num].key)
            return DicBuf_ReportErr(DIC_BUF_UNABLE_TO_ALLOC);
        strncpy(dic->elems[str_num].key, src.arr[str_num].c_str, 63);
        dic->elems[str_num].value = ++key_end;
    }
    if (!is_legal_frmt) {
        printf("str# %zu\n", str_num);
        return DicBuf_ReportErr(DIC_BUF_WRONG_FORMAT);
    }
    dic->n_elems = src.n_strs;
    dic->src = src;

    return DIC_BUF_NO_ERRS;
}


int DicBuf_ReportErr(int err_code) {
    fprintf(stderr, "DicBuf: %s\n", DIC_BUF_ERR_MSGS[err_code]);

    return err_code;
}
