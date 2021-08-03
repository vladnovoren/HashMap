#ifndef HASHTABLE_DIC_PARSER_H
#define HASHTABLE_DIC_PARSER_H

#include "ONEGIN_lib.h"


struct DicElement {
    const char* req_word;
    const char* translation;
};

struct DicBuf {
    StrArr      dic_file_buf;
    DicElement* elems;
    size_t      n_elems;
};


int    DicBuf_Alloc(DicBuf* dic, size_t n_elems);

void   DicBuf_Destruct(DicBuf* dic);

DicBuf DicBuf_ParseDicFile(const char* file_name);


static const DicBuf EMPTY_DIC_BUF = {};

enum DicBufErros {
    DIC_BUF_NO_ERRORS,
    DIC_BUF_UNABLE_TO_ALLOC,
    DIC_BUF_WRONG_FORMAT
};



#endif /* hashtable_dic_parser.h */
