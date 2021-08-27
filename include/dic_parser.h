#ifndef DIC_PARSER_H
#define DIC_PARSER_H

#include "ONEGIN_lib.h"


struct DicElem {
    const char* key;
    const char* value;
};

struct DicBuf {
    DicElem* elems;
    size_t   n_elems;
    StrArr   src;
};


const size_t ALIGN_LEN = 64;

size_t Min(size_t a, size_t b);

int    DicBuf_Alloc(DicBuf* dic, size_t n_elems);

void   DicBuf_Destruct(DicBuf* dic);

int    DicBuf_ParseDicFile(DicBuf* dic, const char* src_path);

int    DicBuf_ReportErr(int err_code);


enum DicBufErros {
    DIC_BUF_NO_ERRS,
    DIC_BUF_UNABLE_TO_ALLOC,
    DIC_BUF_STR_ARR_ERR,
    DIC_BUF_WRONG_FORMAT
};

const size_t DIC_BUF_N_ERRS = 4;

const char* const DIC_BUF_ERR_MSGS[DIC_BUF_N_ERRS] = {
    "no errors",
    "unable to allocate memory",
    "StrArr error",
    "wrong *.dic file format"
};



#endif /* dic_parser.h */
