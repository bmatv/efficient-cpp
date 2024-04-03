#include <iostream>
#include <bitset>
#include <vector>
#include <iomanip>

//float genRandFloat(){
//    return rand()/float(RAND_MAX);
////    return rand()/float(RAND_MAX)*24.f+1.f
//}

int main()
{
//    constexpr int nbits = 8 * sizeof(int);

    const int nbits = 8;


    std::vector<uint8_t> vec {0b10001111,
                               0b00010111,
                               0b11101000,
                               0b10100100,
                               0b11101011};
//    {0b01000010,
//    0b11110110,
//    0b01010110,
//    0b01111111,
//    0b00010100};



    for (auto num:vec){
        std::cout << std::setw(3)<< num << " : "  << std::bitset<nbits> (num) <<'\n';
    }
    std::cout << "--------------------------------"<< '\n';

    std::vector<int> C(nbits, 0); // throwing sums in here


    for(auto& number:vec) {
        int8_t mask = 1;
        for (int i = 0; i < (nbits); ++i) {
            C[i] += ((number & mask) >> i);
//            std::cout << ((number & mask) >> i);
            mask <<= 1;
        }

    }
    for (auto c:C){std::cout << c << ' ';}

    std::cout << '\n';

//    std::vector<float>v (10);
//
//    std::generate(v.begin(),v.end(),genRandFloat);
//
//    for (auto& i:v){
//        std::cout << std::setw(10) << i << ": "<< std::bitset<32>(*reinterpret_cast<int*>(&i)) << '\n';
//    }

}


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