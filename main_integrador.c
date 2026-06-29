/*
 * main_integrador.c
 * Menu principal que integra os tres trabalhos em um so programa.
 *
 * Para compilar junto com os arquivos de cada trabalho:
 *
 * gcc -std=c99 -Wall -pedantic main_integrador.c \
 *     trabalhoA/estoque.c \
 *     trabalhoB/emergencia.c \
 *     trabalhoC/fila.c trabalhoC/arquivo.c \
 *     -o sistema
 */

#include <stdio.h>
#include <stdlib.h>

/* Cores ANSI */
#define RESET    "\033[0m"
#define VERDE    "\033[1;32m"
#define CIANO    "\033[1;36m"
#define VERMELHO "\033[1;31m"
#define NEGRITO  "\033[1m"

/* Prototipos dos menus de cada trabalho */
void menuEstoque(void);
void menuEmergencia(void);
void menuImpressao(void);

int main(void)
{
    int opcao;

    do
    {
        printf(CIANO "\n============================================" RESET);
        printf(NEGRITO "\n   SISTEMA DE ESTRUTURAS DE DADOS 2026.1" RESET);
        printf(CIANO "\n============================================" RESET);
        printf("\n1 - Controle de Estoque  (Lista Simples)");
        printf("\n2 - Pilha de Emergencia  (Pilha LIFO)");
        printf("\n3 - Fila de Impressao    (Fila FIFO + Circular)");
        printf("\n0 - Sair");
        printf(CIANO "\n============================================" RESET);
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                menuEstoque();
                break;

            case 2:
                menuEmergencia();
                break;

            case 3:
                menuImpressao();
                break;

            case 0:
                printf(VERDE "\nEncerrando o sistema. Ate logo!\n" RESET);
                break;

            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

    } while(opcao != 0);

    return 0;
}
