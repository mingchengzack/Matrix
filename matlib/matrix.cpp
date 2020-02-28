#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
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
void Matrix<T>::transpose_(Matrix<T>& mat_t, int count) const {
  unsigned si = count * mat_t.rows / Matrix::num_threads;
  unsigned ei = (count + 1) * mat_t.rows / Matrix::num_threads;
  for (unsigned i = si; i < ei; i++) {
    for (unsigned j = 0; j < mat_t.cols; j++) mat_t.mat[i][j] = mat[j][i];
  }
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
  Matrix<T> mat_t(cols, rows, mat[0][0]);

  // Create threads to perform transposition
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < Matrix::num_threads; i++) {
    threads.push_back(
        std::thread(&Matrix<T>::transpose_, this, std::ref(mat_t), i));
  }

  // Wait for each thread to finish computation
  for (unsigned i = 0; i < threads.size(); i++) threads[i].join();

  return mat_t;
}

// Multiplication of two matrices
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const {
  Matrix result(rows, cols, 0.0);
  return result;
}

// Multiplication of two matrices
template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  Matrix result(rows, cols, 0.0);
  return result;
}

#endif