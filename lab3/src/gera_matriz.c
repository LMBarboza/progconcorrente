#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
  float *matriz;          // matriz que será gerada
  int linhas, colunas;    // dimensoes da matriz
  long long int tam;      // qtde de elementos na matriz
  FILE *descritorArquivo; // descritor do arquivo de saida
  int ret;             // retorno da funcao de escrita no arquivo de saida

  // recebe os argumentos de entrada
  if (argc < 4) {
    fprintf(stderr, "Digite: %s <linhas> <colunas> <arquivo saida>\n", argv[0]);
    return 1;
  }
  linhas = atoi(argv[1]);
  colunas = atoi(argv[2]);
  tam = linhas * colunas;

  // aloca memoria para a matriz
  matriz = (float *)malloc(sizeof(float) * tam);
  if (!matriz) {
    fprintf(stderr, "Erro de alocao da memoria da matriz\n");
    return 2;
  }

  // preenche a matriz com valores float aleatorios
  // randomiza a sequencia de numeros aleatorios
  srand(time(NULL));
  for (long int i = 0; i < tam; i++) {
    *(matriz + i) = (rand() % 1000) * 0.3;
  }

// imprimir na saida padrao a matriz gerada
#ifdef TEXTO
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++)
      fprintf(stdout, "%.6f ", matriz[i * colunas + j]);
    fprintf(stdout, "\n");
  }
#endif

  // escreve a matriz no arquivo
  // abre o arquivo para escrita binaria
  descritorArquivo = fopen(argv[3], "wb");
  if (!descritorArquivo) {
    fprintf(stderr, "Erro de abertura do arquivo\n");
    return 3;
  }

  ret = fwrite(&linhas, sizeof(int), 1, descritorArquivo);
  ret = fwrite(&colunas, sizeof(int), 1, descritorArquivo);
  ret = fwrite(matriz, sizeof(float), tam, descritorArquivo);
  if (ret < tam) {
    fprintf(stderr, "Erro de escrita no  arquivo\n");
    return 4;
  }

  fclose(descritorArquivo);
  free(matriz);
  return 0;
}
