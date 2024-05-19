CC = gcc
CFLAGS = -Wall -Wextra -pthread 

.PHONY: 

all:
	$(CC) $(CFLAGS) src/gera_vet_rand.c -o bin/gera_vet.out
	$(CC) $(CFLAGS) src/main.c -o bin/main.out

gen_vec: bin/gera_vet.out
	$< $(ARGS) > vectors/vetor.txt

run: bin/main.out vectors/vetor.txt
	$< $(ARGS) > results/soma_vetor.txt 

	
