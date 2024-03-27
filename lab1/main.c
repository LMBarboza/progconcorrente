#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
  int* vec;
  int offset;
  int vecSamples;
  pthread_mutex_t mutex;
} vecStruct;

void* quadrado(void* args){
  vecStruct* argumentos = (vecStruct*) args;
  //pthread_mutex_lock(&argumentos->mutex);
  int i = argumentos->offset;

  printf("%d \n", i);
  int N = argumentos->vecSamples;
  int* vetor = argumentos->vec;
  for (; i < N; i++){
    vetor[i] *= vetor[i];
  }
  //pthread_mutex_unlock(&argumentos->mutex);

  pthread_exit(NULL);

}

void print_vetor(int* vec, int vecTam){
  printf("[");
    for (int i = 0; i < vecTam; i++) {
      printf("%d", vec[i]);
      if (i < vecTam - 1)
        printf(", ");
    }
    printf("]\n");
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

  int vecTam = atoi(argv[1]);
  int nThreads = atoi(argv[2]);
  

  if (vecTam < nThreads){
    printf("Vetor < numero de threads");
    return 1;
  }
  
  int* vec = (int*)malloc(sizeof(int)*vecTam);
  pthread_t tid[nThreads];
  
  cria_vetor(vec, vecTam);
  print_vetor(vec, vecTam);
  int vecSamples = vecTam / nThreads;
  vecStruct args = {vec, 0, 0, PTHREAD_MUTEX_INITIALIZER};
  
  for (int i = 0; i < nThreads; i++){
    printf("for %d\n", i);
    args.offset = i * vecSamples;
    args.vecSamples = (i + 1) * vecSamples;
    pthread_create(&tid[i], NULL, quadrado, (void*) &args);

  }
  for (int i = 0; i < nThreads; i++){
    pthread_join(tid[i], NULL);
  }
  print_vetor(args.vec, vecTam);
  free(vec);
  return 0;
}
