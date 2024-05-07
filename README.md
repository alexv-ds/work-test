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

## Linux CLANG 18.3.1 | 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz

```console

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
no_simd                                        100             1    41.0916 ms 
                                        411.816 us    405.316 us    420.015 us 
                                        37.3514 us    30.8399 us     45.519 us 
                                                                               
simd avx2                                      100             1     6.8068 ms 
                                        66.0801 us     65.945 us    66.5972 us 
                                        1.20409 us    250.233 ns     2.8091 us 
                                                                               
simd avx512bw                                  100             1     2.5863 ms 
                                        25.7272 us    25.5405 us    26.2626 us 
                                        1.47449 us    594.266 ns    3.14574 us 
                                                                               
simd avx512cd                                  100             1     2.5871 ms 
                                        25.8632 us    25.6304 us    26.5548 us 
                                        1.86994 us    776.661 ns    4.06981 us 
                                                                               
simd avx512dq                                  100             1      2.602 ms 
                                        25.6578 us    25.4808 us    26.3179 us 
                                        1.52879 us    371.493 ns     3.5177 us 
                                                                               
simd avx512ifma                                100             1     2.5919 ms 
                                           25.6 us    25.3345 us    26.8743 us 
                                        2.55152 us    112.484 ns    6.08066 us 
                                                                               
simd avx512vbmi                                100             1     2.6067 ms 
                                        25.8474 us    25.4839 us    27.5295 us 
                                        3.41367 us    337.431 ns    8.10347 us 
                                                                               
simd sse2                                      100             1    14.6803 ms 
                                         146.43 us    146.029 us    147.153 us 
                                        2.66284 us    1.66723 us    3.99783 us 
                                                                               
simd sse3                                      100             1    14.7552 ms 
                                         147.26 us      146.6 us    148.223 us 
                                        4.02705 us     3.0134 us    5.16377 us 
                                                                               
simd sse4.1                                    100             1    13.5721 ms 
                                        135.507 us     135.28 us    136.039 us 
                                        1.66253 us    860.149 ns    3.14038 us 
                                                                               
simd sse4.2                                    100             1    13.5934 ms 
                                        135.371 us    135.237 us     135.66 us 
                                        956.378 ns    423.719 ns    1.62531 us 
                                                                               
simd ssse3                                     100             1    14.6582 ms 
                                        146.074 us    145.821 us    146.505 us 
                                        1.64948 us    1.08717 us    2.34864 us                                                                     
```

## Linux GCC 14.0.1 20240412 | 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz

```console
benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
no_simd                                        100             1    38.6475 ms 
                                        386.867 us    385.443 us    388.961 us 
                                        8.70461 us    6.57905 us    11.3976 us 
                                                                               
simd avx2                                      100             1     4.2784 ms 
                                        42.4641 us    42.2125 us    43.2382 us 
                                        2.03831 us    745.724 ns    4.45708 us 
                                                                               
simd avx512bw                                  100             1     4.5227 ms 
                                        45.2589 us    45.0817 us    45.6798 us 
                                        1.31842 us    663.745 ns    2.62795 us 
                                                                               
simd avx512cd                                  100             1     4.5417 ms 
                                        50.5688 us    50.2871 us    51.0636 us 
                                        1.85286 us     1.1961 us     2.6493 us 
                                                                               
simd avx512dq                                  100             1     4.5201 ms 
                                         45.174 us    44.9239 us    46.3438 us 
                                        2.36332 us    199.281 ns    5.61698 us 
                                                                               
simd avx512ifma                                100             1     4.5248 ms 
                                         47.608 us     47.216 us     48.154 us 
                                        2.33295 us     1.7407 us    3.95483 us 
                                                                               
simd avx512vbmi                                100             1     4.5113 ms 
                                        45.1658 us    44.9514 us     46.066 us 
                                        1.91543 us    286.067 ns    4.47803 us 
                                                                               
simd sse2                                      100             1     9.3804 ms 
                                         93.229 us    93.1264 us    93.4092 us 
                                        674.921 ns    433.116 ns    1.07643 us 
                                                                               
simd sse3                                      100             1      9.546 ms 
                                        93.7714 us     93.403 us    94.4139 us 
                                         2.4205 us    1.61855 us    3.68893 us 
                                                                               
simd sse4.1                                    100             1     8.9907 ms 
                                        88.9277 us    88.8662 us    89.0116 us 
                                        363.866 ns    280.211 ns    452.316 ns 
                                                                               
simd sse4.2                                    100             1     8.9895 ms 
                                        89.7939 us    89.3258 us    90.5137 us 
                                        2.92355 us    2.10718 us    3.87152 us 
                                                                               
simd ssse3                                     100             1     9.3591 ms 
                                        93.6291 us    93.3707 us    94.1014 us 
                                        1.72803 us    1.07624 us     2.5857 us 
```