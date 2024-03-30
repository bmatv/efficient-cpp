//
// Created by bogdan on 30/03/24.
//
#include <iostream>

class Rational{
public: // definition
    Rational& operator+=(const Rational& rhs); // definition of the function
    Rational operator+(const Rational& other) const; // does not modify class values
    long n_{1}; // numerator w default value of 1
    long d_{1}; // denominator w default value of 1
    void reduce();
    Rational(long n, long d);
};

// description of the function
Rational& Rational::operator+=(const Rational &rhs) {
    n_ = this->n_*rhs.d_ + rhs.n_*this->d_; // this pointer
    d_ = this->d_*rhs.d_;
    reduce();
    return *this;
}

Rational Rational::operator+(const Rational &other) const {
    return Rational {n_*other.d_ + other.n_*d_,d_*other.d_};
}

// This is just an operator overload for std::cout thus is not needed within class definition
std::ostream& operator<<(std::ostream &os, const Rational & rhs) {
    return os << rhs.n_ << "/" << rhs.d_;
}


long gcd(long a, long b){
    while (b != 0){
        long tmp = b;

        b = a % b;
        a = tmp;
    }
    return a;
}

void Rational::reduce() {
    long divisor = gcd(d_,n_);
    d_/=divisor;
    n_/=divisor;
}

Rational::Rational(long n, long d) {
    n_ = n;
    d_ = d;

    reduce();
}


int main(){
    long c = gcd(48,18);
    std::cout << "gcd of 48 and 18 is " <<  c << std::endl;
    Rational a (1,2),b (6,8); // default constructor present, can also run reduce now
//    Rational a {.n_ = 1,.d_ = 2},b {.n_ = 6,.d_ = 8}; // no default constructor in the class

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
//    a+=b;
//    std::cout << "a + b" << a << std::endl;
    std::cout << "a + b = " << a + b << std::endl;


}
