#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int linhas, colunas;
  float *matriz;
} tMatriz;

tMatriz *le_matriz(const char *nomeArquivo) {
  long long int tam; // qtde de elementos na matriz
  FILE *descritorArquivo;
  int ret; // retorno da funcao de leitura no arquivo de entrada
  // recebe os argumentos de entrada
  tMatriz *matriz = (tMatriz *)malloc(sizeof(tMatriz));
  // abre o arquivo para leitura binaria
  descritorArquivo = fopen(nomeArquivo, "rb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
  }

  // le as dimensoes da matriz
  ret = fread(&matriz->linhas, sizeof(int), 1, descritorArquivo);
  if (!ret) {
    fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
  }
  ret = fread(&matriz->colunas, sizeof(int), 1, descritorArquivo);
  if (!ret) {
    fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
  }
  tam =
      matriz->linhas * matriz->colunas; // calcula a qtde de elementos da matriz

  // aloca memoria para a matriz
  matriz->matriz = (float *)malloc(sizeof(float) * tam);
  if (!matriz->matriz) {
    fprintf(stderr, "Erro de alocao da memoria da matriz\n");
  }

  // carrega a matriz de elementos do tipo float do arquivo
  ret = fread(matriz->matriz, sizeof(float), tam, descritorArquivo);
  if (ret < tam) {
    fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
  }

  fclose(descritorArquivo);
  return matriz;
}
