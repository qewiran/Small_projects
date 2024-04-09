// #include "../hdr/iter_method.hpp"
// #include "../hdr/LUdecomp.hpp"
#include "../hdr/matrix.hpp"
// #include "../hdr/QRdecomp.hpp"
#include "../hdr/power_method.hpp"
#include <chrono>
#include <thread>
int main() {
  using namespace std::chrono_literals;
  Matrix<double, 3, 3> a{};
  Matrix<double, 3, 1> b{};
  a.makeRandom(0);
  std::this_thread::sleep_for(1000ms);
  b.makeRandom(0);
  auto result = directMethod(a, b);
}
