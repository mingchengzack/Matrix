#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <thread>

// Constructor using default values for matrix
template <typename T>
Matrix<T>::Matrix(unsigned rows_, unsigned cols_, const T& val)
    : rows(rows_), cols(cols_) {
  mat.resize(rows_);
  for (unsigned i = 0; i < mat.size(); i++) mat[i].resize(cols_, val);
}

// Constructor for vector
template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec) {
  rows = vec.size();
  cols = vec[0].size();
  mat = vec;
}

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
  rows = rhs.rows;
  cols = rhs.cols;
  mat = rhs.mat;
}

// Destructor
template <typename T>
Matrix<T>::~Matrix() {}

// Equal function for double or float
template <typename T>
bool equals(T a, T b, double epsilon = 0.001) {
  return std::abs(a - b) < epsilon;
}

// Comparing if two matrices are equal
template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& rhs) const {
  if (this == &rhs) return true;

  if (rows != rhs.rows || cols != rhs.cols) return false;

  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      if (!equals(mat[i][j], rhs.mat[i][j])) {
        return false;
      }
    }
  }

  return true;
}

// Modify matrix elements
template <typename T>
T& Matrix<T>::operator()(const unsigned& i, const unsigned& j) {
  return mat[i][j];
}

// Access matrix elements
template <typename T>
const T& Matrix<T>::operator()(const unsigned& i, const unsigned& j) const {
  return mat[i][j];
}

// Get nubmer of rows of the matrix
template <typename T>
unsigned Matrix<T>::get_rows() const {
  return rows;
}

// Get nubmer of column of the matrix
template <typename T>
unsigned Matrix<T>::get_cols() const {
  return cols;
}

// Print out the matrix
template <typename T>
void Matrix<T>::print() const {
  for (unsigned i = 0; i < rows; i++) {
    if (i == 0)
      std::cout << "[";
    else
      std::cout << " ";
    for (unsigned j = 0; j < cols; j++) {
      std::cout << mat[i][j];
      if (j != cols - 1) std::cout << " ";
    }
    if (i == rows - 1) std::cout << "]";
    std::cout << std::endl;
  }
}

// Perform transposition
template <typename T>
void Matrix<T>::transpose_(Matrix<T>& mat_t, unsigned num_threads,
                           unsigned count) const {
  unsigned si = count * mat_t.rows / num_threads;
  unsigned ei = (count + 1) * mat_t.rows / num_threads;
  for (unsigned i = si; i < ei; i++) {
    for (unsigned j = 0; j < mat_t.cols; j++) mat_t.mat[i][j] = mat[j][i];
  }
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
  Matrix<T> mat_t(cols, rows, mat[0][0]);

  // Create threads to perform transposition
  std::vector<std::thread> threads;
  unsigned num_threads = Matrix<T>::num_threads;
  if (num_threads > rows / 2) num_threads = rows / 2 == 0 ? 1 : rows / 2;
  if (num_threads > cols / 2) num_threads = cols / 2 == 0 ? 1 : cols / 2;
  for (unsigned i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(&Matrix<T>::transpose_, this, std::ref(mat_t),
                                  num_threads, i));
  }

  // Wait for each thread to finish computation
  for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

  return mat_t;
}

// Perform multiplication of two matrices
template <typename T>
void Matrix<T>::multiply(const Matrix<T>& rhs, Matrix<T>& res,
                         unsigned num_threads, unsigned count) const {
  unsigned si = count * res.rows / num_threads;
  unsigned ei = (count + 1) * res.rows / num_threads;
  for (unsigned i = si; i < ei; i++) {
    for (unsigned j = 0; j < res.cols; j++) {
      for (int k = 0; k < cols; k++) res.mat[i][j] += mat[i][k] * rhs.mat[k][j];
    }
  }
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const {
  Matrix<T> res(rows, rhs.cols, 0.0);

  // Check valid matrix dimension for multiplcation
  assert(cols == rhs.rows);

  // Create threads to perform multiplication
  std::vector<std::thread> threads;
  unsigned num_threads = Matrix<T>::num_threads;
  if (num_threads > rows / 2) num_threads = rows / 2 == 0 ? 1 : rows / 2;
  for (unsigned i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(&Matrix<T>::multiply, this, std::ref(rhs),
                                  std::ref(res), num_threads, i));
  }

  // Wait for each thread to finish computation
  for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

  return res;
}

// Multiplication of two matrices
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  *this = (*this) * rhs;
  return *this;
}

#endif