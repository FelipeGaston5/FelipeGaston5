#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"

void inicializar_fila(Fila *fila, int capacidade)
{
    fila->dados = (int *)malloc(capacidade * sizeof(int));
    fila->frente = 0;
    fila->tras = -1;
    fila->capacidade = capacidade;
    fila->tamanho = 0;
}

void enfileirar(Fila *fila, int valor)
{
    if (fila->tamanho == fila->capacidade)
    {
        printf("Erro: Fila cheia\n");
        return;
    }
    fila->tras = (fila->tras + 1) % fila->capacidade;
    fila->dados[fila->tras] = valor;
    fila->tamanho++;
}

int desenfileirar(Fila *fila)
{
    if (fila->tamanho == 0)
    {
        printf("Erro: Fila vazia\n");
        return -1;
    }
    int valor = fila->dados[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return valor;
}

int frente_fila(Fila fila)
{
    if (fila.tamanho == 0)
    {
        printf("Erro: Fila vazia\n");
        return -1;
    }
    return fila.dados[fila.frente];
}

int fila_vazia(Fila fila)
{
    return fila.tamanho == 0;
}

void destruir_fila(Fila *fila)
{
    free(fila->dados);
    fila->frente = 0;
    fila->tras = -1;
    fila->capacidade = 0;
    fila->tamanho = 0;
}