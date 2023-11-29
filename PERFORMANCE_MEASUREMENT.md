
# The _perf_ profiler
compilation does not require any special options or tools

## perf installation:
- Debian: `sudo apt install linux-perf`

- Ubuntu: `sudo apt-get install linux-tools` or:
  
      apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`

`clang++ -g -O3 -mavx2 -Wall -pedantic compare.C example.C -o efficient_compare`



`perf stat ./efficient_compare`

```
sudo perf stat ./efficient_compare 
Sort time: 7580ms (25889223 comparisons)

 Performance counter stats for './efficient_compare':

          7,595.43 msec task-clock                #    1.000 CPUs utilized          
                17      context-switches          #    2.238 /sec                   
                 0      cpu-migrations            #    0.000 /sec                   
             6,270      page-faults               #  825.497 /sec                   
    31,607,429,314      cycles                    #    4.161 GHz                    
   133,228,566,107      instructions              #    4.22  insn per cycle         
    26,667,659,816      branches                  #    3.511 G/sec                  
        34,862,797      branch-misses             #    0.13% of all branches        

       7.595992013 seconds time elapsed

       7.583859000 seconds user
       0.011999000 seconds sys
```
Or with custom set of metrics:
```
perf stat -e cycles,instructions,branches,branch-misses,cache-references,cache-misses ./efficient_compare 
Sort time: 7785ms (25889223 comparisons)

 Performance counter stats for './efficient_compare':

    32,433,460,441      cycles                                                        (66.68%)
   133,133,277,027      instructions              #    4.10  insn per cycle           (83.34%)
    26,672,679,949      branches                                                      (83.34%)
        34,862,284      branch-misses             #    0.13% of all branches          (83.34%)
       992,029,284      cache-references                                              (83.34%)
       274,049,476      cache-misses              #   27.625 % of all cache refs      (83.30%)

       7.804342416 seconds time elapsed

       7.792009000 seconds user
       0.012000000 seconds sys
```

# The Google performance profiler [-lprofiler flag]

`clang++ -g -O3 -mavx2 -Wall -pedantic compare.C example.C -lprofiler -o efficient_compare`

`CPUPROFILE=prof.data CPUPROFILE_FREQUENCY=1000 ./efficient_compare
Sort time: 7440ms (25889043 comparisons)
PROFILE: interrupts/evictions/bytes = 1864/505/46824`


# LLVM MCA

with only single multiplication:
```cpp
    for (auto _ : state) {
        unsigned long a1 = 0;
        for (size_t i = 0; i < N; ++i) {
            MCA_START;
            a1 += p1[i] * p2[i];
            MCA_END;
        }
```

and throwing the compiled output to llvm-mca-14 (11 was not available) we get:

```
clang++ 01_superscalar.C -g -O3 -mavx2 --std=c++17 -mllvm -x86-asm-syntax=intel -S -o - | llvm-mca-14 -mcpu=btver2 -timeline
```

```
<stdin>:7:2: warning: inconsistent use of MD5 checksums
        .file   3 "/usr/bin/../lib/gcc/x86_64-linux-gnu/12/../../../../include/c++/12/bits" "atomic_base.h"
        ^

[0] Code Region

Iterations:        100
Instructions:      300
Total Cycles:      412
Total uOps:        300

Dispatch Width:    2
uOps Per Cycle:    0.73
IPC:               0.73
Block RThroughput: 4.0


Instruction Info:
[1]: #uOps
[2]: Latency
[3]: RThroughput
[4]: MayLoad
[5]: MayStore
[6]: HasSideEffects (U)

[1]    [2]    [3]    [4]    [5]    [6]    Instructions:
 1      3     1.00    *                   mov	rcx, qword ptr [r13 + 8*rax]
 1      9     4.00    *                   imul	rcx, qword ptr [r14 + 8*rax]
 1      6     1.00    *      *            add	qword ptr [rsp], rcx


Resources:
[0]   - JALU0
[1]   - JALU1
[2]   - JDiv
[3]   - JFPA
[4]   - JFPM
[5]   - JFPU0
[6]   - JFPU1
[7]   - JLAGU
[8]   - JMul
[9]   - JSAGU
[10]  - JSTC
[11]  - JVALU0
[12]  - JVALU1
[13]  - JVIMUL


Resource pressure per iteration:
[0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   
1.00   1.00    -      -      -      -      -     3.00   4.00   1.00    -      -      -      -     

Resource pressure by instruction:
[0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
 -      -      -      -      -      -      -     1.00    -      -      -      -      -      -     mov	rcx, qword ptr [r13 + 8*rax]
 -     1.00    -      -      -      -      -     1.00   4.00    -      -      -      -      -     imul	rcx, qword ptr [r14 + 8*rax]
1.00    -      -      -      -      -      -     1.00    -     1.00    -      -      -      -     add	qword ptr [rsp], rcx


Timeline view:
                    0123456789          0123456789          01 <= THESE ARE CYCLES!!! 52 in total
Index     0123456789          0123456789          0123456789  

[0,0]     DeeeER    .    .    .    .    .    .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[0,1]     D=eeeeeeeeeER  .    .    .    .    .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[0,2]     .D======eeeeeeER    .    .    .    .    .    .    ..   add	qword ptr [rsp], rcx
[1,0]     .D=eeeE--------R    .    .    .    .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[1,1]     . D===eeeeeeeeeER   .    .    .    .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[1,2]     . D=========eeeeeeER.    .    .    .    .    .    ..   add	qword ptr [rsp], rcx
[2,0]     .  DeeeE-----------R.    .    .    .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[2,1]     .  D======eeeeeeeeeER    .    .    .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[2,2]     .   D===========eeeeeeER .    .    .    .    .    ..   add	qword ptr [rsp], rcx
[3,0]     .   DeeeE--------------R .    .    .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[3,1]     .    D========eeeeeeeeeER.    .    .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[3,2]     .    D==============eeeeeeER  .    .    .    .    ..   add	qword ptr [rsp], rcx
[4,0]     .    .DeeeE----------------R  .    .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[4,1]     .    .D===========eeeeeeeeeER .    .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[4,2]     .    . D================eeeeeeER   .    .    .    ..   add	qword ptr [rsp], rcx
[5,0]     .    . D=eeeE------------------R   .    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[5,1]     .    .  D=============eeeeeeeeeER  .    .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[5,2]     .    .  D===================eeeeeeER    .    .    ..   add	qword ptr [rsp], rcx
[6,0]     .    .   D=eeeE--------------------R    .    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[6,1]     .    .   D================eeeeeeeeeER   .    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[6,2]     .    .    D=====================eeeeeeER.    .    ..   add	qword ptr [rsp], rcx
[7,0]     .    .    D==eeeE----------------------R.    .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[7,1]     .    .    .D==================eeeeeeeeeER    .    ..   imul	rcx, qword ptr [r14 + 8*rax]
[7,2]     .    .    . D=======================eeeeeeER .    ..   add	qword ptr [rsp], rcx
[8,0]     .    .    .  D=eeeE------------------------R .    ..   mov	rcx, qword ptr [r13 + 8*rax]
[8,1]     .    .    .   D===================eeeeeeeeeER.    ..   imul	rcx, qword ptr [r14 + 8*rax]
[8,2]     .    .    .    D========================eeeeeeER  ..   add	qword ptr [rsp], rcx
[9,0]     .    .    .    .DeeeE--------------------------R  ..   mov	rcx, qword ptr [r13 + 8*rax]
[9,1]     .    .    .    . D====================eeeeeeeeeER ..   imul	rcx, qword ptr [r14 + 8*rax]
[9,2]     .    .    .    .  D=========================eeeeeeER   add	qword ptr [rsp], rcx


Average Wait times (based on the timeline view):
[0]: Executions
[1]: Average time spent waiting in a scheduler's queue
[2]: Average time spent waiting in a scheduler's queue while ready
[3]: Average time elapsed from WB until retire stage

      [0]    [1]    [2]    [3]
0.     10    1.6    1.6    15.9      mov	rcx, qword ptr [r13 + 8*rax]
1.     10    12.5   11.5   0.0       imul	rcx, qword ptr [r14 + 8*rax]
2.     10    17.8   0.0    0.0       add	qword ptr [rsp], rcx
       10    10.6   4.4    5.3       <total>
```

Addition and multiplication gives us a 53-cycle timeline (+1 cycle for twice as many compute):
```
Timeline view:
                    0123456789          0123456789          012 <= 53 cycles here
Index     0123456789          0123456789          0123456789   
```

7 different operations in the loop (excluding division) as:
```cpp
a1 += p1[i] + p2[i];
a2 += p1[i] * p2[i];
a3 += p2[i] - p1[i];
a4 += p1[i] << 2;
a5 += p1[i] + 1;
a6 += p2[i] * p2[i];
a7 += p1[i] - p2[i];
```

produces 80 cycles timeline:
```
Timeline view:
0123456789          0123456789          0123456789          0123456789
Index     0123456789          0123456789          0123456789          0123456789

```


# Dependent pipelining

```cpp
for (size_t i = 0; i < N; ++i) {
    MCA_START;
    s[i] = (p1[i] + p2[i]);
    d[i] = (p1[i] - p2[i]);
    a1[i] += s[i]*d[i];
    MCA_END;
}
```

```
Benchmark                              Time             CPU   Iterations UserCounters...
----------------------------------------------------------------------------------------
BM_pp_add_sub_mul/4194304        4567842 ns      4567597 ns          147 items_per_second=918.274M/s
BM_pp_add_sub_mul_dep/4194304   18304762 ns     18304074 ns           38 items_per_second=229.146M/s
```

That dependent loop could be converted to an efficient pipelined version if last dependent multiplication could use products of s and d from the previous step.