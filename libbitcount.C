//#include <vector>
#include <iostream>
#include "libbitcount.h"

void bitcount_array(uint8_t* array, int array_size, int* C) {
    int8_t mask;
    for (int j = 0; j < array_size; ++j) {
        mask = 1;
        for (int i = 0; i < 8; ++i) {
            C[i] += ((array[j] & mask) >> i);
            mask <<= 1;
        }
    }
}