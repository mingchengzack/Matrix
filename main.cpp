#include <chrono>
#include <iostream>
#include "matrix.h"

int main() {
  // Doing tranposition
  std::cout << "Matrix Transposition:" << std::endl;
  Matrix<int> matA({{1, 2, 3}, {4, 5, 6}});
  std::cout << "Matrix A:" << std::endl;
  matA.print();
  std::cout << std::endl;
  std::cout << "Matrix A.T:" << std::endl;
  (matA.transpose()).print();
  std::cout << std::endl;

  // Doing multiplication
  std::cout << "Matrix multiplication:" << std::endl;
  Matrix<int> matB({{1, 2, 3}, {4, 5, 6}});
  Matrix<int> matC({{1, 2}, {3, 4}, {5, 6}});
  std::cout << "Matrix B * Matric C:" << std::endl;
  matB.print();
  std::cout << "   *" << std::endl;
  matC.print();
  std::cout << "   =" << std::endl;
  (matB * matC).print();

  return 0;
}