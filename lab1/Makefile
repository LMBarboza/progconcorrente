CC = gcc
CFLAGS = -Wall -pthread
SOURCES = main.c  # Assuming only one source file

# Object file (automatically generated)
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXEC = vecthread

.PHONY: all clean run

all: $(EXEC)

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lpthread -o $@

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJECTS) $(EXEC)C = gcc
