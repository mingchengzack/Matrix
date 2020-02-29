#include <chrono>
#include <iostream>
#include "matrix.h"

using namespace std::chrono;

int main() {
  Matrix<int> m1(3, 3, 2);
  Matrix<int> m2(3, 3, 2);
  m1(0, 0) = 1;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;

  (m1.transpose()).print();
  auto start = high_resolution_clock::now();
  Matrix<int> m3({{1, 2, 3}, {4, 5, 6}});
  m3.print();
  (m3 *= m2);
  m3.print();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time used: " << duration.count() << "microseconds" << std::endl;
  return 0;
}