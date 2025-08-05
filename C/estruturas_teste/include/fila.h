#ifndef FILA_H
#define FILA_H

typedef struct
{
    int *dados;
    int frente;
    int tras;
    int capacidade;
    int tamanho;
} Fila;

void inicializar_fila(Fila *fila, int capacidade);
void enfileirar(Fila *fila, int valor);
int desenfileirar(Fila *fila);
int frente_fila(Fila fila);
int fila_vazia(Fila fila);
void destruir_fila(Fila *fila);

#endif