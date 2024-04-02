#include <iostream>
#include <bitset>
#include <vector>
#include <iomanip>

float genRandFloat(){
    return rand()/float(RAND_MAX);
//    return rand()/float(RAND_MAX)*24.f+1.f
}

int main()
{

    std::vector<float>v (10);

    std::generate(v.begin(),v.end(),genRandFloat);

    for (auto& i:v){
        std::cout << std::setw(10) << i << ": "<< std::bitset<32>(*reinterpret_cast<int*>(&i)) << '\n';
    }

}