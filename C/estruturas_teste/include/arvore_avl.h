#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

typedef struct NoAVL
{
    int dado;
    int altura;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
} NoAVL;

typedef struct
{
    NoAVL *raiz;
} ArvoreAVL;

void inicializar_arvore_avl(ArvoreAVL *arvore);
void inserir_arvore_avl(ArvoreAVL *arvore, int valor);
NoAVL *buscar_arvore_avl(ArvoreAVL arvore, int valor);
void percorrer_em_ordem_avl(NoAVL *no);
void destruir_arvore_avl(NoAVL *no);

#endif