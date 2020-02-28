#include <chrono>
#include <iostream>
#include "matrix.h"

using namespace std::chrono;

int main() {
  Matrix<int> m1(1000, 1000, 2);
  Matrix<int> m2(1000, 1000, 2);
  m1(0, 0) = 1;
  m1(0, 2) = 3;
  m1(1, 0) = 4;
  m1(1, 1) = 5;
  m1(1, 2) = 6;
  m1(2, 0) = 7;
  m1(2, 1) = 8;
  m1(2, 2) = 9;

  //   m1.print();
  auto start = high_resolution_clock::now();

  (m1 * m2);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time used: " << duration.count() << "microseconds" << std::endl;
  return 0;
}