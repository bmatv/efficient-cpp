#include <vector>
#include <iostream>
#include "libbitcount.h"
#include <cassert>

void bitcount_array(uint8_t* array, int& array_size, int* C) {
    int8_t mask;
    for (int j = 0; j < array_size; ++j) {
        mask = 1;
        for (int i = 0; i < 8; ++i) {
            C[i] += ((array[j] & mask) >> i);
            mask <<= 1;
        }
    }
}

void bitPairCount(const std::vector<uint8_t>& vecA, const std::vector<uint8_t> &vecB, std::vector<std::vector<int>>& C){
    assert(vecA.size() == vecB.size());
    uint8_t mask;
    for(size_t j = 0; j<vecA.size();++j) {
        mask = 1;
        for (int i = 0; i < 8; ++i) {
            C[j][((vecA[j] & mask) >> i) + ((vecB[j] & mask) >> i) * 2] += 1;
            mask <<= 1;
        }
    }
}