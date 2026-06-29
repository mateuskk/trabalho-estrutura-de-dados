#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "fila.h"
#include "arquivo.h"

void cadastrarTrabalho(FilaNormal *fn, FilaPrioridade *fp);
void processarTrabalho(FilaNormal *fn, FilaPrioridade *fp);

int main()
{
    FilaNormal filaNormal;
    FilaPrioridade filaPrioridade;

    iniciarFilaNormal(&filaNormal);
    iniciarFilaPrioridade(&filaPrioridade);

    carregarCSV(&filaNormal, &filaPrioridade);

    int opcao;
    int id;

    do
    {
        printf("\n====================================");
        printf("\n   SISTEMA DE FILA DE IMPRESSAO");
        printf("\n====================================");
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
                        printf("\nTrabalho nao encontrado!\n");
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
                    printf("\nTrabalho cancelado!\n");
                else if(cancelarNormal(&filaNormal, id))
                    printf("\nTrabalho cancelado!\n");
                else
                    printf("\nID nao encontrado!\n");
                break;

            case 7:
                salvarCSV(&filaNormal, &filaPrioridade);
                break;

            case 8:
                carregarCSV(&filaNormal, &filaPrioridade);
                break;

            case 0:
                salvarCSV(&filaNormal, &filaPrioridade);
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}

/* Pede os dados ao usuario e insere na fila correta pelo tipo */
void cadastrarTrabalho(FilaNormal *fn, FilaPrioridade *fp)
{
    Trabalho t;

    do
    {
        printf("ID: ");
        scanf("%d", &t.id);
        if(t.id <= 0)
            printf("ID invalido!\n");
    } while(t.id <= 0);

    /* Nao permite cadastrar um ID que ja esta em alguma fila */
    if(idExiste(fn, fp, t.id))
    {
        printf("\nJa existe um trabalho com esse ID!\n");
        return;
    }

    printf("Nome do arquivo: ");
    scanf(" %[^\n]", t.nomeArquivo);

    do
    {
        printf("Quantidade de paginas: ");
        scanf("%d", &t.paginas);
        if(t.paginas <= 0)
            printf("Digite um numero maior que zero!\n");
    } while(t.paginas <= 0);

    do
    {
        printf("Tipo (N/P): ");
        scanf(" %c", &t.tipo);
        t.tipo = toupper(t.tipo);
    } while(t.tipo != 'N' && t.tipo != 'P');

    if(t.tipo == 'P')
    {
        if(inserirPrioridade(fp, t))
            printf("\nTrabalho prioritario cadastrado!\n");
        else
            printf("\nFila prioritaria cheia!\n");
    }
    else
    {
        if(inserirNormal(fn, t))
            printf("\nTrabalho normal cadastrado!\n");
        else
            printf("\nFila normal cheia!\n");
    }
}

/* Processa o proximo trabalho: prioritarios saem primeiro */
void processarTrabalho(FilaNormal *fn, FilaPrioridade *fp)
{
    Trabalho t;

    if(!filaPrioridadeVazia(fp))
    {
        t = removerPrioridade(fp);

        printf("\n==============================");
        printf("\n IMPRIMINDO TRABALHO");
        printf("\n==============================");
        printf("\nID: %d", t.id);
        printf("\nArquivo: %s", t.nomeArquivo);
        printf("\nPaginas: %d", t.paginas);
        printf("\nTipo: %c", t.tipo);
        printf("\n\nImpressao concluida!\n");
        return;
    }

    if(!filaNormalVazia(fn))
    {
        t = removerNormal(fn);

        printf("\n==============================");
        printf("\n IMPRIMINDO TRABALHO");
        printf("\n==============================");
        printf("\nID: %d", t.id);
        printf("\nArquivo: %s", t.nomeArquivo);
        printf("\nPaginas: %d", t.paginas);
        printf("\nTipo: %c", t.tipo);
        printf("\n\nImpressao concluida!\n");
        return;
    }

    printf("\nNao existem trabalhos para imprimir.\n");
}
