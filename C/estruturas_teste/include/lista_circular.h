#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

typedef struct NoCircular
{
    int dado;
    struct NoCircular *proximo;
} NoCircular;

typedef struct
{
    NoCircular *inicio;
    int tamanho;
} ListaCircular;

void inicializar_lista_circular(ListaCircular *lista);
void inserir_lista_circular(ListaCircular *lista, int valor);
int remover_lista_circular(ListaCircular *lista, int valor);
void imprimir_lista_circular(ListaCircular lista);
void destruir_lista_circular(ListaCircular *lista);

#endif