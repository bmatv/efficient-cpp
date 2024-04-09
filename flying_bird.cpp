//
// Created by Bogdan Matviichuk on 31.03.2024.
//
class FlyingBird {
public:
    virtual void fly(...) = 0; // Pure virtual function
};

class Eagle : public FlyingBird {
public:
    void fly(int speed, double direction);
};

int main(){}