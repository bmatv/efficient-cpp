//
// Created by bogdan on 29/11/23.
//
#include "benchmark/benchmark.h"
#include <iostream>
#include <vector>

void BM_branch_not_predicted(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        v2[i] = rand();
        c1[i] = rand() & 1; //rightmost bit as value (0 or 1)
    }
    unsigned long* p1 = v1.data(), *p2 = v2.data();
    int* b1 = c1.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        for (size_t i =0;i<N;++i){
            b1[i]?a1+=p1[i]:a1*=p2[i];
//            if (b1[i]){
//                a1+=p1[i];
//            }else{
//                a1*=p2[i];
//            }
        }
    benchmark::DoNotOptimize(a1);
    benchmark::DoNotOptimize(a2);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_predicted(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        v2[i] = rand();
        c1[i] = rand() >= 0; // always True
    }
    unsigned long* p1 = v1.data(), *p2 = v2.data();
    int* b1 = c1.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        for (size_t i =0;i<N;++i){
            b1[i]?a1+=p1[i]:a1*=p2[i];
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_switching(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        v2[i] = rand();
        if (i == 0) c1[i] = rand() >= 0;
        else c1[i] = !c1[i-1]; // produces 1,0,1,0...
    }
    unsigned long* p1 = v1.data(), *p2 = v2.data();
    int* b1 = c1.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        for (size_t i =0;i<N;++i){
            b1[i]?a1+=p1[i]:a1*=p2[i];
//            if (b1[i]) {
//                a1 += p1[i];
//            }else{
//                a1 *= p2[i];
//            }
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}
BENCHMARK(BM_branch_predicted)->Arg(1<<22);
BENCHMARK(BM_branch_not_predicted)->Arg(1<<22);
BENCHMARK(BM_branch_switching)->Arg(1<<22);
BENCHMARK_MAIN();
