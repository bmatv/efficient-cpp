#include "benchmark/benchmark.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "fast_pythagorean.h"

void genRandIntArrays(unsigned int N, std::vector<int> &v1, std::vector<int> &v2)
{
    const unsigned int M = 5000;
    for (size_t i = 0; i < N; ++i)
    {
        v1[i] = static_cast<int>(static_cast<float>(rand()) / RAND_MAX * M);
        v2[i] = static_cast<int>(static_cast<float>(rand()) / RAND_MAX * M);
    }
}


void BM_pythagorean(benchmark::State &state)
{
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    genRandIntArrays(N, v1, v2);

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            c1[i] = static_cast<int>(std::sqrt(
                static_cast<float>(v1[i] * v1[i] + v2[i] * v2[i])));
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_pythagorean_no_cast(benchmark::State &state)
{
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    genRandIntArrays(N, v1, v2);

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            c1[i] = std::sqrt(std::pow((v1[i]), 2.0F) + std::pow((v2[i]), 2.0F));
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

/// @brief can get as fast as sqrt implementation with -ffast-math, otherwise is 10 times slower
/// @param state 
void BM_pythagorean_powsqrt(benchmark::State &state)
{
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    genRandIntArrays(N, v1, v2);

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            c1[i] = pow(pow(v1[i], 2) + pow(v2[i], 2), 0.5);
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "2 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

/// @brief is the fastest if int explicitly casted to float, otherwise is very slow
/// @param state 
void BM_pythagorean_hypot_float(benchmark::State &state)
{
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    genRandIntArrays(N, v1, v2);

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            c1[i] = static_cast<int>(std::hypot((float)(v1[i]), (float)(v2[i])));
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "2.1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_fast_pythagorean(benchmark::State &state)
{
    // https://en.wikipedia.org/wiki/Alpha_max_plus_beta_min_algorithm
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    auto alpha0 = 2 * cos(M_PI / 8) / (1 + cos(M_PI / 8));
    auto beta0 = 2 * sin(M_PI / 8) / (1 + cos(M_PI / 8));

    for (size_t i = 0; i < N; ++i)
    {
        v1[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
        v2[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
    }
    int *p1 = v1.data(), *p2 = v2.data();
    int *b1 = c1.data();

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            auto &vmax = std::max(p1[i], p2[i]); // marginally faster than pass by copy
            auto &vmin = std::min(p1[i], p2[i]);
            b1[i] = alpha0 * vmax + beta0 * vmin;
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "3 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_fast_pythagorean_2(benchmark::State &state)
{
    // https://en.wikipedia.org/wiki/Alpha_max_plus_beta_min_algorithm
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N, 0);

    auto alpha0 = 2 * cos(M_PI / 8) / (1 + cos(M_PI / 8));
    auto beta0 = 2 * sin(M_PI / 8) / (1 + cos(M_PI / 8));

    for (size_t i = 0; i < N; ++i)
    {
        v1[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
        v2[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
    }

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            auto out = std::minmax(v1[i], v2[i]);
            c1[i] = alpha0 * out.second + beta0 * out.first;
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "4 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_fast_pythagorean_3(benchmark::State &state)
{
    // https://en.wikipedia.org/wiki/Alpha_max_plus_beta_min_algorithm
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    auto alpha0 = 2 * cos(M_PI / 8) / (1 + cos(M_PI / 8));
    auto beta0 = 2 * sin(M_PI / 8) / (1 + cos(M_PI / 8));

    for (size_t i = 0; i < N; ++i)
    {
        v1[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
        v2[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
    }
    int *p1 = v1.data(), *p2 = v2.data();
    int *b1 = c1.data();

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            auto [vmin, vmax] = std::minmax(p1[i], p2[i]);
            b1[i] = alpha0 * vmax + beta0 * vmin;
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "5 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_fast_pythagorean_4(benchmark::State &state)
{
    // https://en.wikipedia.org/wiki/Alpha_max_plus_beta_min_algorithm
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N), v2(N);
    std::vector<int> c1(N);

    auto alpha0 = 2 * cos(M_PI / 8) / (1 + cos(M_PI / 8));
    auto beta0 = 2 * sin(M_PI / 8) / (1 + cos(M_PI / 8));

    for (size_t i = 0; i < N; ++i)
    {
        v1[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
        v2[i] = static_cast<double>(rand()) / RAND_MAX * 5000;
    }
    int *p1 = v1.data(), *p2 = v2.data();

    for (auto _ : state)
    {
        for (size_t i = 0; i < N; ++i)
        {
            // auto[vmax,vmin] = std::minmax(p1[i],p2[i]);
            double s[2] = {alpha0 * p1[i] + beta0 * p2[i], alpha0 * p2[i] + beta0 * p1[i]};

            c1[i] = s[p2[i] > p1[i]];
        }
        benchmark::DoNotOptimize(c1);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N * state.iterations());
    // std::cout << "6 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

BENCHMARK(BM_pythagorean)->Arg(1 << 22);
BENCHMARK(BM_pythagorean_no_cast)->Arg(1 << 22);

BENCHMARK(BM_pythagorean_hypot_float)->Arg(1 << 22);
BENCHMARK(BM_pythagorean_powsqrt)->Arg(1 << 22);

BENCHMARK(BM_fast_pythagorean)->Arg(1 << 22);
BENCHMARK(BM_fast_pythagorean_2)->Arg(1 << 22);
BENCHMARK(BM_fast_pythagorean_3)->Arg(1 << 22);
BENCHMARK(BM_fast_pythagorean_4)->Arg(1 << 22);

BENCHMARK_MAIN();