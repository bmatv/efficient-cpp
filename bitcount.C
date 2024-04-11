//
// Created by bogdan on 4/04/24.
//
#include <iostream>
#include <cassert>
#include "libbitcount.h"
#include <bitset>
#include <iomanip>
#include <math.h>
#include <vector>

float genRandFloat(){
    return rand()/float(RAND_MAX); // outputs 0..1 values
//    return rand()/float(RAND_MAX)*24.f+1.f
}

int main(){

//    float arr[]{0.1,0.2,0.3,0.4,0.5};
//
//    for(int i = 0; i<5;++i) {
//        int* a = reinterpret_cast<int*>(&arr[i]); // 32 bits int
//        std::cout << "a equals to " << a << '\n';
//    }



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

//    std::vector<float>vec(10);
//    std::generate(vec.begin(), vec.end(), genRandFloat);

    std::vector<float>vec{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483};

    for(float element:vec){
        std::cout << element << ' ';
    }
    std::cout << '\n';

    const int nbits = sizeof(vec[0]) * 8; // should be 32 and can be unsigned if that makes sense
    std::vector<std::vector<int>> C(nbits,std::vector<int>(4,0)); //should be [nbits,4], could be a basic 1D array

//    bitPairCount(vecA,vecB,C);
    int mask;
    int idxA = 0, idxB = 0;
    int A, B;
//    for (size_t i = 0; i< vecA.size(); ++i){
    for (size_t i = 0; i< vec.size()-1; ++i){
        mask = 1;
        A = *reinterpret_cast<int*>(&vec[i]);
        B = *reinterpret_cast<int*>(&vec[i+1]);



        for (int j = 0; j< nbits; ++j){
            idxA = (A & mask) >> j;
            idxB = (B & mask) >> j;
            C[j][idxA + idxB*2] += 1; // OK but a bit different order which is fine
            mask <<= 1;
        }
//        std::cout << std::bitset<nbits>(A) << '\n' << std::bitset<nbits>(B) << "\n---------------\n";
    }

//    for each element pair in vector A and B, for each bit get +1 into one of 4 bitpair elements

//    std::cout << "Printing C\n 00 01 10 11\n -----------\n";
//    for(auto vec:C){
//        for(auto num:vec){
//            std::cout << std::setw(3)<< num;
//        }
//        std::cout << '\n';
//    }

    // having C I should be able to get P which is the addition of counts per each bit and division of the sum by total count of elements
    std::vector<std::vector<double> > P (nbits, std::vector<double>(4,0.0));
//    std::vector<double > P(4,0.0);
    double total = vec.size()-1;
    //for each bit, need to compute P[4]
    for(int i = 0; i < nbits; ++i){
        for(int j = 0; j < 4; ++j){
            P[i][j] = double(C[i][j]) / total;
        }
        double py[] {P[i][0] + P[i][1],P[i][2] + P[i][3]};
        double px[] {P[i][0] + P[i][2],P[i][1] + P[i][3]};

        double M=0;
        for (int ii = 0; ii< 2;++ii){
            for (int jj = 0; jj < 2; ++jj){
                if (P[i][ii + jj*2] > 0)
                    M += P[i][ii + jj*2]*log(P[i][ii + jj*2]/px[ii]/py[jj]);
            }
        }
        std::cout << "M = " << M / log(2) << '\n';


//        std::cout << px[0] << ' ' << px[1] << ' ' << py[0] << ' ' << py[1] <<'\n';
//        for(int j = 0; j < 4; ++j){
//            if (P[i][j] > 0)
//                ; //M += p[i,j]*log(p[i,j]/px[i]/py[j])
//        }
        // Computing mutual information now
//        px =

//    M += p[i,j]*log(p[i,j]/px[i]/py[j])
// M should be a double array of 32 that gets new value as all 4 of P have been computed

    }
    // Computing mutual information now

//    M += p[i,j]*log(p[i,j]/px[i]/py[j])


//    for(int j = 0; j < 4; ++j){
//        for(int i = 0; i < nbits; ++i){
//
//            buf += C[i][j];
//        }
//        P[j] = buf / total;
//        buf = 0;
//    }

//    auto Prob = static_cast<float>(P);

//    for (auto v:P){
//        std::cout << "P ";
//        for (auto element:v){
//            std::cout << element << " ";
//        }
//        std::cout << '\n';
//
//
//    }

//    std::cout << "marginal probability P_(r=0) = " << P[0] + P[1] << " | P_(r=1)" << P[2] + P[3] <<'\n';
//
//    std::cout << "marginal probability P_(s=0) = " << P[0] + P[2] << " | P_(s=1)" << P[1] + P[3] <<'\n';


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