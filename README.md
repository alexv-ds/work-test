# Результаты бенчмарка

## Windows CLANG 18.1.4 | 11th Gen Intel(R) Core(TM) i5-11400 @ 2.60GHz

--benchmark-samples=1000 --benchmark-warmup-time=1000

Максимальное ускорение при avx512bw в сравнении с no_simd версией. В 22 раза быстрей (2 210 %).

```console 
benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
no_simd                                       1000             1    546.108 ms
                                        551.916 us     551.39 us    552.462 us
                                        8.67024 us    8.12535 us    9.35913 us

simd avx2                                     1000             1     49.452 ms
                                        48.6281 us    48.5447 us    48.7262 us
                                        1.45168 us    1.26799 us    1.79748 us

simd avx512bw                                 1000             1     25.388 ms
                                        24.9659 us    24.9091 us    25.0494 us
                                        1.09877 us    847.183 ns    1.84483 us

simd avx512cd                                 1000             1     25.137 ms
                                        25.2576 us    25.1563 us    25.3855 us
                                        1.83012 us    1.55451 us    2.37117 us

simd avx512dq                                 1000             1     24.923 ms
                                        25.0958 us    25.0253 us    25.1955 us
                                          1.338 us    1.05803 us    2.13839 us

simd avx512ifma                               1000             1     24.928 ms
                                        25.0479 us    24.9658 us    25.1542 us
                                        1.49547 us    1.26139 us    1.98076 us

simd avx512vbmi                               1000             1     25.305 ms
                                        25.0535 us    24.9888 us    25.1389 us
                                        1.19231 us    989.969 ns    1.76126 us

simd sse2                                     1000             1    153.309 ms
                                        152.192 us    152.055 us    152.333 us
                                        2.23404 us    2.09644 us    2.46873 us

simd sse3                                     1000             1    186.642 ms
                                        186.878 us    186.668 us    187.109 us
                                        3.55658 us    3.27418 us    3.93998 us

simd sse4.1                                   1000             1    180.046 ms
                                        179.749 us    179.637 us    179.865 us
                                        1.84315 us    1.72743 us    2.04539 us

simd sse4.2                                   1000             1    177.662 ms
                                        177.375 us    177.192 us     177.57 us
                                        3.04264 us    2.81732 us    3.44198 us

simd ssse3                                    1000             1    185.319 ms
                                         185.76 us    185.657 us    185.864 us
                                        1.66826 us    1.56373 us    1.86432 us
```


