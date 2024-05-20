#include "../include/le_matriz.h"
#include "../include/timer.h"
#include <stdio.h>
#include <stdlib.h>

tMatriz *t_matrizA;
tMatriz *t_matrizB;
tMatriz *t_matrizC;

typedef struct tArgs {
  int startBlock;
  int endBlock;
} tArgs;

void *sgemm(void *args) {
  tArgs *arg = *(tArgs *)args;
  for (int i = arg->startBlock; i < arg->endBlock; i++) {
    for (int j = 0; j < A->linhas; j++) {
      C->matriz[j * B->colunas + i] = 0;
      for (int k = 0; k < B->linhas; k++) {
        C->matriz[j * B->colunas + i] +=
            A->matriz[j * A->colunas + k] * B->matriz[k * B->colunas + i];
      }
    }
  }

  pthread_exit(NULL);
  return NULL;
}

int main(int argc, char *argv[]) {
  FILE *descritorArquivo; // descritor do arquivo de saida
  int ret;
  double inicio, fim;
  GET_TIME(inicio);
  if (argc != 5) {
    printf("Numero de argumentos errado \n");
    return 1;
  }
  t_matrizA = le_matriz(argv[1]);
  if (!t_matrizA) {
    printf("erro");
    return 1;
  }
  t_matrizB = le_matriz(argv[2]);
  if (!t_matrizB) {
    printf("erro");
    free(t_matrizA);
    return 1;
  }
  int nThreads = atoi(argv[3])

      pthread_t tid[nThreads];
  int colSize = t_matrizB->colunas / nThreads;
  t_matrizC = (tMatriz *)malloc(sizeof(tMatriz));
  if (!t_matrizC) {
    free(t_matrizA);
    free(t_matrizB);
    return 1;
  }
  t_matrizC->linhas = t_matrizA->linhas;
  t_matrizC->colunas = t_matrizB->colunas;
  t_matrizC->matriz =
      (float *)malloc(sizeof(float) * t_matrizC->linhas * t_matrizC->colunas);
  if (!t_matrizC->matriz) {
    free(t_matrizA);
    free(t_matrizB);
    free(t_matrizC);
    return 1;
  }
  GET_TIME(fim);
  printf("Inicializacao: %lf \n", fim - inicio);

  GET_TIME(inicio);
  for (int i = 0; i < nThreads; i++) {
    tArgs *args = (tArgs *)malloc(sizeof(tArgs));

    args->startBlock = i * colSize;
    args->endBlock =
        i == nThreads - 1 ? t_matrizB->colunas : args->startBlock + colSize;
    pthread_create(&tid[i], NULL, sgemm, (void *)args);
  }
  GET_TIME(fim);
  printf("Processamento: %lf \n", fim - inicio);

  GET_TIME(inicio);
  descritorArquivo = fopen(argv[3], "wb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
    return 3;
  }
  int tam = t_matrizC->linhas * t_matrizC->colunas;
  ret = fwrite(&t_matrizC->linhas, sizeof(int), 1, descritorArquivo);
  ret = fwrite(&t_matrizC->colunas, sizeof(int), 1, descritorArquivo);
  ret = fwrite(t_matrizC->matriz, sizeof(float), tam, descritorArquivo);
  if (ret < tam) {
    fprintf(stderr, "Erro de escrita no  arquivo\n");
    return 4;
  }

  fclose(descritorArquivo);
  free(t_matrizA->matriz);
  free(t_matrizA);
  free(t_matrizB->matriz);
  free(t_matrizB);
  free(t_matrizC->matriz);
  free(t_matrizC);

  GET_TIME(fim);
  printf("Finalizacao: %lf \n", fim - inicio);
  return 0;
}
