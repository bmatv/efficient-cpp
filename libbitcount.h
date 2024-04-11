//
// Created by bogdan on 4/04/24.
//

#ifndef EFFICIENT_CPP_LIBBITCOUNT_H
#define EFFICIENT_CPP_LIBBITCOUNT_H

#include <cstdint>
#include <vector>

void bitcount_array(uint8_t* array, int& array_size, int* C);

void bitPairCount(const std::vector<uint8_t>& vecA, const std::vector<uint8_t> &vecB, std::vector<std::vector<int>>& C);

inline void bitcount_array_inlined(uint8_t* array, int array_size, int* C) {
    int8_t mask;
    for (int j = 0; j < array_size; ++j) {
        mask = 1;
        for (int i = 0; i < 8; ++i) {
            C[i] += ((array[j] & mask) >> i);
            mask <<= 1;
        }
    }
}

#endif //EFFICIENT_CPP_LIBBITCOUNT_H
