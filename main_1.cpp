#include <functional>
#include <limits>
#include <numbers>
#include <cmath>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <xsimd/xsimd.hpp>
#include <array>
#include <iostream>
#include <hwy/highway.h>
#include <hwy/contrib/math/math-inl.h>

namespace hn = hwy::HWY_NAMESPACE;


constexpr hn::ScalableTag<double> g_tag;
using VecT = hn::TFromD<decltype(g_tag)>;

static double integrate(double from, double to, int segments, const std::function<double(double)>& func) {
  double result = 0;
  double h = (to - from) / static_cast<double>(segments);

  for (int i = 0; i < segments; i++) {
    result += func(from + h / 2 + static_cast<double>(i) * h);
  }

  result *= h;
  return result;
}

template <class Func>
static double integrate2(double from, double to, int segments, const Func func) {
  double result = 0;
  double h = (to - from) / static_cast<double>(segments);

  for (int i = 0; i < segments; i++) {
    result += func(from + h / 2 + static_cast<double>(i) * h);
  }

  result *= h;
  return result;
}



static double integrate3(double from, double to, std::size_t segments, const std::function<xsimd::batch<double>(xsimd::batch<double>)> func) {
  // Увеличим количество сегментов до числа кратного batch<double>::size
  // Это слегка увеличит точность, и немного производительность, т.к. избавляет нас от
  // необходимости обрабатывать хвосты, которые не поместились в векторный регистр
  segments += xsimd::batch<double>::size - (segments % xsimd::batch<double>::size);

  const xsimd::batch<double> h = (to - from) / static_cast<double>(segments);
  // предрассчитываем данные, которые не меняются
  // from + h / 2
  const xsimd::batch<double> from_add_h_mul2 = (from + (to - from) / static_cast<double>(segments)) / 2.0;
  xsimd::batch<double> result = 0;

  for (std::size_t i = 0; i < segments; i += xsimd::batch<double>::size) {
    // подготавливаем пачку данных, не забываем про выравнивание, оно должно быть такое же, как и у
    // batch<double>
    alignas(xsimd::batch<double>) std::array<double, xsimd::batch<double>::size> arr_indexes; // NOLINT(*-pro-type-member-init)
    // компилятор раскрутит цикл, т.к. у нас размер известен во время компиляции
    // Протестировано: GCC, вместо цикла генерирует всего 5 инструкций
    //    cmpq   $0x0,0x10(%r12)
    //    vcvtusi2sd %rbx,%xmm3,%xmm0
    //    vbroadcastsd %xmm0,%ymm0
    //    vmovapd %ymm0,0x100(%rsp)
    //    vmovapd %ymm0,0x120(%rsp)
    // Даже не выгружает в оперативку, т.к. мы переиспользуем регистр.
    for (double& num : arr_indexes) {
      num = static_cast<double>(i);
    }
    result += func(from_add_h_mul2 + xsimd::load_aligned(arr_indexes.data()) / h);
  }

  result *= h;
  return xsimd::reduce_add(result);
};

static double do_magic() {
  hn::ScalableTag<double> tag;
  const double from = 0;
  const double to = std::numbers::pi_v<double>;

  auto keks = hn::Load

  return 0;
}

TEST_CASE("TESTS") {
  BENCHMARK("NO SIMD - std::function"){
    double result = integrate(0, std::numbers::pi_v<double>, 10000, [](double x) -> double {
      return std::pow(std::sin(13 * x) / std::sin(x), 12);
    });
    result /= std::numbers::pi_v<double>;
    result *= 13;
    return result;
  };

  BENCHMARK("NO SIMD - template Func"){
    double result = integrate2(0, std::numbers::pi_v<double>, 10000, [](double x) -> double {
      return std::pow(std::sin(13 * x) / std::sin(x), 12);
    });
    result /= std::numbers::pi_v<double>;
    result *= 13;
    return result;
  };

  BENCHMARK("SIMD - std::function"){
    double result = integrate3(0, std::numbers::pi_v<double>, 10000, [](xsimd::batch<double> x) -> xsimd::batch<double> {
      return xsimd::pow(xsimd::sin(13.0 * x) / xsimd::sin(x), 12);
    });
    result /= std::numbers::pi_v<double>;
    result *= 13.0;
    return result;
  };

  BENCHMARK("SIMD HWY - std::function"){
    double result = do_magic();
    result /= std::numbers::pi_v<double>;
    result *= 13.0;
    return result;
  };
}