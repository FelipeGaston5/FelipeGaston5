#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

typedef struct NoDuplo
{
    int dado;
    struct NoDuplo *anterior;
    struct NoDuplo *proximo;
} NoDuplo;

typedef struct
{
    NoDuplo *inicio;
    NoDuplo *fim;
    int tamanho;
} ListaDupla;

void inicializar_lista_dupla(ListaDupla *lista);
void inserir_inicio_lista_dupla(ListaDupla *lista, int valor);
void inserir_fim_lista_dupla(ListaDupla *lista, int valor);
int remover_lista_dupla(ListaDupla *lista, int valor);
void imprimir_lista_dupla(ListaDupla lista);
void imprimir_lista_dupla_reverso(ListaDupla lista);
void destruir_lista_dupla(ListaDupla *lista);

#endif