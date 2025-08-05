#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha.h"

void inicializar_pilha(Pilha *pilha, int capacidade)
{
    pilha->dados = (int *)malloc(capacidade * sizeof(int));
    pilha->topo = -1;
    pilha->capacidade = capacidade;
}

void empilhar(Pilha *pilha, int valor)
{
    if (pilha->topo == pilha->capacidade - 1)
    {
        printf("Erro: Pilha cheia\n");
        return;
    }
    pilha->dados[++pilha->topo] = valor;
}

int desempilhar(Pilha *pilha)
{
    if (pilha->topo == -1)
    {
        printf("Erro: Pilha vazia\n");
        return -1;
    }
    return pilha->dados[pilha->topo--];
}

int topo_pilha(Pilha pilha)
{
    if (pilha.topo == -1)
    {
        printf("Erro: Pilha vazia\n");
        return -1;
    }
    return pilha.dados[pilha.topo];
}

int pilha_vazia(Pilha pilha)
{
    return pilha.topo == -1;
}

void destruir_pilha(Pilha *pilha)
{
    free(pilha->dados);
    pilha->topo = -1;
    pilha->capacidade = 0;
}