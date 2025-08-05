#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void criarArquivo(const char *nome)
{
    FILE *arquivo = fopen(nome, "w");
    if (!arquivo)
    {
        perror("Erro ao criar o arquivo");
        return;
    }

    printf("Digite o texto (digite 'FIM' em uma linha para encerrar):\n");

    char linha[MAX_LINE];
    while (1)
    {
        fgets(linha, MAX_LINE, stdin);
        if (strncmp(linha, "FIM", 3) == 0)
            break;
        fputs(linha, arquivo);
    }

    fclose(arquivo);
    printf("Arquivo '%s' criado com sucesso!\n", nome);
}

void lerArquivo(const char *nome)
{
    FILE *arquivo = fopen(nome, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("\nConteudo de '%s':\n\n", nome);

    char linha[MAX_LINE];
    while (fgets(linha, MAX_LINE, arquivo))
    {
        printf("%s", linha);
    }

    fclose(arquivo);
    printf("\n\n[Fim do arquivo]\n");
}

void editarArquivo(const char *nome)
{
    FILE *arquivo = fopen(nome, "a");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Digite o novo texto (digite 'FIM' para encerrar):\n");

    char linha[MAX_LINE];
    while (1)
    {
        fgets(linha, MAX_LINE, stdin);
        if (strncmp(linha, "FIM", 3) == 0)
            break;
        fputs(linha, arquivo);
    }

    fclose(arquivo);
    printf("Arquivo '%s' editado com sucesso!\n", nome);
}

int main()
{
    int opcao;
    char nomeArquivo[100];
    char caminhoCompleto[150];

    system("mkdir exe\\txt > nul 2>nul");

    do
    {
        printf("\n--- Editor de Texto Simples ---\n");
        printf("1. Criar novo arquivo\n");
        printf("2. Ler arquivo existente\n");
        printf("3. Editar arquivo existente\n");
        printf("0. Sair\n");
        printf("Escolha uma opc: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            printf("Nome do novo arquivo (ex: exemplo.txt): ");
            fgets(nomeArquivo, 100, stdin);
            nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
            criarArquivo(nomeArquivo);
            break;
        case 2:
            printf("Nome do arquivo para leitura: ");
            fgets(nomeArquivo, 100, stdin);
            nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
            lerArquivo(nomeArquivo);
            break;
        case 3:
            printf("Nome do arquivo para edt: ");
            fgets(nomeArquivo, 100, stdin);
            nomeArquivo[strcspn(nomeArquivo, "\n")] = 0;
            editarArquivo(nomeArquivo);
            break;
        case 0:
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opc invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
