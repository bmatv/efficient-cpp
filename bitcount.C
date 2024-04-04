//
// Created by bogdan on 4/04/24.
//
#include <iostream>
#include <assert.h>
#include "libbitcount.h"

#include <iomanip>

#include <vector>

//void bitcount_array(uint8_t* array, int array_size, int* C) {
//    int8_t mask;
//    for (int j = 0; j < array_size; ++j) {
//        mask = 1;
//        for (int i = 0; i < 8; ++i) {
//            C[i] += ((array[j] & mask) >> i);
//            mask <<= 1;
//        }
//    }
//}

int main(){
//    uint8_t array[] {0b10001111,
//                     0b00010111,
//                     0b11101000,
//                     0b10100100,
//                     0b11101011};
//    int C [8] {};
//
//    bitcount_array(array, 5, C);
//
//    for (int i=0;i<8;++i){
//        std::cout << C[i] << '\n';
//    }



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

//    int C[4]{};
    uint8_t mask;

    for(int j = 0; j<vecA.size();++j){
        mask = 1;
        for (int i = 0; i<8;++i){

            C[j][((vecA[j] & mask) >> i) + ((vecB[j] & mask) >> i)*2] += 1;
//            std::cout << "bit" << i << ' ' << ((vecA[j] & mask) >> i) << " and " << ((vecB[j] & mask) >> i) << " +1 to " <<
//
//                                                                                                                         ((vecA[j] & mask) >> i) + ((vecB[j] & mask) >> i)*2 << '\n';
//            C[(vecA[i] & mask) >> j ]
            mask <<=1;
        }
//        std::cout << "--------" << '\n';


    }


    std::cout << " 00 01 10 11\n -----------\n";
    for(auto vec:C){
        for(auto num:vec){
            std::cout << std::setw(3)<< num;
        }
        std::cout << '\n';
    }



}

//float genRandFloat(){
//    return rand()/float(RAND_MAX);
////    return rand()/float(RAND_MAX)*24.f+1.f
//}

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