#include "hash_table.h"


HashT PolynomialHash(const char* c_str) {
	static HashT p_powers[MAX_WORD_LEN] = {};
	if (!p_powers[0]) {
		p_powers[0] = 1;
		for (size_t pos = 1; pos < MAX_WORD_LEN; pos++)
			p_powers[pos] = p_powers[pos - 1] * POLYNOM_HASH_P;
	}

	HashT symb_num = 0;
	HashT hash     = 0;
	while (c_str[symb_num])
		hash += p_powers[symb_num++];

	return hash;
}


HashT GetHash(const char* c_str) {
    return PolynomialHash(c_str);
}



