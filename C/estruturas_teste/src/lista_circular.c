#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_circular.h"

void inicializar_lista_circular(ListaCircular *lista)
{
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserir_lista_circular(ListaCircular *lista, int valor)
{
    NoCircular *novo = (NoCircular *)malloc(sizeof(NoCircular));
    novo->dado = valor;

    if (lista->inicio == NULL)
    {
        novo->proximo = novo;
        lista->inicio = novo;
    }
    else
    {
        NoCircular *atual = lista->inicio;
        while (atual->proximo != lista->inicio)
        {
            atual = atual->proximo;
        }
        atual->proximo = novo;
        novo->proximo = lista->inicio;
    }
    lista->tamanho++;
}

int remover_lista_circular(ListaCircular *lista, int valor)
{
    if (lista->inicio == NULL)
        return 0;

    NoCircular *atual = lista->inicio;
    NoCircular *anterior = NULL;

    do
    {
        if (atual->dado == valor)
        {
            if (anterior == NULL)
            { // Removendo o primeiro nó
                if (atual->proximo == lista->inicio)
                { // Único nó
                    lista->inicio = NULL;
                }
                else
                {
                    NoCircular *ultimo = lista->inicio;
                    while (ultimo->proximo != lista->inicio)
                    {
                        ultimo = ultimo->proximo;
                    }
                    lista->inicio = atual->proximo;
                    ultimo->proximo = lista->inicio;
                }
            }
            else
            {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            lista->tamanho--;
            return 1;
        }

        anterior = atual;
        atual = atual->proximo;
    } while (atual != lista->inicio);

    return 0;
}

void imprimir_lista_circular(ListaCircular lista)
{
    if (lista.inicio == NULL)
    {
        printf("Lista Circular Vazia\n");
        return;
    }

    NoCircular *atual = lista.inicio;
    printf("Lista Circular (%d elementos): ", lista.tamanho);
    do
    {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    } while (atual != lista.inicio);
    printf("\n");
}

void destruir_lista_circular(ListaCircular *lista)
{
    if (lista->inicio == NULL)
        return;

    NoCircular *atual = lista->inicio;
    NoCircular *proximo;

    do
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    } while (atual != lista->inicio);

    lista->inicio = NULL;
    lista->tamanho = 0;
}