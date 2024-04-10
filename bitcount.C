//
// Created by bogdan on 4/04/24.
//
#include <iostream>
#include <cassert>
#include "libbitcount.h"
#include <bitset>
#include <iomanip>

#include <vector>

float genRandFloat(){
    return rand()/float(RAND_MAX); // outputs 0..1 values
//    return rand()/float(RAND_MAX)*24.f+1.f
}

int main(){
    float arr[]{0.1,0.2,0.3,0.4,0.5};

    for(int i = 0; i<5;++i) {
        int* a = reinterpret_cast<int*>(&arr[i]);
        std::cout << "a equals to " << a << '\n';
    }



    std::vector<uint8_t> vecA {0b11111111,
                    0b00010111,
                    0b11101001,
                    0b10100101,
                    0b11101011};

    std::vector<float>v(10);
    std::generate(v.begin(), v.end(), genRandFloat);

    for(float element:v){
        std::cout << element << ' ';
    }
    std::cout << '\n';

    // generate array A of 1M length
    // TODO check how fast is reinterpret_cast
//    auto randNum = genRandFloat();
//    std::cout << "some random number: " << randNum << " bits: "<< std::bitset<32>(*reinterpret_cast<int32_t*>(&randNum)) << '\n';

//    std::vector<uint8_t> vecB {0b11111111,
//                    0b00010111,
//                    0b11101001,
//                    0b10100101,
//                    0b11101011};


//    assert(vecA.size() == vecB.size());

    int nbits = 8;
    std::vector<std::vector<int>> C(nbits,std::vector<int>(4,0)); //should be [nbits,4]

//    bitPairCount(vecA,vecB,C);
    uint8_t mask;
    int idxA = 0, idxB = 0;
//    for (size_t i = 0; i< vecA.size(); ++i){
    for (size_t i = 0; i< vecA.size()-1; ++i){
        mask = 1;
        for (int j = 0; j< nbits; ++j){
            idxA = (vecA[i] & mask) >> j;
//            idxB = (vecB[i] & mask) >> j;
            idxB = (vecA[i+1] & mask) >> j;
            C[j][idxA + idxB*2] += 1;
            mask <<= 1;
        }
    }

//    for each element pair in vector A and B, for each bit get +1 into one of 4 bitpair elements
    std::cout << " 00 01 10 11\n -----------\n";
    for(auto vec:C){
        for(auto num:vec){
            std::cout << std::setw(3)<< num;
        }
        std::cout << '\n';
    }

    // having C I should be able to get P which is the addition of counts per each bit and division of the sum by total count of elements
    std::vector<uint8_t > P(4,0.0);

    for(int i = 0; i < nbits; ++i){
        for(int j = 0; j < 4; ++j){
            P[j] += C[i][j];
        }
    }

    for (uint8_t element:P){
        std::cout << "P element. SUM = " << (int)element << "|Probability = " << (double) element / (vecA.size() * nbits) << '\n';
    }




}



//std::vector<int> bitcount(std::vector<uint8_t> vec);

//int main()
//{
////    constexpr int nbits = 8 * sizeof(int);
//
//    const int nbits = 8;
//
//
//    std::vector<uint8_t> vecA {0b10001111,
//                               0b00010111,
//                               0b11101000,
//                               0b10100100,
//                               0b11101011};
//
//    std::vector<uint8_t> vecB {0b10001111,
//                               0b00010111,
//                               0b11101000,
//                               0b10100100,
//                               0b11101011};
////    {0b01000010,
////    0b11110110,
////    0b01010110,
////    0b01111111,
////    0b00010100};
//
//
//
//    for (auto num:vecA){
//        std::cout << std::setw(3)<< num << " : "  << std::bitset<nbits> (num) <<'\n';
//    }
//    std::cout << "--------------------------------"<< '\n';
//
//
//
////    std::vector<float>v (10);
////
////    std::generate(v.begin(),v.end(),genRandFloat);
////
////    for (auto& i:vecA){
////        std::cout << std::setw(10) << i << ": "<< std::bitset<32>(*reinterpret_cast<int*>(&i)) << '\n';
////    }
//
//    std::vector<int> C = bitcount(vecA);
//
//    for (auto& i:C){
//        std::cout << i <<' ';
//    }
//    std::cout << '\n';
//
//}








//std::vector<int> bitcount(std::vector<uint8_t> vec){
//    std::vector<int> C(8, 0); // throwing sums in here
//
//
//    for(auto& number:vec) {
//        int8_t mask = 1;
//        for (int i = 0; i < (8); ++i) {
//            C[i] += ((number & mask) >> i);
////            std::cout << ((number & mask) >> i);
//            mask <<= 1;
//        }
//
//    }
////    for (auto c:C){std::cout << c << ' ';}
//return C;
//
////    std::cout << '\n';
//}

//#include <iostream>
//#include <bitset>
//
//int main()
//{
//    uint32_t v = 0b1000;
//    std::cout << std::bitset<32>(v >> 1) << std::endl;
//
//    return 0;
//}