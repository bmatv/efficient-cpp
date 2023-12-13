//
// Created by bogdan on 13/12/23.
//
#include <iostream>


int main(){
    /*
     * Constant memory and O(n) computation complexity
     */
    int const size = 10;
    int s[size] {0,1,2,3,4,5,6,7,8,9}; // needs to be sorted for this approach to work
    int findSum = 15;

    int* idx_head = s;
    int* idx_tail = idx_head + size -1;

    int tmpSum =0;

    while(idx_head != idx_tail){
        tmpSum = *idx_head + *idx_tail;
        if (tmpSum == findSum){
            std::cout << *idx_head << " and " << *idx_tail << " produce " << findSum <<'\n';
//            return *idx_head, *idx_tail;
            return 0;
        }

        if (tmpSum > findSum){
//            std::cout << *idx_head << '+' << *idx_tail << " > " << findSum <<'\n';
            --idx_tail;
        }
        else{
//            std::cout << *idx_head << '+' << *idx_tail << " < " << findSum <<'\n';
            ++idx_head;
        }

    }
    std::cout << findSum << " could not be found" <<'\n';

    for(int& element:s){
        std::cout << element << ' ';
    }
}

