#include "../include/le_num.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int main(int argc, char *argv[]) {
  int numPrimos = 0;

  if (argc != 2) {
    printf("Numero de argumentos errado \n");
    return 1;
  }
  
  tInteiros *listaInteiros = le_lista(argv[1]);
  
  for (int i = 0; i < listaInteiros->N; i++) {
    numPrimos += ehPrimo(listaInteiros->listaNum[i]);
  }
  printf("numPrimos = %d\n", numPrimos);
  return 0;
}
