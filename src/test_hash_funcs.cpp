#include <stdio.h>
#include <stdlib.h>

#include "test_hash_map.h"


int main (int argc, char* argv[]) {
    if (argc < 3) {
        printf("fatal err: no dict-file name or gnuplot folder path\n");
        return 1;
    }

    TestHashFuncs(argv[1], argv[2]);

	return 0;
}
