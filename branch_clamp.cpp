//
// Created by bogdan on 30/11/23.
//
#include "benchmark/benchmark.h"
#include <algorithm>
#include <iostream>
#include <immintrin.h>
#include <smmintrin.h>

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

    __m128i ma_l = _mm_load_si128((__m128i*) v1.data());
//    _mm_min_epi8()
    //    _mm256_cvtepi8_epi16
//    _mm_min_epi16()
//    extern _mm256
//    _mm_min_epu8()
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

int sumup_char_arrays(char *A, char *B, int size) {
    assert (size % 32 == 0);
    int sum = 0;
    __m256i sum_tmp;
    for (int i = 0; i < size; i += 32) {
        __m256i ma_l = _mm256_cvtepi8_epi16(_mm_load_si128((__m128i*)A));
        __m256i ma_h = _mm256_cvtepi8_epi16(_mm_load_si128((__m128i*)(A+16)));
        __m256i mb_l = _mm256_cvtepi8_epi16(_mm_load_si128((__m128i*)B));
        __m256i mb_h = _mm256_cvtepi8_epi16(_mm_load_si128((__m128i*)(B+16)));
        __m256i mc = _mm256_madd_epi16(ma_l, mb_l);
        mc = _mm256_add_epi32(mc, _mm256_madd_epi16(ma_h, mb_h));
        sum_tmp = _mm256_add_epi32(mc, sum_tmp);
        //sum += A[i]*B[i];
    }
    sum_tmp = _mm256_add_epi32(sum_tmp, _mm256_permute2x128_si256(sum_tmp, sum_tmp, 0x81));
    sum_tmp = _mm256_add_epi32(sum_tmp, _mm256_srli_si256(sum_tmp, 8));
    sum_tmp = _mm256_add_epi32(sum_tmp, _mm256_srli_si256(sum_tmp, 4));
    sum = _mm256_extract_epi32(sum_tmp, 0);
    return sum;
}


BENCHMARK(BM_branch_clamp)->Arg(1<<22); // still faster than lookup - need to check assembly
BENCHMARK(BM_branch_clamp_LUT)->Arg(1<<22);
BENCHMARK(BM_branch_clamp_min)->Arg(1<<22);
BENCHMARK(BM_branch_clamp_branchless)->Arg(1<<22);
BENCHMARK_MAIN();