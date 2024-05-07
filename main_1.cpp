#include <numbers>
#include <cmath>
#include <array>
#include <iostream>
#include <xsimd/xsimd.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

// Интегрирование методом прямоугольников
// Обычная версия.
template <class Func>
double integrate(const double from, const double to, const std::size_t segments, const Func func) {
  double result = 0.0;
  const double h = (to - from) / static_cast<double>(segments);
  for (std::size_t i = 0; i < segments; ++i) {
    result += func(from + h / 2.0 + static_cast<double>(i) * h);
  }
  result *= h;
  return result;
}

// Формула, которую нам надо проинтегрировать.
// Обычная версия.
inline double f_x(const double x) {
  return std::pow(std::sin(13.0 * x) / std::sin(x), 12);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

// Интегрирование методом прямоугольников
// SIMD версия.
template <class Arch, class Func>
double integrate_simd(const double from, const double to, std::size_t segments, const Func func) {
  segments += xsimd::batch<double, Arch>::size - (segments % xsimd::batch<double, Arch>::size);

  xsimd::batch<double, Arch> result = 0.0;
  const double h = (to - from) / static_cast<double>(segments);

  for (std::size_t i = 0; i < segments; i += xsimd::batch<double, Arch>::size) {
    alignas(xsimd::batch<double, Arch>) std::array<double, xsimd::batch<double, Arch>::size> indexes; // NOLINT(*-pro-type-member-init)

    for (double& num : indexes) {
      num = static_cast<double>(i);
    }

    result += func(from + h / 2.0 + xsimd::load_aligned<Arch>(indexes.data()) * h);
  }
  result *= h;
  return xsimd::reduce_add(result);
}

// Формула которую нам надо проинтегрировать.
// SIMD версия
template <class Arch>
inline xsimd::batch<double, Arch> f_x_simd(const xsimd::batch<double, Arch> x) {
  return xsimd::pow(xsimd::sin(13.0 * x) / xsimd::sin(x), 12);
}

template<class Arch>
inline double simd_bench() {
  double result = integrate_simd<Arch>(0.0, std::numbers::pi_v<double>, 10000, f_x_simd<Arch>);
  result /= std::numbers::pi_v<double>;
  result *= 13.0;
  return result;
}

#define MAKE_SIMD_BENCHMARK(Arch) \
  if constexpr(Arch::supported()) {  \
    BENCHMARK(std::format("simd {}", Arch::name())) {return simd_bench<Arch>(); }; \
  }

TEST_CASE("TESTS WITH SIMD") {
  BENCHMARK("no_simd"){
    double result = integrate(0.0, std::numbers::pi_v<double>, 10000, f_x);
    result /= std::numbers::pi_v<double>;
    result *= 13.0;
    return result;
  };
  MAKE_SIMD_BENCHMARK(xsimd::avx2)
  MAKE_SIMD_BENCHMARK(xsimd::avx512bw)
  MAKE_SIMD_BENCHMARK(xsimd::avx512cd)
  MAKE_SIMD_BENCHMARK(xsimd::avx512dq)
  MAKE_SIMD_BENCHMARK(xsimd::avx512ifma)
  MAKE_SIMD_BENCHMARK(xsimd::avx512vbmi)
  MAKE_SIMD_BENCHMARK(xsimd::sse2)
  MAKE_SIMD_BENCHMARK(xsimd::sse3)
  MAKE_SIMD_BENCHMARK(xsimd::sse4_1)
  MAKE_SIMD_BENCHMARK(xsimd::sse4_2)
  MAKE_SIMD_BENCHMARK(xsimd::ssse3)
}