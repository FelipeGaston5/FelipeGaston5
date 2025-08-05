#include <stdio.h>
#include <stdlib.h>
#include "../include/hashtable.h"

int funcao_hash(int chave, int tamanho)
{
    return chave % tamanho;
}

void inicializar_hash_table(HashTable *ht, int tamanho)
{
    ht->tabela = (NoHash **)malloc(tamanho * sizeof(NoHash *));
    ht->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++)
    {
        ht->tabela[i] = NULL;
    }
}

void inserir_hash_table(HashTable *ht, int chave, int valor)
{
    int indice = funcao_hash(chave, ht->tamanho);

    NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = NULL;

    if (ht->tabela[indice] == NULL)
    {
        ht->tabela[indice] = novo;
    }
    else
    {
        NoHash *atual = ht->tabela[indice];
        while (atual->proximo != NULL)
        {
            if (atual->chave == chave)
            {
                atual->valor = valor; // Atualiza valor se chave já existe
                free(novo);
                return;
            }
            atual = atual->proximo;
        }

        if (atual->chave == chave)
        {
            atual->valor = valor; // Atualiza valor se chave já existe
            free(novo);
        }
        else
        {
            atual->proximo = novo;
        }
    }
}

int buscar_hash_table(HashTable ht, int chave)
{
    int indice = funcao_hash(chave, ht.tamanho);

    NoHash *atual = ht.tabela[indice];
    while (atual != NULL)
    {
        if (atual->chave == chave)
        {
            return atual->valor;
        }
        atual = atual->proximo;
    }

    return -1; // Não encontrado
}

void remover_hash_table(HashTable *ht, int chave)
{
    int indice = funcao_hash(chave, ht->tamanho);

    NoHash *atual = ht->tabela[indice];
    NoHash *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->chave == chave)
        {
            if (anterior == NULL)
            {
                ht->tabela[indice] = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

void imprimir_hash_table(HashTable ht)
{
    printf("Hash Table:\n");
    for (int i = 0; i < ht.tamanho; i++)
    {
        printf("[%d]: ", i);
        NoHash *atual = ht.tabela[i];
        while (atual != NULL)
        {
            printf("(%d, %d) ", atual->chave, atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

void destruir_hash_table(HashTable *ht)
{
    for (int i = 0; i < ht->tamanho; i++)
    {
        NoHash *atual = ht->tabela[i];
        while (atual != NULL)
        {
            NoHash *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(ht->tabela);
    ht->tamanho = 0;
}