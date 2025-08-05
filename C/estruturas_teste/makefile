CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/lista_simples.c src/lista_dupla.c src/lista_circular.c \
      src/pilha.c src/fila.c src/arvore_binaria.c src/arvore_avl.c src/hashtable.c
OBJ = $(SRC:.c=.o)
EXEC = estruturas_teste

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: all
	./$(EXEC)

.PHONY: all clean run