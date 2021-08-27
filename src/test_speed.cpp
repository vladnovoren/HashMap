#include "test_hash_map.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("enter *.dic or requests file path\n");
        return 1;
    }

    assert(!TestSpeed(argv[1], argv[2]));

    return 0;
}
