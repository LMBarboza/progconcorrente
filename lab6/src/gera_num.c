#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  long long int *listaNum;
  int N, ret;
  FILE *descritorArquivo;

  if (argc != 3) {
    fprintf(stderr, "Digite: %s <quantidade> <arquivo saida>\n", argv[0]);
    return 1;
  }

  N = atoi(argv[1]);
  listaNum = (long long int *)malloc(sizeof(long long int) * N);
  if (!listaNum) {
    fprintf(stderr, "Erro de alocao da memoria da matriz\n");
    return 2;
  }

  srand(time(NULL));
  for (int i = 0; i < N; i++) {
    listaNum[i] = rand();
  }

  descritorArquivo = fopen(argv[2], "wb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
    return 3;
  }

  ret = fwrite(&N, sizeof(int), 1, descritorArquivo);
  ret = fwrite(listaNum, sizeof(long long int), N, descritorArquivo);
  if (ret < N) {
    fprintf(stderr, "Erro de escrita no  arquivo\n");
    return 4;
  }

  fclose(descritorArquivo);
  free(listaNum);
  return 0;
}
