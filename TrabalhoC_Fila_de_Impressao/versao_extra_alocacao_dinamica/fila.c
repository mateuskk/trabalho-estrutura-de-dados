#include "fila.h"

/* =========================================================
   Criar No
   ========================================================= */
/* Aloca e retorna um novo no com os dados do trabalho */
No *criarNo(int id, char *nomeArquivo, int paginas, char tipo)
{
    No *novo = (No *)malloc(sizeof(No));

    if(novo == NULL)
    {
        printf(VERMELHO "\nErro ao alocar memoria!\n" RESET);
        return NULL;
    }

    novo->id      = id;
    novo->paginas = paginas;
    novo->tipo    = tipo;
    novo->proximo = NULL;

    strncpy(novo->nomeArquivo, nomeArquivo, sizeof(novo->nomeArquivo) - 1);
    novo->nomeArquivo[sizeof(novo->nomeArquivo) - 1] = '\0';

    return novo;
}

/* =========================================================
   Inicializacao
   ========================================================= */
/* Inicializa a fila normal zerada */
void iniciarFilaNormal(FilaNormal *f)
{
    f->inicio    = NULL;
    f->fim       = NULL;
    f->quantidade = 0;
}

/* Inicializa a fila prioritaria zerada */
void iniciarFilaPrioridade(FilaPrioridade *f)
{
    f->inicio    = NULL;
    f->fim       = NULL;
    f->quantidade = 0;
}

/* =========================================================
   Verificacoes
   ========================================================= */
/* Verifica se a fila normal esta vazia */
int filaNormalVazia(FilaNormal *f)
{
    return (f->quantidade == 0);
}

/* Verifica se a fila prioritaria esta vazia */
int filaPrioridadeVazia(FilaPrioridade *f)
{
    return (f->quantidade == 0);
}

/* =========================================================
   Insercao - Fila Normal
   ========================================================= */
/* Insere um trabalho no fim da fila normal encadeada */
void inserirNormal(FilaNormal *f, int id, char *nome, int pag, char tipo)
{
    No *novo = criarNo(id, nome, pag, tipo);
    if(novo == NULL) return;

    if(f->fim == NULL)
    {
        f->inicio = novo;
        f->fim    = novo;
    }
    else
    {
        f->fim->proximo = novo;
        f->fim          = novo;
    }

    f->quantidade++;
}

/* =========================================================
   Insercao - Fila Prioritaria
   ========================================================= */
/* Insere um trabalho no fim da fila prioritaria encadeada */
void inserirPrioridade(FilaPrioridade *f, int id, char *nome, int pag, char tipo)
{
    No *novo = criarNo(id, nome, pag, tipo);
    if(novo == NULL) return;

    if(f->fim == NULL)
    {
        f->inicio = novo;
        f->fim    = novo;
    }
    else
    {
        f->fim->proximo = novo;
        f->fim          = novo;
    }

    f->quantidade++;
}

/* =========================================================
   Remocao - Fila Normal (retorna ponteiro, caller usa free)
   ========================================================= */
/* Remove o primeiro trabalho da fila normal e retorna o no */
No *removerNormal(FilaNormal *f)
{
    No *removido;

    if(filaNormalVazia(f))
        return NULL;

    removido  = f->inicio;
    f->inicio = f->inicio->proximo;

    if(f->inicio == NULL)
        f->fim = NULL;

    removido->proximo = NULL;
    f->quantidade--;

    return removido;
}

/* =========================================================
   Remocao - Fila Prioritaria
   ========================================================= */
/* Remove o primeiro trabalho da fila prioritaria e retorna o no */
No *removerPrioridade(FilaPrioridade *f)
{
    No *removido;

    if(filaPrioridadeVazia(f))
        return NULL;

    removido  = f->inicio;
    f->inicio = f->inicio->proximo;

    if(f->inicio == NULL)
        f->fim = NULL;

    removido->proximo = NULL;
    f->quantidade--;

    return removido;
}

/* =========================================================
   Listar Fila Normal
   ========================================================= */
/* Percorre e exibe todos os trabalhos da fila normal */
void listarFilaNormal(FilaNormal *f)
{
    No *atual = f->inicio;

    if(filaNormalVazia(f))
    {
        printf(VERMELHO "\nFila normal vazia!\n" RESET);
        return;
    }

    printf(CIANO "\n========== FILA NORMAL ==========\n" RESET);

    while(atual != NULL)
    {
        printf("\nID: %d",       atual->id);
        printf("\nArquivo: %s",  atual->nomeArquivo);
        printf("\nPaginas: %d",  atual->paginas);
        printf("\nTipo: %c",     atual->tipo);
        printf("\n-------------------------------");
        atual = atual->proximo;
    }

    printf("\n");
}

/* =========================================================
   Listar Fila Prioritaria
   ========================================================= */
/* Percorre e exibe todos os trabalhos da fila prioritaria */
void listarFilaPrioridade(FilaPrioridade *f)
{
    No *atual = f->inicio;

    if(filaPrioridadeVazia(f))
    {
        printf(VERMELHO "\nFila prioritaria vazia!\n" RESET);
        return;
    }

    printf(CIANO "\n====== FILA PRIORITARIA ======\n" RESET);

    while(atual != NULL)
    {
        printf("\nID: %d",       atual->id);
        printf("\nArquivo: %s",  atual->nomeArquivo);
        printf("\nPaginas: %d",  atual->paginas);
        printf("\nTipo: %c",     atual->tipo);
        printf("\n-------------------------------");
        atual = atual->proximo;
    }

    printf("\n");
}

/* =========================================================
   Buscar na Fila Normal
   ========================================================= */
/* Verifica se o ID ja existe em qualquer uma das duas filas */
int idExiste(FilaNormal *fn, FilaPrioridade *fp, int id)
{
    No *atual;

    atual = fn->inicio;
    while(atual != NULL)
    {
        if(atual->id == id)
            return 1;
        atual = atual->proximo;
    }

    atual = fp->inicio;
    while(atual != NULL)
    {
        if(atual->id == id)
            return 1;
        atual = atual->proximo;
    }

    return 0;
}

/* Busca um trabalho pelo ID na fila normal */
int buscarNormal(FilaNormal *f, int id)
{
    No *atual = f->inicio;

    while(atual != NULL)
    {
        if(atual->id == id)
        {
            printf(CIANO "\n=========== TRABALHO ENCONTRADO ===========\n" RESET);
            printf("ID: %d\n",      atual->id);
            printf("Arquivo: %s\n", atual->nomeArquivo);
            printf("Paginas: %d\n", atual->paginas);
            printf("Tipo: %c\n",    atual->tipo);
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

/* =========================================================
   Buscar na Fila Prioritaria
   ========================================================= */
/* Busca um trabalho pelo ID na fila prioritaria */
int buscarPrioridade(FilaPrioridade *f, int id)
{
    No *atual = f->inicio;

    while(atual != NULL)
    {
        if(atual->id == id)
        {
            printf(CIANO "\n=========== TRABALHO ENCONTRADO ===========\n" RESET);
            printf("ID: %d\n",      atual->id);
            printf("Arquivo: %s\n", atual->nomeArquivo);
            printf("Paginas: %d\n", atual->paginas);
            printf("Tipo: %c\n",    atual->tipo);
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

/* =========================================================
   Cancelar da Fila Normal
   ========================================================= */
/* Remove um trabalho especifico da fila normal pelo ID */
int cancelarNormal(FilaNormal *f, int id)
{
    No *atual    = f->inicio;
    No *anterior = NULL;

    while(atual != NULL)
    {
        if(atual->id == id)
        {
            if(anterior == NULL)
                f->inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            if(atual == f->fim)
                f->fim = anterior;

            free(atual);
            f->quantidade--;
            return 1;
        }
        anterior = atual;
        atual    = atual->proximo;
    }

    return 0;
}

/* =========================================================
   Cancelar da Fila Prioritaria
   ========================================================= */
/* Remove um trabalho especifico da fila prioritaria pelo ID */
int cancelarPrioridade(FilaPrioridade *f, int id)
{
    No *atual    = f->inicio;
    No *anterior = NULL;

    while(atual != NULL)
    {
        if(atual->id == id)
        {
            if(anterior == NULL)
                f->inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            if(atual == f->fim)
                f->fim = anterior;

            free(atual);
            f->quantidade--;
            return 1;
        }
        anterior = atual;
        atual    = atual->proximo;
    }

    return 0;
}

/* =========================================================
   Liberar memoria - Fila Normal
   ========================================================= */
/* Libera toda a memoria da fila normal */
void liberarFilaNormal(FilaNormal *f)
{
    No *atual = f->inicio;
    No *proximo;

    while(atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    f->inicio    = NULL;
    f->fim       = NULL;
    f->quantidade = 0;
}

/* =========================================================
   Liberar memoria - Fila Prioritaria
   ========================================================= */
/* Libera toda a memoria da fila prioritaria */
void liberarFilaPrioridade(FilaPrioridade *f)
{
    No *atual = f->inicio;
    No *proximo;

    while(atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    f->inicio    = NULL;
    f->fim       = NULL;
    f->quantidade = 0;
}
