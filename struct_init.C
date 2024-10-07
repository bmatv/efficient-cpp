#include <iostream>

struct statistics {
  statistics(float sum_elements, int n_elements)
      : sum_elements(sum_elements), n_elements(n_elements) {}
  float sum_elements;
  int n_elements;

  float avg = sum_elements / static_cast<float>(n_elements);
};

int main() {
  statistics a{10, 5};

  std::cout << a.avg << '\n';
  a = {30, 5};
  std::cout << a.avg << '\n';
  // statistics b = a;{20, 4};
}
