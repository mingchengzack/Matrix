#include <cassert>
#include <iostream>
#include <vector>
#include "matrix.h"

// Some unit tests to test the functionality of Matrix::tranpose
void test_transpoe() {
  std::cout << "Testing Matrix::transpose()..." << std::endl;

  // case 1
  Matrix<int> mat1({{1, 2}});
  Matrix<int> mat1_T({{1}, {2}});
  assert(mat1.transpose() == mat1_T);

  Matrix<double> mat1_d({{1.0, 2.0}});
  Matrix<double> mat1_d_T({{1.0}, {2.0}});
  assert(mat1_d.transpose() == mat1_d_T);

  // case 2
  Matrix<int> mat2({{1, 2}, {3, 4}, {5, 6}});
  Matrix<int> mat2_T({{1, 3, 5}, {2, 4, 6}});
  assert(mat2.transpose() == mat2_T);

  Matrix<double> mat2_d({{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}});
  Matrix<double> mat2_d_T({{1.0, 3.0, 5.0}, {2.0, 4.0, 6.0}});
  assert(mat2_d.transpose() == mat2_d_T);

  // case 3
  std::vector<std::vector<int>> vec3;
  for (int i = 0; i < 100; i++) {
    vec3.push_back(std::vector<int>());
    for (int j = 0; j < 200; j++) {
      vec3[i].push_back(j * i);
    }
  }

  std::vector<std::vector<int>> vec3_T;
  for (int i = 0; i < 200; i++) {
    vec3_T.push_back(std::vector<int>());
    for (int j = 0; j < 100; j++) {
      vec3_T[i].push_back(j * i);
    }
  }

  Matrix<int> mat3(vec3);
  Matrix<int> mat3_T(vec3_T);
  assert(mat3.transpose() == mat3_T);

  std::cout << "Matrix::tranpose()...OK!\n" << std::endl;
}

// Some unit tests to test th funtionality of Matrix::operator*
void test_multiplication() {
  std::cout << "Testing Matrix::operator*()..." << std::endl;

  // case 1
  Matrix<int> mat1A({{1, 2}});
  Matrix<int> mat1B({{1}, {2}});
  Matrix<int> mat1C({{5}});
  assert(mat1A * mat1B == mat1C);

  Matrix<double> mat1A_d({{1.0, 2.0}});
  Matrix<double> mat1B_d({{1.0}, {2.0}});
  Matrix<double> mat1C_d({{5.0}});
  assert(mat1A_d * mat1B_d == mat1C_d);

  // case 2
  Matrix<int> mat2A({{12, 2, 3}, {34, 4, 7}, {55, 6, 10}});
  Matrix<int> mat2B(
      {{3, 10, 12, 15, 26}, {1, 2, 8, 10, 12}, {32, 35, 3, 5, 9}});
  Matrix<int> mat2C({{134, 229, 169, 215, 363},
                     {330, 593, 461, 585, 995},
                     {491, 912, 738, 935, 1592}});
  assert(mat2A * mat2B == mat2C);

  Matrix<double> mat2A_d(
      {{12.2, 2.2, 3.3}, {34.2, 4.2, 7.2}, {55.1, 6.2, 10.5}});
  Matrix<double> mat2B_d({{3.6, 10.6, 12.2, 15.6, 26.1},
                          {1.1, 2.2, 8.9, 10.3, 12.4},
                          {32.5, 35.5, 3.6, 5.9, 9.0}});
  Matrix<double> mat2C_d({{153.59, 251.31, 180.3, 232.45, 375.4},
                          {361.74, 627.36, 480.54, 619.26, 1009.5},
                          {546.43, 970.45, 765.2, 985.37, 1609.49}});
  assert(mat2A_d * mat2B_d == mat2C_d);

  std::cout << "Matrix::operator*()...OK!\n" << std::endl;
}

int main() {
  test_transpoe();
  test_multiplication();
  return 0;
}