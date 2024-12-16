#include "../include/le_num.h"
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20
#define NTHREADS 8
// variaveis globais

sem_t slotCheio, slotVazio, mutexCons;
long long int buffer[N];

void insereBuffer(long long int item) {
  static int in = 0;
  sem_wait(&slotVazio);
  buffer[in] = item;
  in = (in + 1) % N;
  sem_post(&slotCheio);
}

long long int retiraBuffer(void) {
  static int out = 0;
  sem_wait(&slotVazio);
  sem_wait(&mutexCons);
  long long int item = buffer[out];
  out = (out + 1) % N;
  sem_post(&mutexCons);
  sem_post(&slotVazio);
  return item;
}

int ehPrimo(long long int n) {
  int i;
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;
  for (i = 3; i < sqrt(n) + 1; i += 2)
    if (n % i == 0)
      return 0;
  return 1;
}

void *produtor(void *arg) {
  tInteiros *listaInteiros = le_lista((char *)arg);
  while (1) {
    int i = 0;
    insereBuffer(listaInteiros->listaNum[i]);
    i++;
  }
  pthread_exit(NULL);
  return NULL;
}

void *consumidor(void *arg) {
  while (1) {
    long long int elemento = retiraBuffer();
  }
  pthread_exit(NULL);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Numero de argumentos errado \n");
    return 1;
  }

  pthread_t tid[NTHREADS];
  char *arquivo = argv[1];

  sem_init(&slotCheio, 0, N);
  sem_init(&slotVazio, 0, 0);
  sem_init(&mutexCons, 0, 1);

  return 0;
}
