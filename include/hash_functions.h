#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include "common_header.h"
#include "assert.h"


const size_t FNV_OFFSET_BASICS = 14695981039346656037LLU;
const size_t FNV_PRIME         = 1099511628211;
const size_t HASH_CONST        = 12;
const size_t MAX_WORD_LEN      = 100000;
const int    POLYNOMIAL_HASH_P = 257;

HashT ConstantHash(const char* c_str);

HashT FirstCharHash(const char* c_str);

HashT ASCII_SumHash(const char* c_str);

HashT PolynomialHash(const char* c_str);

HashT FNVA1aHash(const char* c_str);


#endif /* hash_functions.h */
