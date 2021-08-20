#include <stdio.h>
#include <stdlib.h>

#include "test_hash_table.h"


int main (int argc, char* argv[]) {
    if (argc < 3) {
        printf("fatal error: no dict-file name or gnuplot folder path\n");
        return 1;
    }

    TestHashFunctions(argv[1], argv[2]);

	return 0;
}
