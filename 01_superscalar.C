//
// Created by bogdan on 19/11/23.
//
#define MCA_START __asm volatile("# LLVM-MCA-BEGIN");
#define MCA_END __asm volatile("# LLVM-MCA-END");


#include "benchmark/benchmark.h"
#include <random>
using std::rand;
using std::srand;

void BM_add(benchmark::State& state){
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
        for (size_t i = 0; i < N; ++i) {
            MCA_START;
            a1 += p1[i] * p2[i];
            MCA_END;
        }

    benchmark::DoNotOptimize(a1);
	benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(N*state.iterations());
}

//void BM_div(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] / p2[i];
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}
//
//void BM_multiply(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] * p2[i];
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}
//
//void BM_add_multiply(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        unsigned long a2 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] + p2[i];
//            a2 += p1[i] * p2[i];
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::DoNotOptimize(a2);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}
//
//void BM_add_div(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        unsigned long a2 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] + p2[i];
//            a2 += p1[i] / p2[i];
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::DoNotOptimize(a2);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}
//
//
//
//
//void BM_add_multiply_sub_shift(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        unsigned long a2 = 0;
//        unsigned long a3 = 0;
//        unsigned long a4 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] + p2[i];
//            a2 += p1[i] * p2[i];
//            a3 += p2[i] - p1[i];
//            a4 += p1[i] << 2;
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::DoNotOptimize(a2);
//        benchmark::DoNotOptimize(a3);
//        benchmark::DoNotOptimize(a4);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}
//
//void BM_pipeline7(benchmark::State& state){
//    // generating test data
//    srand(1);
//    const unsigned int N = state.range(0);
//    std::vector<unsigned long> v1(N), v2(N);
//    for (size_t i = 0; i < N; ++i) {
//        v1[i] = rand(); v2[i] = rand();
//    }
//    unsigned long* p1 = v1.data();
//    unsigned long* p2 = v2.data();
//    for (auto _ : state) {
//        unsigned long a1 = 0;
//        unsigned long a2 = 0;
//        unsigned long a3 = 0;
//        unsigned long a4 = 0;
//        unsigned long a5 = 0;
//        unsigned long a6 = 0;
//        unsigned long a7 = 0;
//        for (size_t i = 0; i < N; ++i) {
//            a1 += p1[i] + p2[i];
//            a2 += p1[i] * p2[i];
//            a3 += p2[i] - p1[i];
//            a4 += p1[i] << 2;
//            a5 += p1[i] + 1;
//            a6 += p2[i] * p2[i];
//            a7 += p1[i] - p2[i];
//        }
//
//        benchmark::DoNotOptimize(a1);
//        benchmark::DoNotOptimize(a2);
//        benchmark::DoNotOptimize(a3);
//        benchmark::DoNotOptimize(a4);
//        benchmark::DoNotOptimize(a5);
//        benchmark::DoNotOptimize(a6);
//        benchmark::DoNotOptimize(a7);
//        benchmark::ClobberMemory();
//    }
//
//    state.SetItemsProcessed(N*state.iterations());
//}

BENCHMARK(BM_add)->Arg(1<<22);
//BENCHMARK(BM_multiply)->Arg(1<<22);
//BENCHMARK(BM_div)->Arg(1<<22);
//BENCHMARK(BM_add_multiply)->Arg(1<<22);
//BENCHMARK(BM_add_div)->Arg(1<<22);
//BENCHMARK(BM_add_multiply_sub_shift)->Arg(1<<22);
//BENCHMARK(BM_pipeline7)->Arg(1<<22);
BENCHMARK_MAIN();
