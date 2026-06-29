#include "arquivo.h"

/* Salva os trabalhos das duas filas no CSV, prioritarios primeiro */
void salvarCSV(FilaNormal *fn, FilaPrioridade *fp)
{
    FILE *arquivo;
    int i, pos;

    arquivo = fopen("trabalhos.csv", "w");

    if(arquivo == NULL)
    {
        printf("\nErro ao criar o arquivo!\n");
        return;
    }

    fprintf(arquivo, "id;arquivo;paginas;tipo\n");

    /* Prioritarios */
    pos = fp->inicio;
    for(i = 0; i < fp->quantidade; i++)
    {
        fprintf(arquivo, "%d;%s;%d;%c\n",
                fp->dados[pos].id,
                fp->dados[pos].nomeArquivo,
                fp->dados[pos].paginas,
                fp->dados[pos].tipo);

        pos = (pos + 1) % MAX;
    }

    /* Normais */
    for(i = 0; i < fn->quantidade; i++)
    {
        fprintf(arquivo, "%d;%s;%d;%c\n",
                fn->dados[i].id,
                fn->dados[i].nomeArquivo,
                fn->dados[i].paginas,
                fn->dados[i].tipo);
    }

    fclose(arquivo);
    printf("\nArquivo salvo com sucesso!\n");
}

/* Carrega o CSV e distribui os trabalhos entre as filas pelo tipo */
void carregarCSV(FilaNormal *fn, FilaPrioridade *fp)
{
    FILE *arquivo;
    Trabalho t;
    char linha[200];

    arquivo = fopen("trabalhos.csv", "r");

    if(arquivo == NULL)
    {
        printf("\nArquivo nao encontrado!\n");
        return;
    }

    iniciarFilaNormal(fn);
    iniciarFilaPrioridade(fp);

    /* Ignora o cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while(fscanf(arquivo, "%d;%99[^;];%d;%c\n",
                 &t.id,
                 t.nomeArquivo,
                 &t.paginas,
                 &t.tipo) == 4)
    {
        if(t.tipo == 'P')
            inserirPrioridade(fp, t);
        else
            inserirNormal(fn, t);
    }

    fclose(arquivo);
    printf("\nDados carregados com sucesso!\n");
}
