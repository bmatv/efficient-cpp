# Some optimized-out examples

```cpp
    constexpr double X = 1e7;
    double s1 = 0, s2 = 0;
    auto f = std::async(std::launch::async,
                        [&]{ for (double x = 0; x < X; x += 0.1) s1 += sin(x);
                            });

    for (double x = 0; x < X; x += 0.1) s2 += sin(x);
    f.wait();
```
The `s1` or `s2` variable can get optimized out and thread time will be very low no matter the `X`:

`Real time: 1.09939s, CPU time: 1.20366s, Thread time: 0.104457s`

 Hence `cout << s1 << endl << s2 << endl;` statement is required:

`Real time: 3.20667s, CPU time: 5.76689s, Thread time: 3.20641s`

Now, the thread time is close to real time while CPU time is almost double (we were running two threads!) which makes perfect sense. 