#include "arquivo.h"

/* =====================================
   Salvar CSV
   ===================================== */
/* Salva os trabalhos das duas filas no CSV, prioritarios primeiro */
void salvarCSV(FilaNormal *fn, FilaPrioridade *fp)
{
    FILE *arquivo;
    No *atual;

    arquivo = fopen("trabalhos.csv", "w");

    if(arquivo == NULL)
    {
        printf(VERMELHO "\nErro ao criar o arquivo!\n" RESET);
        return;
    }

    fprintf(arquivo, "id;arquivo;paginas;tipo\n");

    /* Prioritarios */
    atual = fp->inicio;
    while(atual != NULL)
    {
        fprintf(arquivo, "%d;%s;%d;%c\n",
                atual->id,
                atual->nomeArquivo,
                atual->paginas,
                atual->tipo);
        atual = atual->proximo;
    }

    /* Normais */
    atual = fn->inicio;
    while(atual != NULL)
    {
        fprintf(arquivo, "%d;%s;%d;%c\n",
                atual->id,
                atual->nomeArquivo,
                atual->paginas,
                atual->tipo);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf(VERDE "\nArquivo salvo com sucesso!\n" RESET);
}

/* =====================================
   Carregar CSV
   ===================================== */
/* Carrega o CSV e distribui os trabalhos entre as filas pelo tipo */
void carregarCSV(FilaNormal *fn, FilaPrioridade *fp)
{
    FILE *arquivo;
    char linha[200];
    int id, paginas;
    char nomeArquivo[100];
    char tipo_str[5];
    char tipo;

    arquivo = fopen("trabalhos.csv", "r");

    if(arquivo == NULL)
    {
        printf(AMARELO "\nArquivo nao encontrado!\n" RESET);
        return;
    }

    liberarFilaNormal(fn);
    liberarFilaPrioridade(fp);
    iniciarFilaNormal(fn);
    iniciarFilaPrioridade(fp);

    /* ignora cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if(sscanf(linha, "%d;%99[^;];%d;%4s",
                  &id, nomeArquivo, &paginas, tipo_str) == 4)
        {
            tipo = tipo_str[0];

            if(tipo == 'P')
                inserirPrioridade(fp, id, nomeArquivo, paginas, tipo);
            else
                inserirNormal(fn, id, nomeArquivo, paginas, tipo);
        }
    }

    fclose(arquivo);
    printf(VERDE "\nDados carregados com sucesso!\n" RESET);
}
