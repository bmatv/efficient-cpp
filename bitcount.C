//
// Created by bogdan on 4/04/24.
//
#include <iostream>
#include <cassert>
#include "libbitcount.h"
#include <bitset>
#include <iomanip>
#include <cmath>
#include <vector>

float genRandFloat(){
    return rand()/float(RAND_MAX); // outputs 0..1 values
//    return rand()/float(RAND_MAX)*24.f+1.f
}


//int* genMaskArray32(){
//    int maskArray[32]{};
//    for(int i=0; i<32; ++i){
//        maskArray[i] = (static_cast<int>(1) << i);
//    }
//    return maskArray;
//}

int main(){
//    std::vector<float>vec(10);
//    std::generate(vec.begin(), vec.end(), genRandFloat);
//    assert(vecA.size() == vecB.size());
    std::vector<float>vec{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483};

    // have to create a long vector with ~1m of values to properly assess the AVX implementation and how to load stuff in chunks

//    std::vector<float>vec{0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584,0.43579006,
//                          0.9274405,0.5442584,0.43579006,0.54717463,0.29385483,0.9274405,0.5442584};


    std::cout << "sizeof (vec) = " << vec[0] << '\n';

    for(float element:vec){
        std::cout << element << ' ';
    }
    std::cout << '\n';

    const int nbits = sizeof(vec[0]) * 8; // should be 32 and can be unsigned if that makes sense
    std::vector<std::vector<int>> C(nbits,std::vector<int>(4,0)); //should be [nbits,4], could be a basic 1D array
//    std::vector<std::vector<int>> C_fast(nbits,std::vector<int>(4,0)); //should be [nbits,4], could be a basic 1D array
//    bitPairCount(vecA,vecB,C);

    int maskArray[32]{};
    for(int i=0; i<32; ++i) {
        maskArray[i] = (static_cast<int>(1) << i);
    }

    int idxA = 0, idxB = 0;
    int A, B;
    size_t total = vec.size()-1;

//    for (int j = 0; j< nbits; ++j){
//        for (size_t i = 0; i< vec.size()-1; ++i){
//            // collect 0 bits of each number into one long bitstream, create two bitstreams by chopping the end and the head
//            // do the logic manipulation with popcount to compute quanities of 00, 01, 10, 11.
//            // involves lots of jumping thus might not be that efficient
//        }
//    }

    for (size_t i = 0; i< vec.size()-1; ++i){
        A = *reinterpret_cast<int*>(&vec[i]);
        B = *reinterpret_cast<int*>(&vec[i+1]);

        for (int j = 0; j< nbits; ++j){
            idxA = (A & maskArray[j]) >> j;
            idxB = (B & maskArray[j]) >> j;
            C[j][idxA + idxB*2] += 1; // OK but a bit different order which is fine
        }
    }

//    for each element pair in vector A and B, for each bit get +1 into one of 4 bitpair elements

    std::cout << "Printing C\n 00 01 10 11\n -----------\n";
    for(auto vec:C){
        for(auto num:vec){
            std::cout << std::setw(3)<< num;
        }
        std::cout << '\n';
    }

    std::vector<std::vector<double> > P (nbits, std::vector<double>(4,0.0));
//    std::vector<double > P(4,0.0);

    //for each bit, need to compute P[4]

    double m[nbits] {};
    double mSum = 0;
    for(int i = 0; i < nbits; ++i){
        for(int j = 0; j < 4; ++j){
            P[i][j] = double(C[i][j]) / total;
        }
        double py[] {P[i][0] + P[i][1],P[i][2] + P[i][3]};
        double px[] {P[i][0] + P[i][2],P[i][1] + P[i][3]};


        for (int ii = 0; ii< 2;++ii){
            for (int jj = 0; jj < 2; ++jj){
                if (P[i][ii + jj*2] > 0)
                    m[i] += P[i][ii + jj * 2] * log(P[i][ii + jj * 2] / px[ii] / py[jj]);
            }
        }
        m[i] /= log(2);
        mSum += m[i];
        std::cout << "M = " << m[i] << '\n';
    }
    double accumulator = 0;

    int bitsToKeep = 0;
    for (int i = (nbits - 1); i >=0; --i){ // can't be size_t as size_t(0) - 1 => 0 and the loop never stops
        if(accumulator < 0.99) {
            accumulator += m[i]/mSum;
            bitsToKeep++;
        }
        else {
            continue;
        }
//            std::cout << "accumulator value = " << accumulator <<'\n';
    }
    std::cout << "ARG value = " << bitsToKeep - 9 << '\n';
    std::cout << "accumulator value = " << accumulator <<'\n';

    std::cout << "M_sum = " << mSum << '\n';

}