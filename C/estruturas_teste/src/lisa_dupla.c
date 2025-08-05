#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_dupla.h"

void inicializar_lista_dupla(ListaDupla *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

void inserir_inicio_lista_dupla(ListaDupla *lista, int valor)
{
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    novo->dado = valor;
    novo->anterior = NULL;
    novo->proximo = lista->inicio;

    if (lista->inicio != NULL)
    {
        lista->inicio->anterior = novo;
    }
    else
    {
        lista->fim = novo;
    }

    lista->inicio = novo;
    lista->tamanho++;
}

void inserir_fim_lista_dupla(ListaDupla *lista, int valor)
{
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = lista->fim;

    if (lista->fim != NULL)
    {
        lista->fim->proximo = novo;
    }
    else
    {
        lista->inicio = novo;
    }

    lista->fim = novo;
    lista->tamanho++;
}

int remover_lista_dupla(ListaDupla *lista, int valor)
{
    NoDuplo *atual = lista->inicio;

    while (atual != NULL && atual->dado != valor)
    {
        atual = atual->proximo;
    }

    if (atual == NULL)
        return 0; // Não encontrado

    if (atual->anterior != NULL)
    {
        atual->anterior->proximo = atual->proximo;
    }
    else
    {
        lista->inicio = atual->proximo;
    }

    if (atual->proximo != NULL)
    {
        atual->proximo->anterior = atual->anterior;
    }
    else
    {
        lista->fim = atual->anterior;
    }

    free(atual);
    lista->tamanho--;
    return 1;
}

void imprimir_lista_dupla(ListaDupla lista)
{
    NoDuplo *atual = lista.inicio;
    printf("Lista Dupla (%d elementos): ", lista.tamanho);
    while (atual != NULL)
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_lista_dupla_reverso(ListaDupla lista)
{
    NoDuplo *atual = lista.fim;
    printf("Lista Dupla Reverso (%d elementos): ", lista.tamanho);
    while (atual != NULL)
    {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }
    printf("\n");
}

void destruir_lista_dupla(ListaDupla *lista)
{
    NoDuplo *atual = lista->inicio;
    while (atual != NULL)
    {
        NoDuplo *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}