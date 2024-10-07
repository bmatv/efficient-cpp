//
// Created by Bogdan Matviichuk on 31.03.2024.
//
#include <memory>
#include <string>

struct FlyingBird {
public:
  // virtual void fly(int speed, double direction) = 0;
  virtual void f();
  ~FlyingBird() {};
};

struct Eagle : FlyingBird {
public:
  // void fly(int speed, double direction) override;
  std::string s{"some string"};
  ~Eagle() {};
};

void use() {
  std::unique_ptr<FlyingBird> p = std::make_unique<Eagle>();
  // ...
} // p's destruction calls ~Base(), not ~D(), which leaks D::s and possibly more

// int main() {
//     std::unique_ptr<FlyingBird> p = std::make_unique<Eagle>();
//     // p->fly();
// }
