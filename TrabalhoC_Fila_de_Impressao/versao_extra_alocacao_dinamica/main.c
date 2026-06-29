#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "fila.h"
#include "arquivo.h"

void cadastrarTrabalho(FilaNormal *fn, FilaPrioridade *fp);
void processarTrabalho(FilaNormal *fn, FilaPrioridade *fp);

int main()
{
    FilaNormal    filaNormal;
    FilaPrioridade filaPrioridade;

    iniciarFilaNormal(&filaNormal);
    iniciarFilaPrioridade(&filaPrioridade);

    carregarCSV(&filaNormal, &filaPrioridade);

    int opcao, id;

    do
    {
        printf(CIANO "\n====================================" RESET);
        printf(NEGRITO "\n   SISTEMA DE FILA DE IMPRESSAO" RESET);
        printf(CIANO "\n====================================" RESET);
        printf("\n1 - Cadastrar Trabalho");
        printf("\n2 - Processar Impressao");
        printf("\n3 - Buscar Trabalho");
        printf("\n4 - Listar Fila Normal");
        printf("\n5 - Listar Fila Prioritaria");
        printf("\n6 - Cancelar Trabalho");
        printf("\n7 - Salvar CSV");
        printf("\n8 - Carregar CSV");
        printf("\n0 - Sair");
        printf("\n\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                cadastrarTrabalho(&filaNormal, &filaPrioridade);
                break;

            case 2:
                processarTrabalho(&filaNormal, &filaPrioridade);
                break;

            case 3:
                printf("\nInforme o ID: ");
                scanf("%d", &id);
                if(!buscarPrioridade(&filaPrioridade, id))
                {
                    if(!buscarNormal(&filaNormal, id))
                        printf(VERMELHO "\nTrabalho nao encontrado!\n" RESET);
                }
                break;

            case 4:
                listarFilaNormal(&filaNormal);
                break;

            case 5:
                listarFilaPrioridade(&filaPrioridade);
                break;

            case 6:
                printf("\nInforme o ID: ");
                scanf("%d", &id);
                if(cancelarPrioridade(&filaPrioridade, id))
                    printf(VERDE "\nTrabalho cancelado!\n" RESET);
                else if(cancelarNormal(&filaNormal, id))
                    printf(VERDE "\nTrabalho cancelado!\n" RESET);
                else
                    printf(VERMELHO "\nID nao encontrado!\n" RESET);
                break;

            case 7:
                salvarCSV(&filaNormal, &filaPrioridade);
                break;

            case 8:
                carregarCSV(&filaNormal, &filaPrioridade);
                break;

            case 0:
                salvarCSV(&filaNormal, &filaPrioridade);
                liberarFilaNormal(&filaNormal);
                liberarFilaPrioridade(&filaPrioridade);
                printf(VERDE "\nPrograma encerrado.\n" RESET);
                break;

            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

    } while(opcao != 0);

    return 0;
}

/* =============================================
   Cadastrar Trabalho
   ============================================= */
void cadastrarTrabalho(FilaNormal *fn, FilaPrioridade *fp)
{
    int id, paginas;
    char nomeArquivo[100];
    char tipo;

    do
    {
        printf("ID: ");
        scanf("%d", &id);
        if(id <= 0)
            printf(VERMELHO "ID invalido!\n" RESET);
    } while(id <= 0);

    /* Nao permite cadastrar um ID que ja esta em alguma fila */
    if(idExiste(fn, fp, id))
    {
        printf(VERMELHO "\nJa existe um trabalho com esse ID!\n" RESET);
        return;
    }

    printf("Nome do arquivo: ");
    scanf(" %[^\n]", nomeArquivo);

    do
    {
        printf("Quantidade de paginas: ");
        scanf("%d", &paginas);
        if(paginas <= 0)
            printf(VERMELHO "Digite um numero maior que zero!\n" RESET);
    } while(paginas <= 0);

    do
    {
        printf("Tipo (N/P): ");
        scanf(" %c", &tipo);
        tipo = toupper(tipo);
    } while(tipo != 'N' && tipo != 'P');

    if(tipo == 'P')
    {
        inserirPrioridade(fp, id, nomeArquivo, paginas, tipo);
        printf(VERDE "\nTrabalho prioritario cadastrado!\n" RESET);
    }
    else
    {
        inserirNormal(fn, id, nomeArquivo, paginas, tipo);
        printf(VERDE "\nTrabalho normal cadastrado!\n" RESET);
    }
}

/* =============================================
   Processar Trabalho
   ============================================= */
void processarTrabalho(FilaNormal *fn, FilaPrioridade *fp)
{
    No *t = NULL;

    if(!filaPrioridadeVazia(fp))
        t = removerPrioridade(fp);
    else if(!filaNormalVazia(fn))
        t = removerNormal(fn);

    if(t == NULL)
    {
        printf(AMARELO "\nNao existem trabalhos para imprimir.\n" RESET);
        return;
    }

    printf(CIANO "\n==============================" RESET);
    printf(NEGRITO "\n IMPRIMINDO TRABALHO" RESET);
    printf(CIANO "\n==============================" RESET);
    printf("\nID: %d",       t->id);
    printf("\nArquivo: %s",  t->nomeArquivo);
    printf("\nPaginas: %d",  t->paginas);
    printf("\nTipo: %c",     t->tipo);
    printf(VERDE "\n\nImpressao concluida!\n" RESET);

    free(t);
}
