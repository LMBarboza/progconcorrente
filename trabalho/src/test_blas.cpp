#include "../include/matrix.h"
#include "../include/timer.h"
#include <iostream>

extern "C" void dgeqrf_(int *M, int *N, double *A, int *LDA, double *TAU,
                        double *WORK, int *LWORK, int *INFO);

template <typename T> void QR(Matrix<T> *A) {
  double *tau = new double[A->nCols];
  double *work;
  int lwork = -1;
  int info;
  dgeqrf_(&A->nRows, &A->nCols, A->matrixData, &A->nRows, tau, work, &lwork,
          &info);
}

void printTime(Timer *timer) {
  std::cout << "T(ms): " << timer->getTime() << std::endl;
  timer->reset();
}

int main(void) {
  Timer timer;

  Matrix<double> matrix250(250, 250);
  // Matrix<double> matrix500(500, 500);
  // Matrix<double> matrix1000(1000, 1000);

  matrix250.fillMatrix();
  //  matrix500.fillMatrix();
  // matrix1000.fillMatrix();

  matrix250.dumpMatrix("matrix250.bin");
  // matrix500.dumpMatrix("matrix500.bin");
  // matrix1000.dumpMatrix("matrix1000.bin");

  timer.start();
  QR(&matrix250);
  timer.end();
  printTime(&timer);
  /*
    timer.start();
    QR(&matrix500);
    timer.end();
    printTime(&timer);


    timer.start();
    QR(&matrix1000);
    timer.end();
    printTime(&timer);
  */
  matrix250.dumpMatrix("QR250.bin");
  // matrix500.dumpMatrix("QR500.bin");
  // matrix1000.dumpMatrix("QR1000.bin");

  return 0;
}
