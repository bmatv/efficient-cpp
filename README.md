# Some notes
CLion calls `clang++` with `-MT/-MD/-MF` flags - a separate dependency file is created. 
This seems to the reason for slowness (~30%). Effectively two additional files are created with the flags: `compare.C.o.d` and `examples.C.o.d`

`-MD`                     Write a depfile containing user and system headers

`-MT <value>`             Specify name of main file output in depfile

`-MF <file>`              Write depfile output from -MMD, -MD, -MM, or -M to <file>

1. `clang++ -O3 -mavx2 -Wall -pedantic -MD -MT example.C.o -MF example.C.o.d -o example.C.o -c example.C`
2. `clang++ -O3 -mavx2 -Wall -pedantic -MD -MT compare.C.o -MF compare.C.o.d -o compare.C.o -c compare.C`
3. `clang++  -O3 -mavx2 -Wall -pedantic   example.C.o compare.C.o  -o efficient_compare`

```
-rw-rw-r-- 1 bogdan bogdan 1000 Nov  9 13:36 compare.C.o
-rw-rw-r-- 1 bogdan bogdan   23 Nov  9 13:36 compare.C.o.d
-rwxrwxr-x 1 bogdan bogdan  18K Nov  9 13:36 efficient_compare
-rw-rw-r-- 1 bogdan bogdan 7.0K Nov  9 13:33 example.C.o
-rw-rw-r-- 1 bogdan bogdan  17K Nov  9 13:33 example.C.o.d
```

### `Sort time: 13962ms (25889223 comparisons)`

---


`clang++ -g -O3 -mavx2 -Wall -pedantic compare.C example.C -o example && ./example`

### `Sort time: 9905ms (25889223 comparisons)`

---



`/usr/bin/clang++  -O3 -mavx2 -Wall -pedantic -g   CMakeFiles/efficient_programs.dir/example.C.o CMakeFiles/efficient_programs.dir/compare.C.o  -o efficient_programs` 
is slower than 
`clang++ -g -O3 -mavx2 -Wall -pedantic CMakeFiles/efficient_programs.dir/compare.C.o CMakeFiles/efficient_programs.dir/example.C.o -o example`

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
