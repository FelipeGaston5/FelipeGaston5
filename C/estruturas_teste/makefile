CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRC = src/main.c src/lista_simples.c src/lista_circular.c \
    src/pilha.c src/fila.c src/arvore_binaria.c src/arvore_avl.c src/hashtable.c

OBJDIR = bin
OBJ = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))

EXEC = estruturas_teste


ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RM = rmdir /S /Q $(OBJDIR) 2>NUL & del /Q $(EXEC).exe 2>NUL
    RUN = .\$(EXEC).exe
else
    MKDIR = mkdir -p $(OBJDIR)
    RM = rm -rf $(OBJDIR) $(EXEC)
    RUN = ./$(EXEC)
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: src/%.c
	$(MKDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)

run: all
	$(RUN)

.PHONY: all clean run
