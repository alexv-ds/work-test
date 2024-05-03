#include <cstddef>
#include <numbers>
#include <functional>
#include <iostream>
#include <cmath>
#include <limits>

/**
 * Вычисление интеграла методом Симпсона, ее можно немножко оптимизировать.
 * Вынести из цикла те вещи, которые могут быть рассчитаны только один раз + избавиться
 * от std::function, из-за которого компилятор не может ее заинлайнить, поменять на шаблонный параметр.
 *
 * Но для простоты чтения оставил так.
 *
 * @param from
 * @param to
 * @param segments
 * @param func
 * @return
 */
double integrate(double from, double to, std::size_t segments, const std::function<double(double)>& func) {
  double h = (to - from) / static_cast<double>(segments);
  double sum = 0;

  double x0 = from;
  double x1 = from + h;

  for (unsigned i = 0; i <= segments - 1; i++) {
    sum += func(x0) + 4 * func(x0 + h / 2) + func(x1);
    x0 += h;
    x1 += h;
  }

  return (h / 6) * sum;
}



int main() {
  double result = integrate(std::numeric_limits<double>::min(), std::numbers::pi_v<double>, 10000000, [](double x) -> double {
//    return std::pow(std::sin(13 * x) / std::sin(x), 12);
    return std::pow(std::sin(10 * x) / std::sin(x), 6);

  });

  result /= std::numbers::pi_v<double>;

  //707972099627 - правильное значение
  //707972265076 - моё
  std::cout << static_cast<std::size_t>(std::round(result)) << std::endl;

}