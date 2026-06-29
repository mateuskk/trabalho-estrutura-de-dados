#include <stdio.h>
#include <stdlib.h>
#include "estoque.h"

int main()
{
    No *inicio = NULL;
    int qtd    = 0;
    int opcao;

    carregarCSV(&inicio, &qtd);

    do
    {
        printf(CIANO "\n=========================================\n" RESET);
        printf(NEGRITO "        CONTROLE DE ESTOQUE\n" RESET);
        printf(CIANO "=========================================\n" RESET);
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
        printf(CIANO "=========================================\n" RESET);
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1: inserirProduto(&inicio, &qtd);  break;
            case 2: buscarProduto(inicio);           break;
            case 3: editarProduto(inicio);           break;
            case 4: excluirProduto(&inicio, &qtd);  break;
            case 5: listarProdutos(inicio);          break;
            case 6: salvarCSV(inicio);               break;
            case 7: buscarPorNome(inicio);           break;
            case 8: estatisticas(inicio, qtd);       break;
            case 9: carregarCSV(&inicio, &qtd);     break;
            case 0:
                salvarCSV(inicio);
                liberarLista(&inicio);
                printf(VERDE "\nPrograma encerrado.\n" RESET);
                break;
            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

    } while(opcao != 0);

    return 0;
}
