#include "hash_functions.h"



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


HashT PolynomialHash(const char* c_str) {
    assert(c_str);

	static HashT p_powers[MAX_WORD_LEN] = {};
	if (!p_powers[0]) {
		p_powers[0] = 1;
		for (size_t pos = 1; pos < MAX_WORD_LEN; pos++)
			p_powers[pos] = p_powers[pos - 1] * POLYNOMIAL_HASH_P;
	}

	HashT symb_num = 0;
	HashT hash     = 0;
	while (c_str[symb_num]) {
        hash += p_powers[symb_num] * c_str[symb_num];
        symb_num++;
    }

	return hash;
}


HashT FNVA1aHash(const char* c_str) {
    assert(c_str);

    HashT hash = FNV_OFFSET_BASICS;

    while (*c_str) {
        hash ^= *c_str;
        hash *= FNV_PRIME;
        c_str++;
    }

    return hash;
}