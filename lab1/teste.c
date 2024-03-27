#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct{
  int a;
} meu;


void* tarefa(void* arg){
  printf("thread %d \n", *(int*)arg);
  pthread_exit(NULL);
}


int main(void){
  pthread_t tid[5];
  int a[5];
  meu b = {0};
  for (int i = 0; i < 5; i++){
    a[i] = i;
    b.a = i;
    pthread_create(&tid[i], NULL, tarefa, (void*)&b.a);
    
  }
  pthread_exit(NULL);
}
