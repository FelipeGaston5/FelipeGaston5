#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_simples.h"

void inicializar_lista_simples(ListaSimples *lista)
{
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserir_inicio_lista_simples(ListaSimples *lista, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
}

void inserir_fim_lista_simples(ListaSimples *lista, int valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = valor;
    novo->proximo = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        No *atual = lista->inicio;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    lista->tamanho++;
}

int remover_lista_simples(ListaSimples *lista, int valor)
{
    No *anterior = NULL;
    No *atual = lista->inicio;

    while (atual != NULL && atual->dado != valor)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
        return 0; // Não encontrado

    if (anterior == NULL)
    {
        lista->inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    lista->tamanho--;
    return 1;
}

void imprimir_lista_simples(ListaSimples lista)
{
    No *atual = lista.inicio;
    printf("Lista Simples (%d elementos): ", lista.tamanho);
    while (atual != NULL)
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void destruir_lista_simples(ListaSimples *lista)
{
    No *atual = lista->inicio;
    while (atual != NULL)
    {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
}