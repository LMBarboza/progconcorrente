## Compilação

Para compilar os programas principais e auxiliares, utilize o seguinte comando:

```bash
make all
```

## Gerar matrizes 

As matrizes utilizadas para a multiplicação podem ser geradas da seguinte forma:

```bash 
make gen_mat
```
## Resultado 

Os resultados da mutliplicação sequencial e multithreaded ficam armazenados no diretório results/. Para executar os programas utilize:

```bash 
make run_seq
make run_mult
```
Os resultados podem ser testados com:

```bash
make test
```

