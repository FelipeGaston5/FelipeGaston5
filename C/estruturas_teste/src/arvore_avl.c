#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore_avl.h"

int altura_avl(NoAVL *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

int maximo(int a, int b)
{
    return (a > b) ? a : b;
}

NoAVL *rotacao_direita(NoAVL *y)
{
    NoAVL *x = y->esquerda;
    NoAVL *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maximo(altura_avl(y->esquerda), altura_avl(y->direita)) + 1;
    x->altura = maximo(altura_avl(x->esquerda), altura_avl(x->direita)) + 1;

    return x;
}

NoAVL *rotacao_esquerda(NoAVL *x)
{
    NoAVL *y = x->direita;
    NoAVL *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maximo(altura_avl(x->esquerda), altura_avl(x->direita)) + 1;
    y->altura = maximo(altura_avl(y->esquerda), altura_avl(y->direita)) + 1;

    return y;
}

int fator_balanceamento(NoAVL *no)
{
    if (no == NULL)
        return 0;
    return altura_avl(no->esquerda) - altura_avl(no->direita);
}

NoAVL *inserir_no_avl(NoAVL *no, int valor)
{
    if (no == NULL)
    {
        NoAVL *novo = (NoAVL *)malloc(sizeof(NoAVL));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
        return novo;
    }

    if (valor < no->dado)
    {
        no->esquerda = inserir_no_avl(no->esquerda, valor);
    }
    else if (valor > no->dado)
    {
        no->direita = inserir_no_avl(no->direita, valor);
    }
    else
    {
        return no; // Valores iguais não são permitidos
    }

    no->altura = 1 + maximo(altura_avl(no->esquerda), altura_avl(no->direita));

    int balanceamento = fator_balanceamento(no);

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && valor < no->esquerda->dado)
    {
        return rotacao_direita(no);
    }

    // Caso Direita-Direita
    if (balanceamento < -1 && valor > no->direita->dado)
    {
        return rotacao_esquerda(no);
    }

    // Caso Esquerda-Direita
    if (balanceamento > 1 && valor > no->esquerda->dado)
    {
        no->esquerda = rotacao_esquerda(no->esquerda);
        return rotacao_direita(no);
    }

    // Caso Direita-Esquerda
    if (balanceamento < -1 && valor < no->direita->dado)
    {
        no->direita = rotacao_direita(no->direita);
        return rotacao_esquerda(no);
    }

    return no;
}

void inserir_arvore_avl(ArvoreAVL *arvore, int valor)
{
    arvore->raiz = inserir_no_avl(arvore->raiz, valor);
}

NoAVL *buscar_no_avl(NoAVL *no, int valor)
{
    if (no == NULL || no->dado == valor)
    {
        return no;
    }

    if (valor < no->dado)
    {
        return buscar_no_avl(no->esquerda, valor);
    }
    else
    {
        return buscar_no_avl(no->direita, valor);
    }
}

NoAVL *buscar_arvore_avl(ArvoreAVL arvore, int valor)
{
    return buscar_no_avl(arvore.raiz, valor);
}

void percorrer_em_ordem_avl(NoAVL *no)
{
    if (no != NULL)
    {
        percorrer_em_ordem_avl(no->esquerda);
        printf("%d ", no->dado);
        percorrer_em_ordem_avl(no->direita);
    }
}

void destruir_arvore_avl(NoAVL *no)
{
    if (no != NULL)
    {
        destruir_arvore_avl(no->esquerda);
        destruir_arvore_avl(no->direita);
        free(no);
    }
}