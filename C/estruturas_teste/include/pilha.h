#ifndef PILHA_H
#define PILHA_H

typedef struct
{
    int *dados;
    int topo;
    int capacidade;
} Pilha;

void inicializar_pilha(Pilha *pilha, int capacidade);
void empilhar(Pilha *pilha, int valor);
int desempilhar(Pilha *pilha);
int topo_pilha(Pilha pilha);
int pilha_vazia(Pilha pilha);
void destruir_pilha(Pilha *pilha);

#endif