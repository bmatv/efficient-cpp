# Some notes
There are additional flags that CMake appends by default for every object file call:

`-MD`                     Write a depfile containing user and system headers

`-MT <value>`             Specify name of main file output in depfile

`-MF <file>`              Write depfile output from -MMD, -MD, -MM, or -M to <file>

1. `clang++ -O3 -mavx2 -Wall -pedantic -MD -MT example.C.o -MF example.C.o.d -o example.C.o -c example.C`
2. `clang++ -O3 -mavx2 -Wall -pedantic -MD -MT compare.C.o -MF compare.C.o.d -o compare.C.o -c compare.C`
3. `clang++  -O3 -mavx2 -Wall -pedantic compare.C.o  example.C.o -o example`

The order of the files in linker seems to affect the performance (~30%). 
The example.C contains the main function and should be in the end.
example.C and compare.C can be compiled to .o - no difference.

`clang++ -g -O3 -mavx2 -Wall -pedantic   example.C compare.C -o example && ./example`

## `Sort time: 12979ms (25889223 comparisons)`

---


`clang++ -g -O3 -mavx2 -Wall -pedantic   compare.C example.C -o example && ./example`

## `Sort time: 9517ms (25889223 comparisons)`

---

Exactly the same behaviour with CMake:

|   Correct                                                 |       Incorrect                                         |
|:----------------------------------------------------------|:--------------------------------------------------------|
| `add_executable(efficient_programs compare.C example.C)`  | `add_executable(efficient_programs example.C compare.C)`|
| Sort time: 9517ms (25889223 comparisons)                  | Sort time: 14033ms (25889223 comparisons)               |


### Compilation flags
- [`-pedantic`](https://stackoverflow.com/questions/2855121/what-is-the-purpose-of-using-pedantic-in-the-gcc-g-compiler)  In absence of -pedantic, even when a specific standard is requested, GCC will still allow some extensions that are not acceptable in the C standard. Consider for example the program
    ```cpp
    struct test {
        int zero_size_array[0];
    };
    ```
    -**pedantic** causes the compiler to actually comply to the C standard; so now it will produce a diagnostic message, as is required by the standard:

    The C11 draft n1570 paragraph 6.7.6.2p1 says:

        In addition to optional type qualifiers and the keyword static, the [ and ] may delimit an expression or *. If they delimit an expression (which specifies the size of an array), the expression shall have an integer type. If the expression is a constant expression, it shall have a value greater than zero.[...]

    The C standard requires that the array length be greater than zero; and this paragraph is in the constraints; the standard says the following 5.1.1.3p1:

        A conforming implementation shall produce at least one diagnostic message (identified in an implementation-defined manner) if a preprocessing translation unit or translation unit contains a violation of any syntax rule or constraint, even if the behavior is also explicitly specified as undefined or implementation-defined. Diagnostic messages need not be produced in other circumstances.9)

    However, if you compile the program with `gcc -c -std=c90 pedantic_test.c`, no warning is produced.
    ```shall
    gcc -c -pedantic -std=c90 pedantic_test.c
    pedantic_test.c:2:9: warning: ISO C forbids zero-size array ‘zero_size_array’ [-Wpedantic]
    int zero_size_array[0];
    ```

## Profiling

In order to run profiling one needs to compile with -lprofiler

`clang++-11 -g -O3 -mavx2 -Wall -pedantic   compare.C example.C -lprofiler  -o efficient_compare`

The profiler lib is available after the installation of  **libgoogle-perftools-dev** 
```
$ CPUPROFILE=prof.data ./efficient_compare 
Sort time: 9771ms (25889043 comparisons)
PROFILE: interrupts/evictions/bytes = 978/293/28696
```
The profile data is collected in the file `prof.data`, as given by the `CPUPROFILE` environment variable.

`google-pprof --text ./efficient_compare prof.data` 
```bash
Using local file ./efficient_compare.
Using local file prof.data.
/usr/bin/addr2line: DWARF error: section .debug_info is larger than its filesize! (0x93ef57 vs 0x530f28)
Total: 978 samples
     961  98.3%  98.3%      961  98.3% compare
       5   0.5%  98.8%      191  19.5% std::__unguarded_linear_insert (inline)
       4   0.4%  99.2%      783  80.1% __gnu_cxx::__ops::_Iter_comp_iter::operator (inline)
       3   0.3%  99.5%      964  98.6% operator (inline)
       2   0.2%  99.7%        2   0.2% std::__introsort_loop (inline)
       1   0.1%  99.8%      186  19.0% __gnu_cxx::__ops::_Val_comp_iter::operator (inline)
       1   0.1%  99.9%        1   0.1% __munmap
       1   0.1% 100.0%      773  79.0% std::__unguarded_partition (inline)
       0   0.0% 100.0%        1   0.1% _ZNKSt14default_deleteIA_cEclIcEENSt9enable_ifIXsr14is_convertibleIPA_T_PS0_EE5valueEvE4typeEPS4_ (inline)
       0   0.0% 100.0%      978 100.0% __libc_start_main
       0   0.0% 100.0%      978 100.0% _start
       0   0.0% 100.0%      978 100.0% main
       0   0.0% 100.0%      191  19.5% std::__final_insertion_sort (inline)
       0   0.0% 100.0%      786  80.4% std::__introsort_loop
       0   0.0% 100.0%       12   1.2% std::__move_median_to_first (inline)
       0   0.0% 100.0%      977  99.9% std::__sort (inline)
       0   0.0% 100.0%      191  19.5% std::__unguarded_insertion_sort (inline)
       0   0.0% 100.0%      786  80.4% std::__unguarded_partition_pivot (inline)
       0   0.0% 100.0%        1   0.1% std::iter_swap (inline)
       0   0.0% 100.0%      977  99.9% std::sort (inline)
       0   0.0% 100.0%        1   0.1% ~unique_ptr (inline)

```

`using std::cout, std::endl;` is a c++17 feature, need to split for portability


[Here is additional docu](EXTRA.md)

[Measuring performance is here](PERFORMANCE_MEASUREMENT.md)