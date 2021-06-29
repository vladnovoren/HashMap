#include "dic_parser.h"


int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("Enter dictionary file name\n");
        return 1;
    }

    const char* dic_file_name = argv[1];
    Dic dic = ParseDicFile(dic_file_name);
    for (size_t elem_num = 0; elem_num < dic.n_elems; elem_num++) {
        printf("word: %s, translation: %s\n", dic.elems[elem_num].req_word, dic.elems[elem_num].translation);
    }
    DicDestruct(&dic);

    return 0;
}