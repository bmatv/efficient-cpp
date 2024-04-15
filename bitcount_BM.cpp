//
// Created by bogdan on 4/04/24.
//
//
#include <iostream>
#include <bitset>
#include "benchmark/benchmark.h"
#include "libbitcount.h"
#include <immintrin.h>
//#include <cstdint>

void BM_bitpaircount_vec_float_bitshift_AVX(benchmark::State& state){

    int maskArray[32][8]{{1,    1,    1,    1,    1,    1,    1,    1,},
                         {2,    2,    2,    2,    2,    2,    2,    2,},
                         {4,    4,    4,    4,    4,    4,    4,    4,},
                         {8,    8,    8,    8,    8,    8,    8,    8,},
                         {16,   16,   16,   16,   16,   16,   16,   16,},
                         {32,   32,   32,   32,   32,   32,   32,   32,},
                         {64,   64,   64,   64,   64,   64,   64,   64,},
                         {128,  128,  128,  128,  128,  128,  128,  128,},
                         {256,  256,  256,  256,  256,  256,  256,  256,},
                         {512,  512,  512,  512,  512,  512,  512,  512,},
                         {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024,},
                         {2048,2048,2048,2048,2048,2048,2048,2048,},
                         {4096,4096,4096,4096,4096,4096,4096,4096,},
                         {8192,8192,8192,8192,8192,8192,8192,8192,},
                         {16384,16384,16384,16384,16384,16384,16384,16384,},
                         {32768,32768,32768,32768,32768,32768,32768,32768,},
                         {65536,65536,65536,65536,65536,65536,65536,65536,},
                         {131072,131072,131072,131072,131072,131072,131072,131072,},
                         {262144,262144,262144,262144,262144,262144,262144,262144,},
                         {524288,524288,524288,524288,524288,524288,524288,524288,},
                         {1048576,1048576,1048576,1048576,1048576,1048576,1048576,1048576,},
                         {2097152,2097152,2097152,2097152,2097152,2097152,2097152,2097152,},
                         {4194304,4194304,4194304,4194304,4194304,4194304,4194304,4194304,},
                         {8388608,8388608,8388608,8388608,8388608,8388608,8388608,8388608,},
                         {16777216,16777216,16777216,16777216,16777216,16777216,16777216,16777216,},
                         {33554432,33554432,33554432,33554432,33554432,33554432,33554432,33554432,},
                         {67108864,67108864,67108864,67108864,67108864,67108864,67108864,67108864,},
                         {134217728,134217728,134217728,134217728,134217728,134217728,134217728,134217728,},
                         {268435456,268435456,268435456,268435456,268435456,268435456,268435456,268435456,},
                         {536870912,536870912,536870912,536870912,536870912,536870912,536870912,536870912,},
                         {1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,1073741824,},
                         {-2147483648,-2147483648,-2147483648,-2147483648,-2147483648,-2147483648,-2147483648,-2147483648,},};

    float a[8] = {0.9274405,0.5442584,0.43579006,0.54717463,0.29385483, 0.9274405,0.5442584,0.43579006};
    int c[8];
    int C[32][4] {};

    for (auto _:state) {
        __m256 a8 = _mm256_loadu_ps(a);
        for (int i = 0; i < 32; ++i) {

            __m256i b8 = _mm256_loadu_si256((__m256i *) maskArray[i]); // masks
            __m256i c8 = _mm256_castps_si256(_mm256_and_ps(a8, _mm256_castsi256_ps(b8)));

            _mm256_storeu_si256((__m256i *) c, c8);

            C[i][(c[0] >> i) + ((c[1] >> i) << 1)] += 1; // could be also (c[0]>0) + (c[1]>0)*2
            C[i][(c[1] >> i) + ((c[2] >> i) << 1)] += 1;
            C[i][(c[2] >> i) + ((c[3] >> i) << 1)] += 1;
            C[i][(c[3] >> i) + ((c[4] >> i) << 1)] += 1;
            C[i][(c[4] >> i) + ((c[5] >> i) << 1)] += 1;
            C[i][(c[5] >> i) + ((c[6] >> i) << 1)] += 1;
            C[i][(c[6] >> i) + ((c[7] >> i) << 1)] += 1;
            C[i][(c[6] >> i) + ((c[7] >> i) << 1)] += 1;

        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations()*8);
}

float genRandFloat(){
    return rand()/float(RAND_MAX); // outputs 0..1 values
//    return rand()/float(RAND_MAX)*24.f+1.f
}

void BM_bitpaircount_vec_float_AVX(benchmark::State& state){

    int mask[32] = {1, 2, 4, 8, 16, 32, 64, 128,
                    256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
                    65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
                    16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, -2147483648};

    std::vector<float>a(1000);
    std::generate(a.begin(), a.end(), genRandFloat);

    int c[8];
    int C[32][4] {};

    long aligned_size = (a.size() - a.size() % 7);
    for (auto _:state) {
        for (int j = 1; j <= aligned_size; j+=7) {
            __m256 a8 = _mm256_loadu_ps(&a[j - 1]);
            for (int i = 0; i < 32; ++i) {

                __m256i b8 = _mm256_set1_epi32(mask[i]);
                // __m256i _mm256_set1_epi32 (int a) Broadcast 32-bit integer a to all elements of dst. This intrinsic may generate the vpbroadcastd.

//            __m256 c8 = _mm256_castps_si256(_mm256_and_ps(a8, _mm256_castsi256_ps(b8)));
                __m256 c8 = _mm256_and_ps(a8, _mm256_castsi256_ps(b8));
                // __m256 _mm256_and_ps (__m256 a, __m256 b) Compute the bitwise AND of packed single-precision (32-bit) floating-point elements in a and b, and store the results in dst.
                // __m256i _mm256_castps_si256 (__m256 a) Cast vector of type __m256 to type __m256i. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.
                __m256 d8 = _mm256_cmp_ps(c8,_mm256_set1_ps(0),_CMP_GT_OS); // a>b

                __m256 _result = _mm256_and_ps(d8, _mm256_castsi256_ps(_mm256_set1_epi32(1))); // getting 0 and 1 mask with AVX1

                _mm256_storeu_si256((__m256i *) c, _mm256_castps_si256(_result));



                C[i][c[0] + c[1]*2] ++;
                C[i][c[1] + c[2]*2] ++;
                C[i][c[2] + c[3]*2] ++;
                C[i][c[3] + c[4]*2] ++;
                C[i][c[4] + c[5]*2] ++;
                C[i][c[5] + c[6]*2] ++;
                C[i][c[6] + c[7]*2] ++;

            }
        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations()*aligned_size);
}

void BM_bitpaircount_vec_float(benchmark::State& state){

    std::vector<float>vec(1000);
    std::generate(vec.begin(), vec.end(), genRandFloat);
    size_t total = vec.size()-1;
    const int nbits = sizeof(vec[0]) * 8; // should be 32 and can be unsigned if that makes sense
//    std::vector<std::vector<int>> C(nbits,std::vector<int>(4,0)); //should be [nbits,4], could be a basic 1D array
    int C[nbits][4]{};

    int mask[32] = {1, 2, 4, 8, 16, 32, 64, 128,
                    256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
                    65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
                    16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, -2147483648};


    int idxA = 0, idxB = 0;
    int A, B;


    for (auto _:state) {
    // could be easily paralleled
    for (size_t i = 0; i< total; ++i){
        A = reinterpret_cast<int&>(vec[i]);
        B = reinterpret_cast<int&>(vec[i+1]);

        for (int j = 0; j< nbits; ++j){
            idxA = (A & mask[j]) > 0;
            idxB = (B & mask[j]) > 0;
            C[j][idxA + idxB*2] += 1; // OK but a bit different order which is fine
        }
    }

        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();

    }
    state.SetItemsProcessed(state.iterations()*1000);
}


void BM_reinterp_cast(benchmark::State& state){
//    std::vector<float> vec{0.1,0.2,0.3,0.4,0.5};
    float arr[]{0.1,0.2,0.3,0.4,0.5};
    int *a;
    for (auto _:state) {
        for(int i = 0; i<5;++i){
            a = reinterpret_cast<int*>(arr+i);

        }
        benchmark::DoNotOptimize(a);
        benchmark::ClobberMemory();


    }
    state.SetItemsProcessed(state.iterations()*5);
}

void BM_reinterp_cast_single(benchmark::State& state){
//    std::vector<float> vec{0.1,0.2,0.3,0.4,0.5};
//    float arr[]{0.1,0.2,0.3,0.4,0.5};
    float a = 0.1;
    int b;
    for (auto _:state) {
        b = reinterpret_cast<int&>(a);
        benchmark::DoNotOptimize(b);
        benchmark::ClobberMemory();


    }
    state.SetItemsProcessed(state.iterations());
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
    state.SetItemsProcessed(state.iterations()*5);
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
    state.SetItemsProcessed(state.iterations()*5);
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
    int C[8*4] {0,0,0,0,
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
                C[i*4 + ((vecA[j] & mask) >> i) + ((vecB[j] & mask) >> i)*2] ++;
                mask <<=1;
            }
        }
        benchmark::DoNotOptimize(C);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations()*5);
}


BENCHMARK(BM_bitpaircount_vec_float)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_vec_float_AVX)->Arg(1<<22);
BENCHMARK(BM_bitpaircount_vec_float_bitshift_AVX)->Arg(1<<22);

//BENCHMARK(BM_reinterp_cast)->Arg(1 << 22);
//BENCHMARK(BM_reinterp_cast_single)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_vec)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_array)->Arg(1 << 22);
BENCHMARK(BM_bitpaircount_array1d)->Arg(1 << 22);
//BENCHMARK(BM_bitcount_array)->Arg(1 << 22);
//BENCHMARK(BM_bitcount_array_fn)->Arg(1 << 22);
//BENCHMARK(BM_bitcount_array_fn_inline)->Arg(1 << 22);
//BENCHMARK(BM_bitcount_vec)->Arg(1 << 22);

BENCHMARK_MAIN();