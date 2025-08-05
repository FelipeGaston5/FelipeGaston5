#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TAMANHO_TABELA 10

typedef struct NoHash
{
    int chave;
    int valor;
    struct NoHash *proximo;
} NoHash;

typedef struct
{
    NoHash **tabela;
    int tamanho;
} HashTable;

void inicializar_hash_table(HashTable *ht, int tamanho);
void inserir_hash_table(HashTable *ht, int chave, int valor);
int buscar_hash_table(HashTable ht, int chave);
void remover_hash_table(HashTable *ht, int chave);
void imprimir_hash_table(HashTable ht);
void destruir_hash_table(HashTable *ht);

#endif