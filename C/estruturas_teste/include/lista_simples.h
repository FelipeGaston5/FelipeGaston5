#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

typedef struct No
{
    int dado;
    struct No *proximo;
} No;

typedef struct
{
    No *inicio;
    int tamanho;
} ListaSimples;

void inicializar_lista_simples(ListaSimples *lista);
void inserir_inicio_lista_simples(ListaSimples *lista, int valor);
void inserir_fim_lista_simples(ListaSimples *lista, int valor);
int remover_lista_simples(ListaSimples *lista, int valor);
void imprimir_lista_simples(ListaSimples lista);
void destruir_lista_simples(ListaSimples *lista);

#endif