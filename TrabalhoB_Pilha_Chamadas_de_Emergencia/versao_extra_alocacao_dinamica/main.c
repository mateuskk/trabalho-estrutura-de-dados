#include <stdio.h>
#include <stdlib.h>
#include "emergencia.h"

int main()
{
    No *topo     = NULL;
    int atendidas = 0;
    int total     = 0;
    int op;

    carregarCSV(&topo, &total);

    do
    {
        printf(CIANO "\n============================" RESET);
        printf(NEGRITO "\n PILHA DE EMERGENCIA" RESET);
        printf(CIANO "\n============================" RESET);
        printf("\n1 - Registrar chamada");
        printf("\n2 - Atender chamada");
        printf("\n3 - Consultar ultima chamada");
        printf("\n4 - Listar chamadas");
        printf("\n5 - Salvar CSV");
        printf("\n6 - Carregar CSV");
        printf("\n7 - Relatorio");
        printf("\n0 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1: push(&topo, &total);          break;
            case 2: pop(&topo, &atendidas);        break;
            case 3: peek(topo);                    break;
            case 4: listar(topo);                  break;
            case 5: salvarCSV(topo, total);        break;
            case 6: carregarCSV(&topo, &total);    break;
            case 7: relatorio(topo, atendidas);    break;
            case 0:
                salvarCSV(topo, total);
                liberarPilha(&topo);
                printf(VERDE "\nPrograma encerrado.\n" RESET);
                break;
            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

    } while(op != 0);

    return 0;
}
