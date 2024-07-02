#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

template <typename T> class Matrix {
public:
  int nRows, nCols;
  T *matrixData;

  Matrix(int rows, int cols);
  ~Matrix(void);

  void fillMatrix(double mean = 0.0, double std = 1.0);
  void dumpMatrix(const std::string &filePath);
  void loadMatrix(const std::string &filePath);
  void printMatrix(void);

  Matrix operator-(Matrix &B);
};

template <typename T> double frobeniusNorm(Matrix<T> &matrix);

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : nRows(rows), nCols(cols) {
  matrixData = new T[rows * cols];
}

template <typename T> Matrix<T>::~Matrix() { delete[] matrixData; }

template <typename T> void Matrix<T>::fillMatrix(double mean, double std) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<T> dist(mean, std);

  for (int i = 0; i < nRows * nCols; ++i) {
    matrixData[i] = dist(gen);
  }
}

template <typename T> void Matrix<T>::dumpMatrix(const std::string &filePath) {
  std::ofstream ofs(filePath, std::ios::binary);

  if (!ofs) {
    std::cerr << "Error abrindo arquivo" << std::endl;
    return;
  }

  ofs.write(reinterpret_cast<const char *>(&nRows), sizeof(nRows));
  ofs.write(reinterpret_cast<const char *>(&nCols), sizeof(nCols));
  ofs.write(reinterpret_cast<const char *>(matrixData),
            nRows * nCols * sizeof(T));

  ofs.close();
}

template <typename T> void Matrix<T>::loadMatrix(const std::string &filePath) {
  std::ifstream ifs(filePath, std::ios::binary);

  if (!ifs) {
    std::cerr << "Error abrindo arquivo" << std::endl;
    return;
  }

  ifs.read(reinterpret_cast<char *>(&nRows), sizeof(nRows));
  ifs.read(reinterpret_cast<char *>(&nCols), sizeof(nCols));

  delete[] matrixData;
  matrixData = new T[nRows * nCols];
  ifs.read(reinterpret_cast<char *>(matrixData), nRows * nCols * sizeof(T));

  ifs.close();
}

template <typename T> void Matrix<T>::printMatrix() {
  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      std::cout << matrixData[i * nCols + j] << " ";
    }
    std::cout << std::endl;
  }
}

template <typename T> Matrix<T> Matrix<T>::operator-(Matrix &B) {
  if (nRows != B.nRows || nCols != B.nCols) {
    throw std::invalid_argument("Erro de dimensão");
  }

  Matrix C(nRows, nCols);
  for (int i = 0; i < nRows * nCols; ++i) {
    C.matrixData[i] = matrixData[i] - B.matrixData[i];
  }
  return C;
}

template <typename T> double frobeniusNorm(Matrix<T> &matrix) {
  double norm = 0.0;
  for (int i = 0; i < matrix.nRows * matrix.nCols; ++i) {
    norm += std::pow(std::abs(matrix.matrixData[i]), 2);
  }
  return std::sqrt(norm);
}

#endif 
