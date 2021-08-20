#include "test_hash_table.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("enter *.dic file path\n");
        return 1;
    }

    TestSpeed(argv[1]);

    return 0;
}