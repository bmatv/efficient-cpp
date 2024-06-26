//
// Created by bogdan on 12/04/24.
//
#include <iomanip>
#include <iostream>
#include <immintrin.h>
#include <bitset>
#include <vector>
#include <algorithm>

float genRandFloat(){
    return rand()/float(RAND_MAX); // outputs 0..1 values
//    return rand()/float(RAND_MAX)*24.f+1.f
}

int main() {
//    float a[15]{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584,0.43579006,
//                0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584};
//    float a[8] = {0.9274405,0.5442584,0.43579006,0.54717463,0.29385483, 0.9274405,0.5442584,0.43579006};

    std::vector<float>a{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584,0.43579006,
                          0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584};

//    for(auto& row:maskArray){
//        std::cout << row[0] << ", ";
//    }
//    std::cout <<'\n';

    int mask[32] = {1, 2, 4, 8, 16, 32, 64, 128,
                  256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
                  65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
                  16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, -2147483648};


//    std::vector<float>a(1000);
//    std::generate(a.begin(), a.end(), genRandFloat);

    int c[8];

//    for (float & i : a){
//        std::cout << std::setw(8)<< i << ": "<< std::bitset<32>(*reinterpret_cast<int*>(&i)) << '\n';
//    }

    int C[32][4] {};

    std::cout << "total size of vector is " << a.size() <<". Aligned size for AVX is " << a.size() - a.size() % 7 << '\n';

  auto total = a.size() - a.size() % 7;
    for (size_t j = 1; j <= total; j+=7){
//        std::cout << "Printing batches of values to be loaded to AVX registers\n";
//        for (int i = 0; i<8; i++){
//            std::cout << a[j - 1 + i] << ' ';
////            std::cout << std::setw(8)<< i << ": "<< std::bitset<32>(*reinterpret_cast<int*>(&i)) << '\n';
//        }
//        std::cout << '\n';


        __m256 a8 = _mm256_loadu_ps(&a[j-1]);
        for (int i = 0; i < 32; ++i) {

//            __m256i b8 = _mm256_loadu_si256((__m256i *) maskArray[i]); // masks

//            _mm256_set1_ps
            __m256i b8 = _mm256_set1_epi32(mask[i]);
            // __m256i _mm256_set1_epi32 (int a) Broadcast 32-bit integer a to all elements of dst. This intrinsic may generate the vpbroadcastd.

//            __m256 c8 = _mm256_castps_si256(_mm256_and_ps(a8, _mm256_castsi256_ps(b8)));
            __m256 c8 = _mm256_and_ps(a8, _mm256_castsi256_ps(b8));
            // __m256 _mm256_and_ps (__m256 a, __m256 b) Compute the bitwise AND of packed single-precision (32-bit) floating-point elements in a and b, and store the results in dst.
            // __m256i _mm256_castps_si256 (__m256 a) Cast vector of type __m256 to type __m256i. This intrinsic is only used for compilation and does not generate any instructions, thus it has zero latency.
            __m256 d8 = _mm256_cmp_ps(c8,_mm256_set1_ps(0),_CMP_GT_OS); // a>b

            __m256 _result = _mm256_and_ps(d8, _mm256_castsi256_ps(_mm256_set1_epi32(1))); // getting 0 and 1 mask with AVX1

            _mm256_storeu_si256((__m256i *) c, _mm256_castps_si256(_result));


            for(size_t idx_c = 0; idx_c<7;++i){
            C[i][c[idx_c] + c[idx_c+1]*2] ++; // this index computation could potentially be done with AVX a[0:6] + a[1:7]*2, one value will be thrown away though
            }

        }

    }
    std::cout << "Printing C (AVX)\n 00 01 10 11\n -----------\n";
    for(auto & bitPairs : C) {
        for(auto & pairCount:bitPairs) { std::cout << pairCount << ' '; }
        std::cout <<'\n';
    }
}


//__m256 _mm256_hadd_ps (__m256 a, __m256 b)
//Synopsis
//        __m256 _mm256_hadd_ps (__m256 a, __m256 b)
//#include <immintrin.h>
//Instruction: vhaddps ymm, ymm, ymm
//CPUID Flags: AVX
//        Description
//Horizontally add adjacent pairs of single-precision (32-bit) floating-point elements in a and b, and pack the results in dst.
//Operation
//        dst[31:0] := a[63:32] + a[31:0]
//dst[63:32] := a[127:96] + a[95:64]
//dst[95:64] := b[63:32] + b[31:0]
//dst[127:96] := b[127:96] + b[95:64]
//dst[159:128] := a[191:160] + a[159:128]
//dst[191:160] := a[255:224] + a[223:192]
//dst[223:192] := b[191:160] + b[159:128]
//dst[255:224] := b[255:224] + b[223:192]
//dst[MAX:256] := 0