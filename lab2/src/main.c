#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

float vector;
float globalSum;
int nThreads;

pthread_mutex_t mutex;

void* addVector(void* arg) {
  int offset = *(size_t) arg; 
  int block = sizeVector / nThreads;
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
  pthread_mutex_lock(&mutex);
  globalSum += localSum;
  pthread_mutex_unlock(&mutex);

  return NULL;
}


int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Numero invalido de argumentos\n");
    return 1;
  }

  nThreads = atoi(argv[1]);
  pthread_t tid[nThreads];

  for (size_t i = 0; i < nThreads; i++){
    pthread_create(&tid[i], NULL, addVector, (void*) &tid[i]);
  }

  for (size_t i = 0; i < nThreads; i++){
    pthread_join(&tid[i], NULL);
  }

  return 0;
}
