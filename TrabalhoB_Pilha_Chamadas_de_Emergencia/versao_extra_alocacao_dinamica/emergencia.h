#ifndef EMERGENCIA_H
#define EMERGENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== Cores ANSI ===== */
#define RESET    "\033[0m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define CIANO    "\033[1;36m"
#define VERMELHO "\033[1;31m"
#define NEGRITO  "\033[1m"

/* ===== No da Pilha ===== */
typedef struct No
{
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
    struct No *proximo;
} No;

/* ===== Prototipos ===== */
No  *criarNo(int protocolo, char *local, char *tipo, char *horario);
int  protocoloExiste(No *topo, int protocolo);
void push(No **topo, int *total);
void pop(No **topo, int *atendidas);
void peek(No *topo);
void listar(No *topo);
void salvarCSV(No *topo, int total);
void carregarCSV(No **topo, int *total);
void relatorio(No *topo, int atendidas);
void liberarPilha(No **topo);

#endif
