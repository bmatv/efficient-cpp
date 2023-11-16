
# The _perf_ profiler
compilation does not require any special options or tools

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


