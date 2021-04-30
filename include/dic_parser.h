#ifndef HASHTABLE_DIC_PARSER_H
#define HASHTABLE_DIC_PARSER_H

#include "ONEGIN_lib.h"


struct DictionaryElement {
    const char* req_word;
    const char* translation;
};

struct Dictionary {
    DictionaryElement* data;
    size_t             size;
};


#endif /* hashtable_dic_parser.h */
