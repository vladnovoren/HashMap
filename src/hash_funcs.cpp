#include "hash_funcs.h"
#include "stdio.h"



HashT ConstantHash(const char* c_str) {
    assert(c_str);

    return HASH_CONST;
}


HashT FirstCharHash(const char* c_str) {
    assert(c_str);

    return *c_str;
}


HashT ASCII_SumHash(const char* c_str) {
    assert(c_str);

    HashT hash = 0;
    while (*c_str) {
        hash += *c_str;
        c_str++;
    }

    return hash;
}


HashT Rol(HashT x) {
    return (x << 1) | (x >> 63);
}


HashT RolHash(const char* c_str) {
    assert(c_str);

    HashT hash = 0;

    while (*c_str) {
        hash = Rol(hash) ^ (*c_str);
        ++c_str;
    }

    return hash;
}


//HashT Crc32Hash(const char* c_str) {
    //assert(c_str);

    //unsigned int crc_sum = MAX_UNSIGNED_INT;
    //while(*c_str)
        //crc_sum = (crc_sum >> 8) ^ CRC_32_TABLE[(crc_sum ^ *c_str++) & 0xFF];
    //return crc_sum ^ MAX_UNSIGNED_INT;
//}


HashT Crc32Hash(const char* c_str) {
    assert(c_str);

    HashT hash = 0;
    __asm__("xor %0, %0\n"
            "crc32q (%1), %0\n" : "=r" (hash) : "r" (c_str));
    return hash;
}

