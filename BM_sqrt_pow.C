#include "benchmark/benchmark.h"
#include <vector>
#include <cmath>
#include <cstdint>

void BM_sqrt_int16(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int16_t> v1(N);
    std::vector<int16_t>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::sqrt(std::abs(v1[i]));
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_sqrt_int32(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int32_t> v1(N);
    std::vector<int32_t>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::sqrt(std::abs(v1[i]));
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_sqrt_uint32(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<uint32_t> v1(N);
    std::vector<uint32_t>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::sqrt(v1[i]);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_sqrt_float(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::sqrt(std::abs(v1[i]));
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}


void BM_powsqrt_float(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = pow(std::abs(v1[i]),0.5);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}

void BM_sqrt_double(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<double> v1(N);
    std::vector<double>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // uint16_t* p1 = v1.data();
    // double* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::sqrt(std::abs(v1[i]));
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
    // std::cout << "1 " << c1[0] << ' ' << v1[0] <<' ' <<v2[0] << '\n';
}



void BM_square_mul_int(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // int* p1 = v1.data();
    // int* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = v1[i]*v1[i];
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_mul_float(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = v1[i]*v1[i];
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_pow_int(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<int> v1(N);
    std::vector<int>c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }
    // int* p1 = v1.data();
    // int* b1 = c1.data();

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::pow(v1[i],2) + std::pow(v1[i],2);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_pow_float(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float> c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::pow(v1[i],2) + std::pow(v1[i],2);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_pow_float2(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float> c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::pow(v1[i],2.0F) + std::pow(v1[i],2.0F);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_pow_float3(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<float> v1(N);
    std::vector<float> c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<double>(rand())/ RAND_MAX * 5000;
    }

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = powf(v1[i],2.0F) + powf(v1[i],2.0F);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

void BM_square_pow_double2(benchmark::State& state){
    srand(1);
    unsigned int N = state.range(0);
    std::vector<long double> v1(N);
    std::vector<long double> c1(N);

    for(size_t i=0;i<N;++i){
        v1[i] = static_cast<long double>(rand())/ RAND_MAX * 5000;
    }

    for (auto _:state){
        for (size_t i =0;i<N;++i){
            c1[i] = std::pow(v1[i],2.0L) + std::pow(v1[i],2.0L);
        }
    benchmark::DoNotOptimize(c1);
    benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}


BENCHMARK(BM_sqrt_int16)->Arg(1<<22); //slow
BENCHMARK(BM_sqrt_int32)->Arg(1<<22); //slow
BENCHMARK(BM_sqrt_uint32)->Arg(1<<22); //slow

BENCHMARK(BM_sqrt_float)->Arg(1<<22); //fast
BENCHMARK(BM_powsqrt_float)->Arg(1<<22); //order of magnitude slower than int



BENCHMARK(BM_sqrt_double)->Arg(1<<22);//half speed of float
BENCHMARK(BM_square_mul_int)->Arg(1<<22);
BENCHMARK(BM_square_mul_float)->Arg(1<<22);


BENCHMARK(BM_square_pow_int)->Arg(1<<22);
BENCHMARK(BM_square_pow_float)->Arg(1<<22);
BENCHMARK(BM_square_pow_float2)->Arg(1<<22);
BENCHMARK(BM_square_pow_float3)->Arg(1<<22);

BENCHMARK(BM_square_pow_double2)->Arg(1<<22);

BENCHMARK_MAIN();