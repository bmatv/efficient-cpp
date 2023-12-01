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
        else c1[i] = !c1[i-1]; // produces 1,0,1,0... but branch predictor works really well
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

void BM_branch_false(benchmark::State& state){
    /*Performance of the false branch is the same as that of random branch.
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    std::vector<int>c1(N), c2(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        v2[i] = rand();
        c1[i] = rand() & 1;
        c2[i] = !c1[1];
    }
    unsigned long* p1 = v1.data(), *p2 = v2.data();
    int* b1 = c1.data(), *b2 = c2.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        for (size_t i =0;i<N;++i){
            if (b1[i] || b2[i]){ // always True
                a1 += p1[i];
            }else{
                a1 *= p2[i]; // never reached but compiler doesn't know this, the OR condition is too complicated
            }
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_keysort(benchmark::State& state){
    /*Performance is great because ?: operator is using a lookup array instead of a conditional branch whenever possible. {a1,a2}[b[i]] += p1[i]
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        c1[i] = rand() & 1;
    }
    unsigned long* p1 = v1.data();
    int* b1 = c1.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        for (size_t i =0;i<N;++i){
            (b1[i]?a1:a2)+=p1[i];
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_branch_branchless(benchmark::State& state){
    /*Performance is better because the predictor can actually work now, no ideal though
     *
     */
    srand(1);
    unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = rand();
        v2[i] = rand();
        c1[i] = rand() & 1;
    }
    unsigned long* p1 = v1.data(), * p2 = v2.data();
    int* b1 = c1.data();

    for (auto _:state){
        unsigned long a1 = 0, a2 = 0;
        unsigned long* a[2] = {&a1,&a2};
        for (size_t i =0;i<N;++i){
            unsigned long s [2] = {p1[i] + p2[i], p1[i]*p2[i]};
            a[b1[i]] += s[b1[i]];
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
BENCHMARK(BM_branch_false)->Arg(1<<22);
BENCHMARK(BM_branch_keysort)->Arg(1<<22);
BENCHMARK(BM_branch_branchless)->Arg(1<<22);

BENCHMARK_MAIN();
