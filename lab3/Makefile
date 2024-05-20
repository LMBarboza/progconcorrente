CC = gcc
CFLAGS = -Wall -Wextra -pthread 

.PHONY: 

all:
	$(CC) $(CFLAGS) src/gera_matriz.c -o bin/gera_matriz.out
	$(CC) $(CFLAGS) src/sgemm_seq.c src/le_matriz.c -o bin/sgemm_seq.out
#	$(CC) $(CFLAGS) src/sgemm_mult.c src/le_matriz.c -o bin/sgemm_mult.out

gen_mat: bin/gera_matriz.out
	$< 500 500 matrix/matrix1 
	$< 500 500 matrix/matrix2

run_seq: bin/sgemm_seq.out 
	$< matrix/matrix1 matrix/matrix2 results/seq_result 
	 

run_mult: bin/gera_matriz.out 
	$< $(ARGS) 
