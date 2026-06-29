#include "estoque.h"

/* =========================================================
   Criar No
   ========================================================= */
/* Aloca e retorna um novo no com os dados do produto */
No *criarNo(int codigo, char *nome, int quantidade, float preco)
{
    No *novo = (No *)malloc(sizeof(No));

    if(novo == NULL)
    {
        printf(VERMELHO "\nErro ao alocar memoria!\n" RESET);
        return NULL;
    }

    novo->codigo    = codigo;
    novo->quantidade = quantidade;
    novo->preco     = preco;
    novo->proximo   = NULL;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    return novo;
}

/* =========================================================
   Inserir Produto (lista ordenada por codigo)
   ========================================================= */
/* Insere um produto na lista encadeada mantendo ordenacao por codigo */
void inserirProduto(No **inicio, int *qtd)
{
    int codigo, quantidade;
    float preco;
    char nome[50];
    No *novo, *atual, *anterior;

    if(*qtd >= MAX)
    {
        printf(VERMELHO "\nLista cheia!\n" RESET);
        return;
    }

    printf("\nCodigo: ");
    scanf("%d", &codigo);

    /* verifica duplicata */
    atual = *inicio;
    while(atual != NULL)
    {
        if(atual->codigo == codigo)
        {
            printf(VERMELHO "\nJa existe um produto com esse codigo!\n" RESET);
            return;
        }
        atual = atual->proximo;
    }

    getchar();
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    do
    {
        printf("Quantidade: ");
        scanf("%d", &quantidade);
        if(quantidade < 0)
            printf(VERMELHO "Quantidade invalida!\n" RESET);
    } while(quantidade < 0);

    do
    {
        printf("Preco: ");
        scanf("%f", &preco);
        if(preco < 0)
            printf(VERMELHO "Preco invalido!\n" RESET);
    } while(preco < 0);

    novo = criarNo(codigo, nome, quantidade, preco);
    if(novo == NULL) return;

    /* insercao ordenada por codigo */
    anterior = NULL;
    atual    = *inicio;

    while(atual != NULL && atual->codigo < codigo)
    {
        anterior = atual;
        atual    = atual->proximo;
    }

    novo->proximo = atual;

    if(anterior == NULL)
        *inicio = novo;
    else
        anterior->proximo = novo;

    (*qtd)++;
    printf(VERDE "\nProduto cadastrado com sucesso!\n" RESET);
}

/* =========================================================
   Listar Produtos
   ========================================================= */
/* Percorre a lista e exibe todos os produtos */
void listarProdutos(No *inicio)
{
    No *atual = inicio;
    int i = 1;

    if(atual == NULL)
    {
        printf(AMARELO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    printf(CIANO "\n=========== LISTA DE PRODUTOS ===========\n" RESET);

    while(atual != NULL)
    {
        printf("\n" NEGRITO "Produto %d" RESET "\n", i++);
        printf("Codigo.....: %d\n",      atual->codigo);
        printf("Nome.......: %s\n",      atual->nome);
        printf("Quantidade.: %d\n",      atual->quantidade);
        printf("Preco......: R$ %.2f\n", atual->preco);
        printf("-----------------------------------------\n");
        atual = atual->proximo;
    }
}

/* =========================================================
   Buscar Produto por Codigo
   ========================================================= */
/* Busca e exibe um produto pelo codigo */
void buscarProduto(No *inicio)
{
    int codigo;
    No *atual = inicio;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    while(atual != NULL)
    {
        if(atual->codigo == codigo)
        {
            printf(CIANO "\n========== PRODUTO ==========\n" RESET);
            printf("Codigo.....: %d\n",      atual->codigo);
            printf("Nome.......: %s\n",      atual->nome);
            printf("Quantidade.: %d\n",      atual->quantidade);
            printf("Preco......: R$ %.2f\n", atual->preco);
            return;
        }
        atual = atual->proximo;
    }

    printf(VERMELHO "\nProduto nao encontrado!\n" RESET);
}

/* =========================================================
   Editar Produto
   ========================================================= */
/* Edita os dados de um produto existente */
void editarProduto(No *inicio)
{
    int codigo;
    No *atual = inicio;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    while(atual != NULL)
    {
        if(atual->codigo == codigo)
        {
            getchar();
            printf("Novo nome: ");
            fgets(atual->nome, sizeof(atual->nome), stdin);
            atual->nome[strcspn(atual->nome, "\n")] = '\0';

            do
            {
                printf("Nova quantidade: ");
                scanf("%d", &atual->quantidade);
                if(atual->quantidade < 0)
                    printf(VERMELHO "Quantidade invalida!\n" RESET);
            } while(atual->quantidade < 0);

            do
            {
                printf("Novo preco: ");
                scanf("%f", &atual->preco);
                if(atual->preco < 0)
                    printf(VERMELHO "Preco invalido!\n" RESET);
            } while(atual->preco < 0);

            printf(VERDE "\nProduto editado com sucesso!\n" RESET);
            return;
        }
        atual = atual->proximo;
    }

    printf(VERMELHO "\nProduto nao encontrado!\n" RESET);
}

/* =========================================================
   Excluir Produto
   ========================================================= */
/* Exclui um produto com confirmacao, ajustando os ponteiros */
void excluirProduto(No **inicio, int *qtd)
{
    int codigo;
    char resposta;
    No *atual = *inicio;
    No *anterior = NULL;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    while(atual != NULL)
    {
        if(atual->codigo == codigo)
        {
            printf("\nProduto encontrado:\n");
            printf("Codigo.....: %d\n", atual->codigo);
            printf("Nome.......: %s\n", atual->nome);

            printf(AMARELO "\nDeseja realmente excluir? (S/N): " RESET);
            scanf(" %c", &resposta);

            if(resposta == 'S' || resposta == 's')
            {
                if(anterior == NULL)
                    *inicio = atual->proximo;
                else
                    anterior->proximo = atual->proximo;

                free(atual);
                (*qtd)--;
                printf(VERDE "\nProduto excluido com sucesso!\n" RESET);
            }
            else
            {
                printf("\nExclusao cancelada!\n");
            }
            return;
        }
        anterior = atual;
        atual    = atual->proximo;
    }

    printf(VERMELHO "\nProduto nao encontrado!\n" RESET);
}

/* =========================================================
   Buscar por Nome (parcial)
   ========================================================= */
/* Busca produtos por parte do nome */
void buscarPorNome(No *inicio)
{
    char nome[50];
    int encontrou = 0;
    No *atual = inicio;

    getchar();
    printf("\nDigite o nome ou parte do nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf(CIANO "\n========== RESULTADOS ==========\n" RESET);

    while(atual != NULL)
    {
        if(strstr(atual->nome, nome) != NULL)
        {
            encontrou = 1;
            printf("\nCodigo.....: %d\n",      atual->codigo);
            printf("Nome.......: %s\n",      atual->nome);
            printf("Quantidade.: %d\n",      atual->quantidade);
            printf("Preco......: R$ %.2f\n", atual->preco);
            printf("---------------------------------\n");
        }
        atual = atual->proximo;
    }

    if(!encontrou)
        printf(VERMELHO "\nNenhum produto encontrado!\n" RESET);
}

/* =========================================================
   Estatisticas
   ========================================================= */
/* Mostra total de produtos, itens e valor do estoque */
void estatisticas(No *inicio, int qtd)
{
    No *atual = inicio;
    int totalQuantidade = 0;
    float valorTotal = 0;

    if(atual == NULL)
    {
        printf(AMARELO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    while(atual != NULL)
    {
        totalQuantidade += atual->quantidade;
        valorTotal      += atual->quantidade * atual->preco;
        atual            = atual->proximo;
    }

    printf(CIANO "\n========== ESTATISTICAS ==========\n" RESET);
    printf("Produtos cadastrados : %d\n",      qtd);
    printf("Itens em estoque.....: %d\n",      totalQuantidade);
    printf("Valor total estoque..: R$ %.2f\n", valorTotal);
}

/* =========================================================
   Salvar CSV
   ========================================================= */
/* Salva todos os produtos no CSV percorrendo a lista */
void salvarCSV(No *inicio)
{
    FILE *arquivo;
    No *atual = inicio;

    arquivo = fopen("estoque.csv", "w");

    if(arquivo == NULL)
    {
        printf(VERMELHO "\nErro ao criar o arquivo!\n" RESET);
        return;
    }

    fprintf(arquivo, "codigo;nome;quantidade;preco\n");

    while(atual != NULL)
    {
        fprintf(arquivo, "%d;%s;%d;%.2f\n",
                atual->codigo,
                atual->nome,
                atual->quantidade,
                atual->preco);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf(VERDE "\nArquivo salvo com sucesso!\n" RESET);
}

/* =========================================================
   Carregar CSV
   ========================================================= */
/* Carrega os produtos do CSV e reconstroi a lista encadeada */
void carregarCSV(No **inicio, int *qtd)
{
    FILE *arquivo;
    char linha[200];
    int codigo, quantidade;
    float preco;
    char nome[50];

    arquivo = fopen("estoque.csv", "r");

    if(arquivo == NULL)
    {
        printf(AMARELO "\nNenhum arquivo CSV encontrado.\n" RESET);
        return;
    }

    liberarLista(inicio);
    *qtd = 0;

    /* ignora cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while(fscanf(arquivo, "%d;%49[^;];%d;%f\n",
                 &codigo, nome, &quantidade, &preco) == 4)
    {
        No *novo = criarNo(codigo, nome, quantidade, preco);
        if(novo == NULL) continue;

        /* insere no fim para preservar ordem do arquivo */
        if(*inicio == NULL)
        {
            *inicio = novo;
        }
        else
        {
            No *atual = *inicio;
            while(atual->proximo != NULL)
                atual = atual->proximo;
            atual->proximo = novo;
        }

        (*qtd)++;
        if(*qtd >= MAX) break;
    }

    fclose(arquivo);
    printf(VERDE "\n%d produto(s) carregado(s) com sucesso!\n" RESET, *qtd);
}

/* =========================================================
   Liberar toda a lista da memoria
   ========================================================= */
/* Libera toda a memoria percorrendo e dando free em cada no */
void liberarLista(No **inicio)
{
    No *atual = *inicio;
    No *proximo;

    while(atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}
