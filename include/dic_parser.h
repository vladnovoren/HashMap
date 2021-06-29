#ifndef HASHTABLE_DIC_PARSER_H
#define HASHTABLE_DIC_PARSER_H

#include "ONEGIN_lib.h"


struct DicElement {
    const char* req_word;
    const char* translation;
};

struct Dic {
    StrArr dic_file_buf;
    DicElement* elems;
    size_t n_elems;
};


int  DicAlloc(Dic* dic, size_t n_elems);

void DicDestruct(Dic* dic);

Dic ParseDicFile(const char* file_name);


static const Dic EMPTY_DIC = {};

enum DicErros {
    DIC_NO_ERRORS,
    DIC_UNABLE_TO_ALLOC,
    DIC_WRONG_FORMAT
};




#endif /* hashtable_dic_parser.h */
