#include "fila.h"

/* Inicializa a fila normal zerada */
void iniciarFilaNormal(FilaNormal *f)
{
    f->quantidade = 0;
}

/* Inicializa a fila circular zerada */
void iniciarFilaPrioridade(FilaPrioridade *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

/* Verifica se a fila normal esta vazia */
int filaNormalVazia(FilaNormal *f)
{
    return (f->quantidade == 0);
}

/* Verifica se a fila normal esta cheia */
int filaNormalCheia(FilaNormal *f)
{
    return (f->quantidade == MAX);
}

/* Verifica se a fila prioritaria esta vazia */
int filaPrioridadeVazia(FilaPrioridade *f)
{
    return (f->quantidade == 0);
}

/* Verifica se a fila prioritaria esta cheia */
int filaPrioridadeCheia(FilaPrioridade *f)
{
    return (f->quantidade == MAX);
}

/* Insere um trabalho no fim da fila normal */
int inserirNormal(FilaNormal *f, Trabalho t)
{
    if (filaNormalCheia(f))
        return 0;

    f->dados[f->quantidade] = t;
    f->quantidade++;

    return 1;
}

/* Insere um trabalho no fim da fila circular */
int inserirPrioridade(FilaPrioridade *f, Trabalho t)
{
    if (filaPrioridadeCheia(f))
        return 0;

    f->dados[f->fim] = t;
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;

    return 1;
}

/* Remove o primeiro trabalho da fila normal e desloca os demais */
Trabalho removerNormal(FilaNormal *f)
{
    Trabalho t;
    int i;

    t.id = -1;

    if (filaNormalVazia(f))
        return t;

    t = f->dados[0];

    for (i = 0; i < f->quantidade - 1; i++)
        f->dados[i] = f->dados[i + 1];

    f->quantidade--;

    return t;
}

/* Remove o primeiro trabalho da fila circular avancando o inicio */
Trabalho removerPrioridade(FilaPrioridade *f)
{
    Trabalho t;

    t.id = -1;

    if (filaPrioridadeVazia(f))
        return t;

    t = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;

    return t;
}

/* Lista todos os trabalhos da fila normal */
void listarFilaNormal(FilaNormal *f)
{
    int i;

    if (filaNormalVazia(f))
    {
        printf("\nFila normal vazia!\n");
        return;
    }

    printf("\n========== FILA NORMAL ==========\n");

    for (i = 0; i < f->quantidade; i++)
    {
        printf("\nID: %d", f->dados[i].id);
        printf("\nArquivo: %s", f->dados[i].nomeArquivo);
        printf("\nPaginas: %d", f->dados[i].paginas);
        printf("\nTipo: %c", f->dados[i].tipo);
        printf("\n-------------------------------");
    }

    printf("\n");
}

/* Lista todos os trabalhos da fila circular percorrendo do inicio ao fim */
void listarFilaPrioridade(FilaPrioridade *f)
{
    int i, pos;

    if (filaPrioridadeVazia(f))
    {
        printf("\nFila prioritaria vazia!\n");
        return;
    }

    printf("\n====== FILA PRIORITARIA ======\n");

    pos = f->inicio;

    for (i = 0; i < f->quantidade; i++)
    {
        printf("\nID: %d", f->dados[pos].id);
        printf("\nArquivo: %s", f->dados[pos].nomeArquivo);
        printf("\nPaginas: %d", f->dados[pos].paginas);
        printf("\nTipo: %c", f->dados[pos].tipo);
        printf("\n-------------------------------");

        pos = (pos + 1) % MAX;
    }

    printf("\n");
}

/* Verifica se o ID ja existe em qualquer uma das duas filas */
int idExiste(FilaNormal *fn, FilaPrioridade *fp, int id)
{
    int i, pos;

    for(i = 0; i < fn->quantidade; i++)
    {
        if(fn->dados[i].id == id)
            return 1;
    }

    pos = fp->inicio;
    for(i = 0; i < fp->quantidade; i++)
    {
        if(fp->dados[pos].id == id)
            return 1;
        pos = (pos + 1) % MAX;
    }

    return 0;
}

/* Busca um trabalho pelo ID na fila normal */
int buscarNormal(FilaNormal *f, int id)
{
    int i;

    for(i = 0; i < f->quantidade; i++)
    {
        if(f->dados[i].id == id)
        {
            printf("\n=========== TRABALHO ENCONTRADO ===========\n");
            printf("ID: %d\n", f->dados[i].id);
            printf("Arquivo: %s\n", f->dados[i].nomeArquivo);
            printf("Paginas: %d\n", f->dados[i].paginas);
            printf("Tipo: %c\n", f->dados[i].tipo);
            return 1;
        }
    }

    return 0;
}

/* Busca um trabalho pelo ID na fila circular */
int buscarPrioridade(FilaPrioridade *f, int id)
{
    int i;
    int pos = f->inicio;

    for(i = 0; i < f->quantidade; i++)
    {
        if(f->dados[pos].id == id)
        {
            printf("\n=========== TRABALHO ENCONTRADO ===========\n");
            printf("ID: %d\n", f->dados[pos].id);
            printf("Arquivo: %s\n", f->dados[pos].nomeArquivo);
            printf("Paginas: %d\n", f->dados[pos].paginas);
            printf("Tipo: %c\n", f->dados[pos].tipo);
            return 1;
        }
        pos = (pos + 1) % MAX;
    }

    return 0;
}

/* Remove um trabalho especifico da fila normal pelo ID */
int cancelarNormal(FilaNormal *f, int id)
{
    int i, j;

    for(i = 0; i < f->quantidade; i++)
    {
        if(f->dados[i].id == id)
        {
            for(j = i; j < f->quantidade - 1; j++)
                f->dados[j] = f->dados[j + 1];

            f->quantidade--;
            return 1;
        }
    }

    return 0;
}

/* Remove um trabalho especifico da fila circular pelo ID, reconstruindo a fila */
int cancelarPrioridade(FilaPrioridade *f, int id)
{
    Trabalho aux[MAX];
    int novaQuantidade = 0;
    int pos, encontrado = 0;
    int i;

    if(filaPrioridadeVazia(f))
        return 0;

    pos = f->inicio;

    for(i = 0; i < f->quantidade; i++)
    {
        if(f->dados[pos].id != id)
            aux[novaQuantidade++] = f->dados[pos];
        else
            encontrado = 1;

        pos = (pos + 1) % MAX;
    }

    if(encontrado)
    {
        f->inicio = 0;
        f->fim = 0;
        f->quantidade = 0;

        for(i = 0; i < novaQuantidade; i++)
            inserirPrioridade(f, aux[i]);
    }

    return encontrado;
}
