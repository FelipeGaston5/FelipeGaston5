#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

typedef struct NoArvore
{
    int dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct
{
    NoArvore *raiz;
} ArvoreBinaria;

void inicializar_arvore_binaria(ArvoreBinaria *arvore);
void inserir_arvore_binaria(ArvoreBinaria *arvore, int valor);
NoArvore *buscar_arvore_binaria(ArvoreBinaria arvore, int valor);
void percorrer_em_ordem(NoArvore *no);
void percorrer_pre_ordem(NoArvore *no);
void percorrer_pos_ordem(NoArvore *no);
void destruir_arvore_binaria(NoArvore *no);

#endif