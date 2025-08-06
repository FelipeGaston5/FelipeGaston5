#include <stdio.h>
#include <stdlib.h>
#include "lista_simples.h"
// #include "lista_dupla.h"
#include "lista_circular.h"
#include "pilha.h"
#include "fila.h"
#include "arvore_binaria.h"
#include "arvore_avl.h"
#include "hashtable.h"

void testar_lista_simples()
{
    printf("\n=== TESTE LISTA SIMPLES ===\n");
    ListaSimples lista;
    inicializar_lista_simples(&lista);

    inserir_inicio_lista_simples(&lista, 10);
    inserir_inicio_lista_simples(&lista, 20);
    inserir_fim_lista_simples(&lista, 30);
    inserir_fim_lista_simples(&lista, 40);

    imprimir_lista_simples(lista);

    remover_lista_simples(&lista, 20);
    remover_lista_simples(&lista, 40);

    imprimir_lista_simples(lista);

    destruir_lista_simples(&lista);
}

// void testar_lista_dupla()
// {
//     printf("\n=== TESTE LISTA DUPLA ===\n");
//     ListaDupla lista;
//     inicializar_lista_dupla(&lista);

//     inserir_inicio_lista_dupla(&lista, 10);
//     inserir_inicio_lista_dupla(&lista, 20);
//     inserir_fim_lista_dupla(&lista, 30);
//     inserir_fim_lista_dupla(&lista, 40);

//     imprimir_lista_dupla(lista);
//     imprimir_lista_dupla_reverso(lista);

//     remover_lista_dupla(&lista, 20);
//     remover_lista_dupla(&lista, 40);

//     imprimir_lista_dupla(lista);

//     destruir_lista_dupla(&lista);
// }

void testar_lista_circular()
{
    printf("\n=== TESTE LISTA CIRCULAR ===\n");
    ListaCircular lista;
    inicializar_lista_circular(&lista);

    inserir_lista_circular(&lista, 10);
    inserir_lista_circular(&lista, 20);
    inserir_lista_circular(&lista, 30);
    inserir_lista_circular(&lista, 40);

    imprimir_lista_circular(lista);

    remover_lista_circular(&lista, 20);
    remover_lista_circular(&lista, 40);

    imprimir_lista_circular(lista);

    destruir_lista_circular(&lista);
}

void testar_pilha()
{
    printf("\n=== TESTE PILHA ===\n");
    Pilha pilha;
    inicializar_pilha(&pilha, 5);

    empilhar(&pilha, 10);
    empilhar(&pilha, 20);
    empilhar(&pilha, 30);

    printf("Topo: %d\n", topo_pilha(pilha));
    printf("Desempilhado: %d\n", desempilhar(&pilha));
    printf("Desempilhado: %d\n", desempilhar(&pilha));

    empilhar(&pilha, 40);
    printf("Topo: %d\n", topo_pilha(pilha));

    destruir_pilha(&pilha);
}

void testar_fila()
{
    printf("\n=== TESTE FILA ===\n");
    Fila fila;
    inicializar_fila(&fila, 5);

    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);

    printf("Frente: %d\n", frente_fila(fila));
    printf("Desenfileirado: %d\n", desenfileirar(&fila));
    printf("Desenfileirado: %d\n", desenfileirar(&fila));

    enfileirar(&fila, 40);
    printf("Frente: %d\n", frente_fila(fila));

    destruir_fila(&fila);
}

void testar_arvore_binaria()
{
    printf("\n=== TESTE ÁRVORE BINÁRIA ===\n");
    ArvoreBinaria arvore;
    inicializar_arvore_binaria(&arvore);

    inserir_arvore_binaria(&arvore, 50);
    inserir_arvore_binaria(&arvore, 30);
    inserir_arvore_binaria(&arvore, 70);
    inserir_arvore_binaria(&arvore, 20);
    inserir_arvore_binaria(&arvore, 40);
    inserir_arvore_binaria(&arvore, 60);
    inserir_arvore_binaria(&arvore, 80);

    printf("Em ordem: ");
    percorrer_em_ordem(arvore.raiz);
    printf("\n");

    printf("Pré-ordem: ");
    percorrer_pre_ordem(arvore.raiz);
    printf("\n");

    printf("Pós-ordem: ");
    percorrer_pos_ordem(arvore.raiz);
    printf("\n");

    NoArvore *busca = buscar_arvore_binaria(arvore, 40);
    if (busca != NULL)
    {
        printf("Valor 40 encontrado na árvore\n");
    }
    else
    {
        printf("Valor 40 não encontrado na árvore\n");
    }

    destruir_arvore_binaria(arvore.raiz);
}

void testar_arvore_avl()
{
    printf("\n=== TESTE ÁRVORE AVL ===\n");
    ArvoreAVL arvore;
    inicializar_arvore_avl(&arvore);

    inserir_arvore_avl(&arvore, 10);
    inserir_arvore_avl(&arvore, 20);
    inserir_arvore_avl(&arvore, 30);
    inserir_arvore_avl(&arvore, 40);
    inserir_arvore_avl(&arvore, 50);
    inserir_arvore_avl(&arvore, 25);

    printf("Em ordem: ");
    percorrer_em_ordem_avl(arvore.raiz);
    printf("\n");

    NoAVL *busca = buscar_arvore_avl(arvore, 30);
    if (busca != NULL)
    {
        printf("Valor 30 encontrado na árvore AVL\n");
    }
    else
    {
        printf("Valor 30 não encontrado na árvore AVL\n");
    }

    destruir_arvore_avl(arvore.raiz);
}

void testar_hash_table()
{
    printf("\n=== TESTE HASH TABLE ===\n");
    HashTable ht;
    inicializar_hash_table(&ht, TAMANHO_TABELA);

    inserir_hash_table(&ht, 1, 100);
    inserir_hash_table(&ht, 2, 200);
    inserir_hash_table(&ht, 11, 110); // Colisão com 1 se TAMANHO_TABELA=10
    inserir_hash_table(&ht, 12, 120); // Colisão com 2 se TAMANHO_TABELA=10

    imprimir_hash_table(ht);

    printf("Busca chave 1: %d\n", buscar_hash_table(ht, 1));
    printf("Busca chave 11: %d\n", buscar_hash_table(ht, 11));

    remover_hash_table(&ht, 2);
    imprimir_hash_table(ht);

    destruir_hash_table(&ht);
}

void menu_principal()
{
    int opcao;

    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Testar Lista Simples\n");
        // printf("2. Testar Lista Dupla\n");
        printf("3. Testar Lista Circular\n");
        printf("4. Testar Pilha\n");
        printf("5. Testar Fila\n");
        printf("6. Testar Árvore Binária\n");
        printf("7. Testar Árvore AVL\n");
        printf("8. Testar Hash Table\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            testar_lista_simples();
            break;
        // case 2:
        //     testar_lista_dupla();
        //     break;
        case 3:
            testar_lista_circular();
            break;
        case 4:
            testar_pilha();
            break;
        case 5:
            testar_fila();
            break;
        case 6:
            testar_arvore_binaria();
            break;
        case 7:
            testar_arvore_avl();
            break;
        case 8:
            testar_hash_table();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main()
{
    menu_principal();
    return 0;
}