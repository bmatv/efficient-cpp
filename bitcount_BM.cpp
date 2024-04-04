//
// Created by bogdan on 4/04/24.
//
//
#include <iostream>
#include <bitset>
#include "benchmark/benchmark.h"
#include "libbitcount.h"
//#include <cstdint>

void BM_bitcount_vec(benchmark::State& state) {
    //TODO Why is vec implementation so slow?
    std::vector<uint8_t> vec{0b10001111,0b00010111,0b11101000,0b10100100,0b11101011};

    int C[8]{0,0,0,0,0,0,0,0}; // throwing sums in here
    uint8_t mask;
    for (auto _:state) {
        for (auto& number: vec) {
            mask = 1;
            for (int i = 0; i < 8; ++i) {
                C[i] += ((number & mask) >> i);
                mask <<= 1;
            }
        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations());

}

void BM_bitcount_array(benchmark::State& state) {
    uint8_t array [5] {0b10001111,
                       0b00010111,
                       0b11101000,
                       0b10100100,
                       0b11101011};

    int C [8] {};
    int8_t mask;
    for (auto _:state) {

        for (auto &number: array) {
            mask = 1;
            for (int i = 0; i < (8); ++i) {
                C[i] += ((number & mask) >> i);
                mask <<= 1;
            }

        }

        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations());
}


void BM_bitcount_array_fn(benchmark::State& state) {
    uint8_t array [5] {0b10001111,
                       0b00010111,
                       0b11101000,
                       0b10100100,
                       0b11101011};

    int C [8] {};
    for (auto _:state) {
        bitcount_array(array, 5, C);
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations());
}

void BM_bitcount_array_fn_inline(benchmark::State& state) {
    uint8_t array [5] {0b10001111,
                       0b00010111,
                       0b11101000,
                       0b10100100,
                       0b11101011};

    int C [8] {};
    for (auto _:state) {
        bitcount_array_inlined(array, 5, C);
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_bitcount_array)->Arg(1 << 22);
BENCHMARK(BM_bitcount_array_fn)->Arg(1 << 22);
BENCHMARK(BM_bitcount_array_fn_inline)->Arg(1 << 22);
BENCHMARK(BM_bitcount_vec)->Arg(1 << 22);
BENCHMARK_MAIN();