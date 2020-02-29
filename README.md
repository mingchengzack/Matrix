# Matrix Library for Multiplcation and Transposition

## Instructions

### How to compile
I had written a Makefile for compilation. Type make and a program called main.out,
which showcases some simple cases for matrix transposition and multiplication.

### Usage
The implementation of the library is is in matlib/matrix.h and matlib/matrix.cpp.
For using the library, simply include "matrix.h". I implemented a class called
Matrix and the methods for transposition and multiplcation.

To declare a Matrix object, we can declare `Matrix<T> mat(M, N, val)`, where it
declares a MxN matrix where each entry is val, and T is the numerical type such
as int and double. We can also declare a matrix using two dimensional
vector, `Matrix<T> mat(vector<vector<T>>)`. For simplicity, I assume the input
for both declaration are valid.

To perform get the transpose of a matrix, we use Matrix<T>.transpose().
To perform multiplcation between matrices, we can either `matC = matA * matB` or
`matA *= matB`.

## Implementation
I used two dimensional vector to represent the matrix. I use multi-threading to implement the transpose and multiplication method.

### Data Structure
For the Matrix class, I have three 3 members.
* `unsigned rows`: the number of rows for the matrix
* `unsigned cols`: the number of cols for the matrix
* `vector<vector<T>> mat`: the actual matrix representation
* `static unsigned num_threads`: the default number of threads to use (2)

### Transposition
I use multiple threads to compute the tranpose of a matrix. If there are `n` rows
for the original matrix and `t` threads (`Matrix::num_threads = t`), I will have one thread to compute the `n / t` rows for the tranpose of the matrix using
`mat_tranpose[i][j] = mat[j][j]`.

### Multiplication
Before doing a multiplcation, I check if two matrice have the matching dimension and if
not, I would stop the program. (using assert)

I use multiple threads to compute the multiplcation between two matrice. For a
matrix A with `MxN` dimension and matrix B with `NxP` dimension, which means the
result matrix will be `MxP` dimension. If I have `t` threads (`Matrix::num_threads = t`),
then I will have one thread to compute the `M / t` rows of the result matrix
using `res[i][j] = matA[i][k] * mat[k][j]`.

### Notes about number of threads
For both transposition and multiplcation, I have one thread to handle the computation
of at least two rows, so if there are `t` threads and `n` rows, where `t > rows / 2`,
I would set `t = rows / 2`.

