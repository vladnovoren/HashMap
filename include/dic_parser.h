#ifndef HASHTABLE_DIC_PARSER_H
#define HASHTABLE_DIC_PARSER_H

#include "ONEGIN_lib.h"


struct DicElement {
    const char* req_word;
    const char* translation;
};

struct Dic {
    DicElement* data;
    size_t             size;
    int Construct(size_t size);
    void Destruct();
};


static const Dic EMPTY_DIC = {};

enum DicErros {
    DIC_NO_ERRORS,
    DIC_UNABLE_TO_ALLOC,
    DIC_WRONG_FORMAT
};


Dic ParseDicFile(const char* file_name);


#endif /* hashtable_dic_parser.h */
