#include "simde/x86/avx512/add.h"
#include "simde/x86/avx512/loadu.h"
#include "simde/x86/avx512/storeu.h"
#include <cstdint>
#include <algorithm>

#include "benchmark/benchmark.h"

auto genRandFloat() -> float{
    return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 10; // outputs 0..10 values
}

auto genRandFloatVec(int64_t n) -> std::vector<float>{
    std::vector<float>vec(n);
    std::generate(vec.begin(), vec.end(), genRandFloat);
    return std::move(vec); 
}

void BM_ps_add_naive(benchmark::State& state){
    
    auto N = state.range(0);
    auto a = genRandFloatVec(N);
    auto b = genRandFloatVec(N);
    auto c = std::vector<float>(N);
    for (auto _ : state)
    {
      for(int i = 0; i< c.size();++i){
        c[i] = a[i] + b[i];
      }
    benchmark::DoNotOptimize(c);
    }
    benchmark::ClobberMemory();
    state.SetItemsProcessed(N);
}

void BM_ps_add_transform(benchmark::State& state){
    
    auto N = state.range(0);
    auto a = genRandFloatVec(N);
    auto b = genRandFloatVec(N);
    auto c = std::vector<float>(N);
    for (auto _ : state)
    {
      std::transform(a.begin(), a.end(), b.begin(), c.begin(), std::plus<float>());
      benchmark::DoNotOptimize(c);
    }
    benchmark::ClobberMemory();
    state.SetItemsProcessed(N);
}

void BM_ps_add_avx512(benchmark::State& state){
    auto N = state.range(0);
    auto a = genRandFloatVec(N);
    auto b = genRandFloatVec(N);
    auto c =std::vector<float>(N);
    simde__m512 va, vb, vc {};
    for (auto _ : state)
    {
      int chunks = N / 16;
      for (int j =0; j<chunks;++j){
        va = simde_mm512_loadu_ps(a.data()+(16*j));
        vb = simde_mm512_loadu_ps(b.data()+(16*j));
        vc = simde_mm512_add_ps(va, vb);
        simde_mm512_storeu_ps(c.data()+(16*j), vc);
      }
    benchmark::DoNotOptimize(c);
    }
    benchmark::ClobberMemory();
    state.SetItemsProcessed(N);
}

BENCHMARK(BM_ps_add_naive)->Arg(1 << 28);
BENCHMARK(BM_ps_add_transform)->Arg(1 << 28);
BENCHMARK(BM_ps_add_avx512)->Arg(1 << 28);

BENCHMARK_MAIN();


// int main(void) {
//   // auto vec = genRandFloatVec(10);
//   // float sum {};
//   // sum = std::accumulate(vec.begin(),vec.end(),static_cast<float>(0));
//   // std::cout << "The sum of elements is " << sum << '\n';
//   // for (auto& val:vec){
//   //   std::cout << val <<'\n';
//   // }
//   float a[32], b[32], c[32];

//   // std::mt19937 rng(123); // fixed seed for reproducibility
//   std::mt19937 rng(std::random_device{}());
//   std::uniform_int_distribution<int> dist(0, 99);

//   for (int i = 0; i < 32; i++) {
//     a[i] = static_cast<float>(dist(rng) * i);
//     b[i] = static_cast<float>(dist(rng) * i * 2);
//   }
//   for (int j =0; j<2;++j){
//     simde__m512 va = simde_mm512_loadu_ps(a+(16*j));
//     simde__m512 vb = simde_mm512_loadu_ps(b+(16*j));
//     simde__m512 vc = simde_mm512_add_ps(va, vb);
//     simde_mm512_storeu_ps(c+(16*j), vc);
//   }

//   for (int i = 0; i < 32; i++) {
//     printf("%f + %f = %f\n", a[i], b[i], c[i]);

//   }

//   return 0;
// }
