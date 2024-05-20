#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define TESTE

float *vector;
/*
float globalSum;
pthread_mutex_t mutex;
*/
int nThreads;
int sizeVector;

typedef struct {
  int offset;
  int block;
} tArgs;

void *addVector(void *arg) {
  tArgs args = *(tArgs *)arg;
  int offset = args.offset;
  int block = args.block;
  float *localSum = (float *)malloc(sizeof(float));

  if (localSum == NULL) {
    pthread_exit(NULL);
  }

  *localSum = 0;
  if (offset != nThreads - 1) {
    for (long int i = block * offset; i < block * (offset + 1); i++) {
      printf("vector[i] = %f\n", vector[i]);
      *localSum += vector[i];
    }
  } else {
    for (long int i = block * offset; i < sizeVector; i++) {
      printf("vector[i] = %f\n", vector[i]);
      *localSum += vector[i];
    }
    /*pthread_mutex_lock(&mutex);
    globalSum += localSum;
    pthread_mutex_unlock(&mutex);

    return NULL;*/
  }
  pthread_exit((void *)localSum);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Numero invalido de argumentos\n");
    return 1;
  }

#ifdef TESTE
  float somaCorreta;
#endif

  FILE *file;
  file = fopen("vectors/vetor.txt", "r");
  if (file == NULL) {
    printf("pobrema");
    return 1;
  }

  nThreads = atoi(argv[1]);
  pthread_t tid[nThreads];
  float globalSum = 0;
  float **results = (float **)malloc(nThreads * sizeof(float *));

  if (results == NULL) {
    printf("Erro malloc \n");
    return 1;
  }

  fscanf(file, "%d", &sizeVector);

  int sizeBlock = sizeVector / nThreads;
  vector = (float *)malloc(sizeof(float) * sizeVector);

  if (vector == NULL) {
    printf("Erro malloc \n");
    return 1;
  }

  for (long int i = 0; i < sizeVector; i++) {
    fscanf(file, "%f", &vector[i]);
  }

#ifdef TESTE
  fscanf(file, "%f", &somaCorreta);
#endif
  /* ifdef TESTE                                                          \
       scanf("%f %f", &maiorCorreto, &menorCorreto);                           \
 */
  // fclose(file);

  for (long int i = 0; i < nThreads; i++) {
    tArgs *args = (tArgs *)malloc(sizeof(tArgs));

    if (args == NULL) {
      printf("Erro malloc \n");
      pthread_exit(NULL);
    }
    args->offset = i;
    args->block = sizeBlock;
    pthread_create(&tid[i], NULL, addVector, (void *)args);
  }

  for (long int i = 0; i < nThreads; i++) {
    pthread_join(tid[i], (void **)&results[i]);
    globalSum += *results[i];
  }

  printf("Soma Pthread: %f \n", globalSum);
  printf("Soma Correta: %f \n", somaCorreta);

  free(vector);
  free(results);
  return 0;
}
