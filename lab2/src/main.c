#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

float* vector;
/*
float globalSum;
*/
int nThreads;
int sizeVector;

pthread_mutex_t mutex;

typedef struct {
  int offset;
  int block;
} tArgs;

void* addVector(void* arg) {
  tArgs args = *(tArgs*) arg; 
  int offset = args.offset;
  int block = args.block;
  float localSum = 0;
  
  if (offset != nThreads - 1) {
    for (size_t i = block * offset; i < block * (offset + 1); i++) {
      localSum += vector[i];
    }
  }
  else {
    for (size_t i = block * offset; i < sizeVector; i++) {
      localSum += vector[i];
  }
  /*pthread_mutex_lock(&mutex);
  globalSum += localSum;
  pthread_mutex_unlock(&mutex);

  return NULL;*/
  pthread((void*) localSum);
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Numero invalido de argumentos\n");
    return 1;
  }

  nThreads = atoi(argv[1]);
  pthread_t tid[nThreads];
  float globalSum = 0;
  float* results = (float*) malloc(sizeof(float) * nThreads);
  if (results == NULL) {
      printf("Erro malloc \n");
    }

  int sizeBlock = sizeVector / nThreads;
  
  for (size_t i = 0; i < nThreads; i++){
    tArgs* args = (tArgs*) malloc(sizeof(tArgs));

    if (args == NULL) {
        printf("Erro malloc \n");
        pthred_exit(NULL);
      }
    args->offset = i;
    args->block = sizeBlock;
    pthread_create(&tid[i], NULL, addVector, (void*) args);
  }

  for (size_t i = 0; i < nThreads; i++){
    pthread_join(&tid[i], (void**) &results);
    globalSum += results[i];
  }
  
  free(results);
  return 0;
}
