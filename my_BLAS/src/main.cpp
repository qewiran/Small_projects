#include "../hdr/matrix.hpp"
#include <iostream>
int main() {
  Matrix<double, 3, 3> a;
  Matrix<double, 3, 1> b;
  std::cout<<a<<'\n'<<b<<'\n';
  a.makeRandom(0);
  b.makeRandom(0);
}
