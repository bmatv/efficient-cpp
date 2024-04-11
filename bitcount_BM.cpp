//
// Created by bogdan on 4/04/24.
//
//
#include <iostream>
#include <bitset>
#include "benchmark/benchmark.h"
#include "libbitcount.h"
//#include <cstdint>

void BM_bitpaircount_vec_float(benchmark::State& state){

    std::vector<float>vec{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483};
    const int nbits = sizeof(vec[0]) * 8; // should be 32 and can be unsigned if that makes sense
    std::vector<std::vector<int>> C(nbits,std::vector<int>(4,0)); //should be [nbits,4], could be a basic 1D array

    int mask;
    int idxA = 0, idxB = 0;
    int A, B;
    size_t total = vec.size()-1;

    for (auto _:state) {

    for (size_t i = 0; i< total; ++i){
        mask = 1;
        A = reinterpret_cast<int&>(vec[i]);
        B = reinterpret_cast<int&>(vec[i+1]);

        for (int j = 0; j< nbits; ++j){
            idxA = (A & mask) >> j;
            idxB = (B & mask) >> j;
            C[j][idxA + idxB*2] += 1; // OK but a bit different order which is fine
            mask <<= 1;
        }
    }

        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations());
}


void BM_reinterp_cast(benchmark::State& state){
//    std::vector<float> vec{0.1,0.2,0.3,0.4,0.5};
    float arr[]{0.1,0.2,0.3,0.4,0.5};
    int* a;
    for (auto _:state) {
        for(int i = 0; i<5;++i){
            a = reinterpret_cast<int*>(&arr[i]);

        }
        benchmark::DoNotOptimize(a);
        benchmark::ClobberMemory();


    }
    state.SetItemsProcessed(state.iterations()*5);
}

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
    int array_size = 5;
    for (auto _:state) {
        bitcount_array(array, array_size, C);
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

void BM_bitpaircount_vec(benchmark::State& state) {
    //TODO Why is vec implementation so slow?
    std::vector<uint8_t> vecA {0b10001110,
                               0b00010110,
                               0b11101001,
                               0b10100101,
                               0b11101010};

    std::vector<uint8_t> vecB {0b10001111,
                               0b00010111,
                               0b11101000,
                               0b10100100,
                               0b11101011};


    assert(vecA.size() == vecB.size());
    std::vector<std::vector<int>> C(5,std::vector<int>(4,0)); // same as {0,0,0,0}?

    uint8_t mask;
    bool idxA, idxB;
    for (auto _:state) {
    for(size_t j = 0; j<vecA.size();++j){
        mask = 1;
        for (int i = 0; i<8;++i){
            idxA = (vecA[j] & mask) >> i;
            idxB = (vecB[j] & mask) >> i;
            C[j][idxA + idxB*2] += 1;
            mask <<=1;
        }
    }
    benchmark::DoNotOptimize(C);
    benchmark::ClobberMemory();
    }
//    std::cout << C[0][0] << '\n';
    state.SetItemsProcessed(state.iterations());
}

void BM_bitpaircount_array(benchmark::State& state) {
    //TODO Why is vec implementation so slow?
    uint8_t vecA[] {0b10001110,
                               0b00010110,
                               0b11101001,
                               0b10100101,
                               0b11101010};

    uint8_t vecB[] {0b10001111,
                   0b00010111,
                   0b11101000,
                   0b10100100,
                   0b11101011};


//    assert(vecA.size() == vecB.size());
    int C[5][4] {{0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0}};
//    std::vector<std::vector<int>> C(5,std::vector<int>(4,0)); // same as {0,0,0,0}?

    uint8_t mask;
    bool idx_a = 0, idx_b = 0;
    for (auto _:state) {
        for(int j = 0; j<5;++j){ // 5 elements
            mask = 1;
            for (int i = 0; i<8;++i){
                idx_a = (vecA[j] & mask) >> i;
                idx_b = (vecB[j] & mask) >> i;
                C[j][idx_a + idx_b*2] += 1;
                mask <<=1;
            }
        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
}

void BM_bitpaircount_array1d(benchmark::State& state) {
    //TODO Why is vec implementation so slow?
    uint8_t vecA[] {0b10001110,
                    0b00010110,
                    0b11101001,
                    0b10100101,
                    0b11101010};

    uint8_t vecB[] {0b10001111,
                    0b00010111,
                    0b11101000,
                    0b10100100,
                    0b11101011};


//    assert(vecA.size() == vecB.size());
    int C[5*4] {0,0,0,0,
                0,0,0,0,
                0,0,0,0,
                0,0,0,0,
                0,0,0,0};
//    std::vector<std::vector<int>> C(5,std::vector<int>(4,0)); // same as {0,0,0,0}?

    uint8_t mask;//, idx_a = 0, idx_b = 0;
    for (auto _:state) {
        for(int j = 0; j<5;++j){ // 5 elements
            mask = 1;
            for (int i = 0; i<8;++i){
//                idx_a = (vecA[j] & mask) >> i;
//                idx_b = (vecB[j] & mask) >> i;
//                C[4*j + idx_a + idx_b*2] += 1;
                C[4*j + ((vecA[j] & mask) >> i) + ((vecB[j] & mask) >> i)*2] ++;
                mask <<=1;
            }
        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_bitpaircount_vec_float)->Arg(1 << 22);
BENCHMARK(BM_reinterp_cast)->Arg(1 << 22);
BENCHMARK(BM_reinterp_cast_single)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_vec)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_array)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_array1d)->Arg(1 << 22);
BENCHMARK(BM_bitcount_array)->Arg(1 << 22);
BENCHMARK(BM_bitcount_array_fn)->Arg(1 << 22);
BENCHMARK(BM_bitcount_array_fn_inline)->Arg(1 << 22);
BENCHMARK(BM_bitcount_vec)->Arg(1 << 22);

BENCHMARK_MAIN();