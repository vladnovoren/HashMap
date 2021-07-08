#include <stdio.h>
#include <stdlib.h>

#include "test_hash_table.h"



int main (int argc, char* argv[]) {
    if (argc < 2) {
        printf("no dictionary file\n");
        return 1;
    }

    TestHashTable(argv[1]);

	return 0;
}
