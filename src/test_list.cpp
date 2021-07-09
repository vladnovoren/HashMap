#include "list.h"
#include "dic_parser.h"


int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("Enter file name\n");
        return 1;
    }

    List list = {};
    ListAlloc(&list);
    Dic dic = ParseDicFile(argv[1]);

    for (size_t word_num = 0; word_num < dic.n_elems; word_num++) {
        ListInsert(&list, {dic.elems[word_num].req_word, dic.elems[word_num].translation, 0});
    }

    ListDestruct(&list);
    DicDestruct(&dic);
    return 0;
}
