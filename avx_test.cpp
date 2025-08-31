//
// Created by bogdan on 1/12/23.
//
#include <random>
//#include <avx2intrin.h>
#include <immintrin.h>
//#include <xmmintrin.h>
#include <vector>
#include <smmintrin.h>

#include <iostream>

int main(){
    srand(1);
    unsigned int N =16;
    std::vector<unsigned char> v1(N);

    for(size_t i=0;i<N;++i) {
        v1[i] = rand() % 256;
    }

//    __m128i ma_l = _mm_load_si128((__m128i*) v1.data());

//    __m128i out = _mm_min_epi8(ma_l, _mm256_set1_epi8(128));
//    auto a = _mm_load_si128((__m128*) v1.data());
//    __mm256 a = _mm_load_si128((__m128*) v1.data());
//    _mm_load_
//    __m256i ma_l = _mm256_cvtepi8_epi16(_mm_load_si128((__m128i*)v1.data()));
//    __m256i bound = _mm256_cvtepi8_epi16()
    __m128i vec = _mm_setr_epi8(v1[0],v1[1],v1[2],v1[3],v1[4],v1[5],v1[6],v1[7],v1[8],v1[9],v1[10],v1[11],v1[12],v1[13],v1[14],v1[15]);
//    int b = _mm_extract_epi8(vec,1);
    __m128i scalar = _mm_set1_epi8(127);
    __m128i vec_out = _mm_min_epi8(vec,scalar);

    std::cout << _mm_extract_epi8(vec,0)<< ' ' <<_mm_extract_epi8(vec,1) << ' ' <<_mm_extract_epi8(vec,2) <<' ' <<_mm_extract_epi8(vec,3) << ' '
            << _mm_extract_epi8(vec,4)<< ' ' <<_mm_extract_epi8(vec,5) << ' ' <<_mm_extract_epi8(vec,6) <<' ' <<_mm_extract_epi8(vec,7)<< ' '
            << _mm_extract_epi8(vec,8)<< ' ' <<_mm_extract_epi8(vec,9) << ' ' <<_mm_extract_epi8(vec,10) <<' ' <<_mm_extract_epi8(vec,11)<< ' '
            << _mm_extract_epi8(vec,12)<< ' ' <<_mm_extract_epi8(vec,13) << ' ' <<_mm_extract_epi8(vec,14) <<' ' <<_mm_extract_epi8(vec,15) << '\n';

    std::cout << _mm_extract_epi8(scalar,0)<< ' ' <<_mm_extract_epi8(scalar,1) << ' ' <<_mm_extract_epi8(scalar,2) <<' ' <<_mm_extract_epi8(scalar,3) << ' '
              << _mm_extract_epi8(scalar,4)<< ' ' <<_mm_extract_epi8(scalar,5) << ' ' <<_mm_extract_epi8(scalar,6) <<' ' <<_mm_extract_epi8(scalar,7)<< ' '
              << _mm_extract_epi8(scalar,8)<< ' ' <<_mm_extract_epi8(scalar,9) << ' ' <<_mm_extract_epi8(scalar,10) <<' ' <<_mm_extract_epi8(scalar,11)<< ' '
              << _mm_extract_epi8(scalar,12)<< ' ' <<_mm_extract_epi8(scalar,13) << ' ' <<_mm_extract_epi8(scalar,14) <<' ' <<_mm_extract_epi8(scalar,15) << '\n';


    std::cout << _mm_extract_epi8(vec_out,0)<< ' ' <<_mm_extract_epi8(vec_out,1) << ' ' <<_mm_extract_epi8(vec_out,2) <<' ' <<_mm_extract_epi8(vec_out,3) << ' '
              << _mm_extract_epi8(vec_out,4)<< ' ' <<_mm_extract_epi8(vec_out,5) << ' ' <<_mm_extract_epi8(vec_out,6) <<' ' <<_mm_extract_epi8(vec_out,7)<< ' '
              << _mm_extract_epi8(vec_out,8)<< ' ' <<_mm_extract_epi8(vec_out,9) << ' ' <<_mm_extract_epi8(vec_out,10) <<' ' <<_mm_extract_epi8(vec_out,11)<< ' '
              << _mm_extract_epi8(vec_out,12)<< ' ' <<_mm_extract_epi8(vec_out,13) << ' ' <<_mm_extract_epi8(vec_out,14) <<' ' <<_mm_extract_epi8(vec_out,15) << '\n';

//    for(size_t i=0;i<10;++i){
//        const int j = i;
//        int b = _mm_extract_epi8(vec,j);
//        std::cout << b  << ' ';
//    }


            //    auto out = _mm_min_epu8(_mm_load_si128((__m128*) v1.data()), _mm_set1_epi8(128));
//    _mm256_min_epi8()
//    _mm_min_epu8()
//    auto out = _mm256_min_epi8(_mm256_loadu_epi8(v1.data()),_mm256_set1_epi8(128));

//    _mm256_extract_epi8(out,32);

}
