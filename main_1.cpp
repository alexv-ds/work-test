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

TEST_CASE("TESTS WITHOUT SIMD") {
  BENCHMARK("no_simd"){
    double result = integrate(0.0, std::numbers::pi_v<double>, 10000, f_x);
    result /= std::numbers::pi_v<double>;
    result *= 13.0;
    //std::cout << "NO SIMD: " <<  (std::size_t)std::round(result) << std::endl;
    return result;
  };
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

// Интегрирование методом прямоугольников
// SIMD версия.
template <class Func>
double integrate_simd(const double from, const double to, std::size_t segments, const Func func) {
  segments += xsimd::batch<double>::size - (segments % xsimd::batch<double>::size);

  xsimd::batch<double> result = 0.0;
  const double h = (to - from) / static_cast<double>(segments);

  for (std::size_t i = 0; i < segments; i += xsimd::batch<double>::size) {
    alignas(xsimd::batch<double>) std::array<double, xsimd::batch<double>::size> indexes; // NOLINT(*-pro-type-member-init)

    for (double& num : indexes) {
      num = static_cast<double>(i);
    }

    result += func(from + h / 2.0 + xsimd::load_aligned(indexes.data()) * h);
  }
  result *= h;
  return xsimd::reduce_add(result);
}

// Формула которую нам надо проинтегрировать.
// SIMD версия
inline xsimd::batch<double> f_x_simd(const xsimd::batch<double> x) {
  return xsimd::pow(xsimd::sin(13.0 * x) / xsimd::sin(x), 12);
}

TEST_CASE("TESTS WITH SIMD") {
  BENCHMARK("simd"){
    double result = integrate_simd(0.0, std::numbers::pi_v<double>, 10000, f_x_simd);
    result /= std::numbers::pi_v<double>;
    result *= 13.0;
    //std::cout << "SIMD: " <<  (std::size_t)std::round(result) << std::endl;
    return result;
  };
}