#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

// Define the tMatriz structure
typedef struct {
  int linhas;  // Number of rows
  int colunas; // Number of columns
  float *
      matriz; // Pointer to the matrix data stored in a single-dimensional array
} tMatriz;

// Function to read a matrix from a binary file
// Returns a pointer to the matrix or NULL in case of error
tMatriz *le_matriz(const char *nomeArquivo);

#endif // MATRIZ_H
