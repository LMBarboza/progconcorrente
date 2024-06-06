#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int N;
  float *listaNum;
} tInteiros;

tInteiros *le_lista(const char *nomeArquivo) {
  int N; 
  FILE *descritorArquivo;
  int ret; // retorno da funcao de leitura no arquivo de entrada
  // recebe os argumentos de entrada
  tInteiros *listaNum= (tInteiros *)malloc(sizeof(tInteiros));
  // abre o arquivo para leitura binaria
  descritorArquivo = fopen(nomeArquivo, "rb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
  }

  ret = fread(&listaNum->N, sizeof(int), 1, descritorArquivo);
  if (!ret) {
    fprintf(stderr, "Erro de leitura das dimensoes da listaNum arquivo \n");
  }

  // aloca memoria para a listaNum
  listaNum->listaNum = (long long int*)malloc(sizeof(long long int) * listaNum->N);

  if (!listaNum->listaNum) {
    fprintf(stderr, "Erro de alocao da memoria da listaNum\n");
  }

  // carrega a listaNum de elementos do tipo float do arquivo
  ret = fread(listaNum->listaNum, sizeof(long long int), listaNum->N, descritorArquivo);
  if (ret < tam) {
    fprintf(stderr, "Erro de leitura dos elementos da listaNum\n");
  }

  fclose(descritorArquivo);
  return listaNum;
}
