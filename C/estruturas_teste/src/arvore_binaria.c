#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore_binaria.h"

void inicializar_arvore_binaria(ArvoreBinaria *arvore)
{
    arvore->raiz = NULL;
}

NoArvore *inserir_no_arvore_binaria(NoArvore *no, int valor)
{
    if (no == NULL)
    {
        NoArvore *novo = (NoArvore *)malloc(sizeof(NoArvore));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (valor < no->dado)
    {
        no->esquerda = inserir_no_arvore_binaria(no->esquerda, valor);
    }
    else if (valor > no->dado)
    {
        no->direita = inserir_no_arvore_binaria(no->direita, valor);
    }

    return no;
}

void inserir_arvore_binaria(ArvoreBinaria *arvore, int valor)
{
    arvore->raiz = inserir_no_arvore_binaria(arvore->raiz, valor);
}

NoArvore *buscar_no_arvore_binaria(NoArvore *no, int valor)
{
    if (no == NULL || no->dado == valor)
    {
        return no;
    }

    if (valor < no->dado)
    {
        return buscar_no_arvore_binaria(no->esquerda, valor);
    }
    else
    {
        return buscar_no_arvore_binaria(no->direita, valor);
    }
}

NoArvore *buscar_arvore_binaria(ArvoreBinaria arvore, int valor)
{
    return buscar_no_arvore_binaria(arvore.raiz, valor);
}

void percorrer_em_ordem(NoArvore *no)
{
    if (no != NULL)
    {
        percorrer_em_ordem(no->esquerda);
        printf("%d ", no->dado);
        percorrer_em_ordem(no->direita);
    }
}

void percorrer_pre_ordem(NoArvore *no)
{
    if (no != NULL)
    {
        printf("%d ", no->dado);
        percorrer_pre_ordem(no->esquerda);
        percorrer_pre_ordem(no->direita);
    }
}

void percorrer_pos_ordem(NoArvore *no)
{
    if (no != NULL)
    {
        percorrer_pos_ordem(no->esquerda);
        percorrer_pos_ordem(no->direita);
        printf("%d ", no->dado);
    }
}

void destruir_arvore_binaria(NoArvore *no)
{
    if (no != NULL)
    {
        destruir_arvore_binaria(no->esquerda);
        destruir_arvore_binaria(no->direita);
        free(no);
    }
}