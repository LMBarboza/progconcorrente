#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* vec;
int vecTam;
int nThreads;

void* rotina(void* args){
  int i = * (int*) args;
  int vecSamples = vecTam / nThreads;
  if (i == nThreads - 1){
    for (int offset = vecSamples * i; offset < vecTam; offset++){
      vec[offset] *= vec[offset];
    }
  }
  else{
    for (int offset = vecSamples * i; offset < vecSamples * (i + 1); offset++){
      vec[offset] *= vec[offset];
    }
  }
  return NULL;
}

void cria_vetor(int* vec, int vecTam){
  for (int i = 0; i < vecTam; i++){
    vec[i] = i;
  }
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

int main(int argc, char* argv[]){
  if (argc != 3){
    printf("Numero de argumentos invalido\n");
    return 1;
  }

  vecTam = atoi(argv[1]);
  nThreads = atoi(argv[2]);

  if (vecTam < nThreads){
    printf("Numero de threads maior do que tamanho do vetor\n");
    return 1;
  }
  pthread_t tid[nThreads];
  vec = (int*)malloc(sizeof(int)*vecTam);
  cria_vetor(vec, vecTam);
  print_vetor(vec, vecTam); 
  int ident[nThreads];
  for (int i = 0; i < nThreads; i++){
    ident[i] = i;
    pthread_create(&tid[i], NULL, rotina, (void*) &ident[i]);
  }
  
  for (int i = 0; i < nThreads; i++){
    pthread_join(tid[i], NULL);
  }
  print_vetor(vec, vecTam);
  free(vec);
  return 0;
}
