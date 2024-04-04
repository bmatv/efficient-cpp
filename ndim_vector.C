//
// Created by bogdan on 4/04/24.
//
#include <vector>
#include <iostream>


void cout_vec_dim3() {
    std::vector<std::vector<std::vector<int>>> vec(8, std::vector<std::vector<int>>(2, std::vector<int>(2)));
    for (auto subsubvec: vec) {
        for (auto subvec: subsubvec) {
            for (auto num: subvec) {
                std::cout << num;
            }
            std::cout << '|';
        }
        std::cout << '\n';
    }
}


void cout_vec_dim2() {
    std::vector<std::vector<int>> vec(8, std::vector<int>(4, 0));
    for (auto subvec: vec) {
        for (auto num: subvec) {
            std::cout << num;
        }
        std::cout << "|\n";
    }
}

int main() {
    std::cout << "writing out a sample 2 dim vector" << '\n';
    cout_vec_dim2();
    std::cout << "writing out a sample 3 dim vector" << '\n';
    cout_vec_dim3();
}