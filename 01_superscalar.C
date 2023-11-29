//
// Created by bogdan on 19/11/23.
//
#define MCA_START __asm volatile("# LLVM-MCA-BEGIN");
#define MCA_END __asm volatile("# LLVM-MCA-END");


#include "benchmark/benchmark.h"
#include <random>
using std::rand;
using std::srand;

void BM_pp_add_mul(benchmark::State& state){
    // generating test data
    srand(1);
    const unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    for (size_t i = 0; i < N; ++i) {
        v1[i] = rand(); v2[i] = rand();
    }
    unsigned long* p1 = v1.data();
    unsigned long* p2 = v2.data();

        for (auto _ : state) {
        unsigned long a1 = 0;
        unsigned long a2 = 0;
//        unsigned long a3 = 0;
        for (size_t i = 0; i < N; ++i) {
//            MCA_START;
            a1 += p1[i] + p2[i];
            a2 += p1[i] * p2[i];
//            a3 += p2[i] - p1[i];
//            MCA_END;
        }

        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
//        benchmark::DoNotOptimize(a3);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(N*state.iterations());
}

void BM_add_multiply_dep(benchmark::State& state) {
    srand(1);
    const unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    for (size_t i = 0; i < N; ++i) {
        v1[i] = rand();
        v2[i] = rand();
    }
    unsigned long* p1 = v1.data();
    unsigned long* p2 = v2.data();
    for (auto _ : state) {
        unsigned long a1 = 0, a2 = 0;
        for (size_t i = 0; i < N; ++i) {
            a1 += (p1[i] + p2[i]) * (p1[i] - p2[i]); // cpu does pipelining automatically:

            //a1 += (p1[i] * p2[i]);
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    //state.SetBytesProcessed(N*sizeof(unsigned long)*state.iterations());
}

void BM_pp_add_sub_mul_dep(benchmark::State& state){
    // generating test data
    srand(1);
    const unsigned int N = state.range(0);
    std::vector<unsigned long> v1(N), v2(N);
    for (size_t i = 0; i < N; ++i) {
        v1[i] = rand(); v2[i] = rand();
    }
    unsigned long* p1 = v1.data();
    unsigned long* p2 = v2.data();

    unsigned long a1 = 0;

    unsigned long tmp1,tmp2 = 0;
    for (auto _ : state) {
        for (size_t i = 1; i < N; ++i) {

            a1 += tmp1 * tmp2;
//            MCA_START;
            tmp1 = (p1[i] + p2[i]);
            tmp2 = (p1[i] * p2[i]);
//            a1 += (p1[i] + p2[i]) * (p1[i] - p2[i]);
//            MCA_END;
        }
        a1 += tmp1 * tmp2;

        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(tmp1);
        benchmark::DoNotOptimize(tmp2);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(N*state.iterations());
}


BENCHMARK(BM_pp_add_mul)->Arg(1<<22);
BENCHMARK(BM_add_multiply_dep)->Arg(1<<22);
BENCHMARK(BM_pp_add_sub_mul_dep)->Arg(1<<22);
BENCHMARK_MAIN();
