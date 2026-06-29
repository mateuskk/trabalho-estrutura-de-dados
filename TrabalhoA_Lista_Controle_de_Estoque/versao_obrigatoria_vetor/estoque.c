#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto lista[MAX];
int quantidade = 0;

int buscarPosicao(int codigo);
void inserirProduto();
void listarProdutos();
void buscarProduto();
void editarProduto();
void excluirProduto();
void salvarCSV();
void carregarCSV();
void buscarPorNome();
void estatisticas();

/* Retorna a posicao do produto no vetor pelo codigo, ou -1 se nao encontrar */
int buscarPosicao(int codigo)
{
    int i;
    for(i = 0; i < quantidade; i++)
    {
        if(lista[i].codigo == codigo)
            return i;
    }
    return -1;
}

/* Insere um produto na lista mantendo a ordenacao por codigo */
void inserirProduto()
{
    Produto novo;
    int pos, i;

    if(quantidade >= MAX)
    {
        printf("\nLista cheia!\n");
        return;
    }

    printf("\nCodigo: ");
    scanf("%d", &novo.codigo);

    if(buscarPosicao(novo.codigo) != -1)
    {
        printf("\nJa existe um produto com esse codigo!\n");
        return;
    }

    getchar();

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    do
    {
        printf("Quantidade: ");
        scanf("%d", &novo.quantidade);
        if(novo.quantidade < 0)
            printf("Quantidade invalida! Digite novamente.\n");
    } while(novo.quantidade < 0);

    do
    {
        printf("Preco: ");
        scanf("%f", &novo.preco);
        if(novo.preco < 0)
            printf("Preco invalido! Digite novamente.\n");
    } while(novo.preco < 0);

    /* Acha a posicao correta pra manter ordenado */
    pos = 0;
    while(pos < quantidade && lista[pos].codigo < novo.codigo)
        pos++;

    /* Desloca os elementos pra abrir espaco */
    for(i = quantidade; i > pos; i--)
        lista[i] = lista[i - 1];

    lista[pos] = novo;
    quantidade++;

    printf("\nProduto cadastrado com sucesso!\n");
}

/* Lista todos os produtos cadastrados */
void listarProdutos()
{
    int i;

    if(quantidade == 0)
    {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n=========== LISTA DE PRODUTOS ===========\n");

    for(i = 0; i < quantidade; i++)
    {
        printf("\nProduto %d\n", i + 1);
        printf("Codigo.....: %d\n", lista[i].codigo);
        printf("Nome.......: %s\n", lista[i].nome);
        printf("Quantidade.: %d\n", lista[i].quantidade);
        printf("Preco......: R$ %.2f\n", lista[i].preco);
        printf("-----------------------------------------\n");
    }
}

/* Busca e exibe um produto pelo codigo */
void buscarProduto()
{
    int codigo, pos;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    pos = buscarPosicao(codigo);

    if(pos == -1)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    printf("\n========== PRODUTO ==========\n");
    printf("Codigo.....: %d\n", lista[pos].codigo);
    printf("Nome.......: %s\n", lista[pos].nome);
    printf("Quantidade.: %d\n", lista[pos].quantidade);
    printf("Preco......: R$ %.2f\n", lista[pos].preco);
}

/* Edita os dados de um produto existente */
void editarProduto()
{
    int codigo, pos;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    pos = buscarPosicao(codigo);

    if(pos == -1)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    getchar();

    printf("Novo nome: ");
    fgets(lista[pos].nome, sizeof(lista[pos].nome), stdin);
    lista[pos].nome[strcspn(lista[pos].nome, "\n")] = '\0';

    do
    {
        printf("Nova quantidade: ");
        scanf("%d", &lista[pos].quantidade);
        if(lista[pos].quantidade < 0)
            printf("Quantidade invalida!\n");
    } while(lista[pos].quantidade < 0);

    do
    {
        printf("Novo preco: ");
        scanf("%f", &lista[pos].preco);
        if(lista[pos].preco < 0)
            printf("Preco invalido!\n");
    } while(lista[pos].preco < 0);

    printf("\nProduto editado com sucesso!\n");
}

/* Exclui um produto com confirmacao do usuario */
void excluirProduto()
{
    int codigo, pos, i;
    char resposta;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    pos = buscarPosicao(codigo);

    if(pos == -1)
    {
        printf("\nProduto nao encontrado!\n");
        return;
    }

    printf("\nProduto encontrado:\n");
    printf("Codigo.....: %d\n", lista[pos].codigo);
    printf("Nome.......: %s\n", lista[pos].nome);

    printf("\nDeseja realmente excluir? (S/N): ");
    scanf(" %c", &resposta);

    if(resposta == 'S' || resposta == 's')
    {
        /* Desloca os elementos pra fechar o espaco */
        for(i = pos; i < quantidade - 1; i++)
            lista[i] = lista[i + 1];

        quantidade--;
        printf("\nProduto excluido com sucesso!\n");
    }
    else
    {
        printf("\nExclusao cancelada!\n");
    }
}

/* Busca produtos por parte do nome */
void buscarPorNome()
{
    char nome[50];
    int i, encontrou = 0;

    getchar();

    printf("\nDigite o nome ou parte do nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("\n========== RESULTADOS ==========\n");

    for(i = 0; i < quantidade; i++)
    {
        if(strstr(lista[i].nome, nome) != NULL)
        {
            encontrou = 1;
            printf("\nCodigo.....: %d\n", lista[i].codigo);
            printf("Nome.......: %s\n", lista[i].nome);
            printf("Quantidade.: %d\n", lista[i].quantidade);
            printf("Preco......: R$ %.2f\n", lista[i].preco);
            printf("---------------------------------\n");
        }
    }

    if(!encontrou)
        printf("\nNenhum produto encontrado!\n");
}

/* Mostra total de produtos, itens e valor do estoque */
void estatisticas()
{
    int i, totalQuantidade = 0;
    float valorTotal = 0;

    if(quantidade == 0)
    {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    for(i = 0; i < quantidade; i++)
    {
        totalQuantidade += lista[i].quantidade;
        valorTotal += lista[i].quantidade * lista[i].preco;
    }

    printf("\n========== ESTATISTICAS ==========\n");
    printf("Produtos cadastrados : %d\n", quantidade);
    printf("Itens em estoque.....: %d\n", totalQuantidade);
    printf("Valor total estoque..: R$ %.2f\n", valorTotal);
}

/* Salva todos os produtos no arquivo CSV */
void salvarCSV()
{
    FILE *arquivo;
    int i;

    arquivo = fopen("estoque.csv", "w");

    if(arquivo == NULL)
    {
        printf("\nErro ao criar o arquivo!\n");
        return;
    }

    fprintf(arquivo, "codigo;nome;quantidade;preco\n");

    for(i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "%d;%s;%d;%.2f\n",
                lista[i].codigo,
                lista[i].nome,
                lista[i].quantidade,
                lista[i].preco);
    }

    fclose(arquivo);
    printf("\nArquivo salvo com sucesso!\n");
}

/* Carrega os produtos do arquivo CSV, ignorando o cabecalho */
void carregarCSV()
{
    FILE *arquivo;
    char linha[200];

    arquivo = fopen("estoque.csv", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhum arquivo CSV encontrado.\n");
        return;
    }

    quantidade = 0;

    fgets(linha, sizeof(linha), arquivo);

    while(fscanf(arquivo, "%d;%49[^;];%d;%f\n",
                 &lista[quantidade].codigo,
                 lista[quantidade].nome,
                 &lista[quantidade].quantidade,
                 &lista[quantidade].preco) == 4)
    {
        quantidade++;
        if(quantidade >= MAX)
            break;
    }

    fclose(arquivo);
    printf("\n%d produto(s) carregado(s) com sucesso!\n", quantidade);
}

int main()
{
    int opcao;

    carregarCSV();

    do
    {
        printf("\n=========================================\n");
        printf("        CONTROLE DE ESTOQUE\n");
        printf("=========================================\n");
        printf("1 - Inserir produto\n");
        printf("2 - Buscar produto\n");
        printf("3 - Editar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Listar produtos\n");
        printf("6 - Salvar arquivo CSV\n");
        printf("7 - Buscar por nome\n");
        printf("8 - Estatisticas\n");
        printf("9 - Carregar arquivo CSV\n");
        printf("0 - Sair\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: inserirProduto(); break;
            case 2: buscarProduto(); break;
            case 3: editarProduto(); break;
            case 4: excluirProduto(); break;
            case 5: listarProdutos(); break;
            case 6: salvarCSV(); break;
            case 7: buscarPorNome(); break;
            case 8: estatisticas(); break;
            case 9: carregarCSV(); break;
            case 0:
                salvarCSV();
                printf("\nPrograma encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
