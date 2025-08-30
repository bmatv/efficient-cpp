#include "simde/x86/avx512.h"
#include <cstdlib>
#include <stdio.h>
#include <random>

int main(void) {
  float a[16], b[16], c[16];

  // std::mt19937 rng(123); // fixed seed for reproducibility
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, 99);

  for (int i = 0; i < 16; i++) {
    a[i] = static_cast<float>(dist(rng) * i);
    b[i] = static_cast<float>(dist(rng) * i * 2);
  }

  simde__m512 va = simde_mm512_loadu_ps(a);
  simde__m512 vb = simde_mm512_loadu_ps(b);
  simde__m512 vc = simde_mm512_add_ps(va, vb);
  simde_mm512_storeu_ps(c, vc);

  for (int i = 0; i < 16; i++) {
    printf("c[%d] = %f\n", i, c[i]);
  }

  return 0;
}
