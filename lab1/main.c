#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
  int* vec;
  int offset;
  int vecSamples;
} vecStruct;

void* quadrado(void* args){
  vecStruct* argumentos = (vecStruct*) args;

  int i = argumentos->offset;
  int N = argumentos->vecSamples;
  int* vetor = argumentos->vec;

  for (; i < N; i++){
    vetor[i] *= vetor[i];
  }
  pthread_exit(NULL);

}

void cria_vetor(int* vec, int vecTam){
  for (int i = 0; i < vecTam; i++){
    vec[i] = i;
  }

}

int main(int argc, char *argv[]){
  if (argc < 2){
    printf("Quantidade de argumentos incorreta \n");
    return 1;
  }

  int vecTam = atoi(argv[0]);
  int nThreads = atoi(argv[1]);

  if (vecTam < nThreads){
    printf("Vetor < numero de threads");
    return 1;
  }
  
  int* vec = (int*)malloc(sizeof(int)*vecTam);
  pthread_t tid[nThreads];
  
  cria_vetor(vec, vecTam);

  for (int i = 0; i < nThreads; i++){
    int vecSamples = vecTam / nThreads;
    vecStruct args = {vec, i, vecSamples};
    if (i == nThreads - 1){
      vecStruct args = {vec, i, vecTam};
    }

    pthread_create(&tid[i], NULL, quadrado, (void*) &args);
  }
  pthread_exit(NULL);

  return 0;
}
