CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = src
BIN_DIR = bin

.PHONY: all clean

all: $(BIN_DIR)/vec_pthread

$(BIN_DIR)/vec_pthread: $(SRC_DIR)/main.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

run: $(BIN_DIR)/vec_pthread
	$< $(ARGS) 

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)


