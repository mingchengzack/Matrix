#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
class Matrix {
 private:
  unsigned rows;
  unsigned cols;
  std::vector<std::vector<T>> mat;
  static unsigned num_threads;

  void transpose_(Matrix<T>& mat_t, unsigned num_threads,
                  unsigned count) const;  // Using threads to do transposition

  void multiply(const Matrix<T>& rhs, Matrix<T>& res, unsigned num_threads,
                unsigned count) const;  // Using threads to do multiplication

 public:
  explicit Matrix(unsigned rows_, unsigned cols_,
                  const T& val);  // Constructor for matrix with same values
  explicit Matrix(
      const std::vector<std::vector<T>>& vec);  // Constructor for vector
  Matrix(const Matrix<T>& rhs);                 // Copy constructor
  ~Matrix();                                    // Destructor

  T& operator()(const unsigned& i,
                const unsigned& j);  // modify matrix elements
  const T& operator()(const unsigned& i,
                      const unsigned& j) const;  // access matrix elements

  unsigned get_rows() const;    // Get nubmer of rows of the matrix
  unsigned get_cols() const;    // Get number of columns of the matrix
  void print() const;           // Print out the matrix
  Matrix<T> transpose() const;  // Perform transposition
  Matrix<T> operator*(const Matrix<T>& rhs) const;  // Multiplication
  Matrix<T>& operator*=(const Matrix<T>& rhs);      // Multiplication

  static unsigned get_threads() { return num_threads; }
  static void change_threads(unsigned num_t) {
    num_threads = num_t;
  }  // Change the default number of threads used
};

template <typename T>
unsigned Matrix<T>::num_threads = 2;

#include "matrix.cpp"

#endif