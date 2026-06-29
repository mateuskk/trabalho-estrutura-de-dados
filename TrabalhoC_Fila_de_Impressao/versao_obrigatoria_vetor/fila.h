#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

/*==============================*/
/* Estrutura do Trabalho        */
/*==============================*/
typedef struct
{
    int id;
    char nomeArquivo[100];
    int paginas;
    char tipo; /* N = Normal | P = Prioritario */

} Trabalho;

/*==============================*/
/* Fila Normal (Simples)        */
/*==============================*/
typedef struct
{
    Trabalho dados[MAX];
    int quantidade;

} FilaNormal;

/*==============================*/
/* Fila Prioritaria (Circular)  */
/*==============================*/
typedef struct
{
    Trabalho dados[MAX];
    int inicio;
    int fim;
    int quantidade;

} FilaPrioridade;

/*==============================*/
/* Inicializacao                */
/*==============================*/
void iniciarFilaNormal(FilaNormal *f);
void iniciarFilaPrioridade(FilaPrioridade *f);

/*==============================*/
/* Verificacoes                 */
/*==============================*/
int filaNormalVazia(FilaNormal *f);
int filaNormalCheia(FilaNormal *f);
int filaPrioridadeVazia(FilaPrioridade *f);
int filaPrioridadeCheia(FilaPrioridade *f);

/*==============================*/
/* Insercao                     */
/*==============================*/
int inserirNormal(FilaNormal *f, Trabalho t);
int inserirPrioridade(FilaPrioridade *f, Trabalho t);

/*==============================*/
/* Remocao                      */
/*==============================*/
Trabalho removerNormal(FilaNormal *f);
Trabalho removerPrioridade(FilaPrioridade *f);

/*==============================*/
/* Listagem                     */
/*==============================*/
void listarFilaNormal(FilaNormal *f);
void listarFilaPrioridade(FilaPrioridade *f);

/*==============================*/
/* Busca                        */
/*==============================*/
int buscarNormal(FilaNormal *f, int id);
int buscarPrioridade(FilaPrioridade *f, int id);

/* Verifica se o ID ja existe em qualquer uma das duas filas */
int idExiste(FilaNormal *fn, FilaPrioridade *fp, int id);

/*==============================*/
/* Cancelamento                 */
/*==============================*/
int cancelarNormal(FilaNormal *f, int id);
int cancelarPrioridade(FilaPrioridade *f, int id);

#endif
