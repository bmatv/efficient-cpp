//
// Created by bogdan on 30/11/23.
//
#include "benchmark/benchmark.h"
#include <algorithm>
#include <iostream>

void BM_branch_clamp(benchmark::State& state){
    /*Performance is better because the predictor can actually work now, no ideal though
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned char> v1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand()%256;
    }
    unsigned char* c1 = v1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = (c1[i] < 128)?c1[i]:128;
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_clamp_LUT(benchmark::State& state){
    /*Performance is better because the predictor can actually work now, no ideal though
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned char> v1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand()%256;
    }
    unsigned char* c1 = v1.data();
    unsigned char LUT[256] = {0,1,2,3,4,5,6,7,8,9,
                              10,11,12,13,14,15,16,17,18,19,
                              20,21,22,23,24,25,26,27,28,29,
                              30,31,32,33,34,35,36,37,38,39,
                              40,41,42,43,44,45,46,47,48,49,
                              50,51,52,53,54,55,56,57,58,59,
                              60,61,62,63,64,65,66,67,68,69,
                              70,71,72,73,74,75,76,77,78,79,
                              80,81,82,83,84,85,86,87,88,89,
                              90,91,92,93,94,95,96,97,98,99,
                              100,101,102,103,104,105,106,107,108,109,
                              110,111,112,113,114,115,116,117,118,119,
                              120,121,122,123,124,125,126,127,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128,128,128,128,128,128,
                              128,128,128,128,128,128};

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = LUT[c1[i]];
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_clamp_min(benchmark::State& state){
    /*Performance is better because the predictor can actually work now, no ideal though
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned char> v1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand()%256;
    }
    unsigned char* c1 = v1.data();
    unsigned char bound = 128;
    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::min(c1[i],bound);
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_clamp_branchless(benchmark::State& state){
    /*Performance is better because the predictor can actually work now, no ideal though
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned char> v1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand()%256;
    }
    unsigned char* c1 = v1.data();
    unsigned char bound = 128;
    for (auto _:state){
        bool is_less = true;
        for (size_t i =0;i<N;++i){
            is_less = c1[i] <= bound;
            c1[i] = c1[i] * is_less + 128 * !is_less;
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

BENCHMARK(BM_branch_clamp)->Arg(1<<22); // still faster than lookup - need to check assembly
BENCHMARK(BM_branch_clamp_LUT)->Arg(1<<22);
BENCHMARK(BM_branch_clamp_min)->Arg(1<<22);
BENCHMARK(BM_branch_clamp_branchless)->Arg(1<<22);
BENCHMARK_MAIN();