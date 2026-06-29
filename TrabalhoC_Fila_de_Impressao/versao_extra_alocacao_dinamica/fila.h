#ifndef FILA_H
#define FILA_H

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

/* ===== No da fila encadeada ===== */
typedef struct No
{
    int id;
    char nomeArquivo[100];
    int paginas;
    char tipo; /* N = Normal | P = Prioritario */
    struct No *proximo;
} No;

/* ===== Fila Normal (encadeada simples) ===== */
typedef struct
{
    No *inicio;
    No *fim;
    int quantidade;
} FilaNormal;

/* ===== Fila Prioritaria (encadeada simples) ===== */
typedef struct
{
    No *inicio;
    No *fim;
    int quantidade;
} FilaPrioridade;

/* ===== Prototipos ===== */
No *criarNo(int id, char *nomeArquivo, int paginas, char tipo);

void iniciarFilaNormal(FilaNormal *f);
void iniciarFilaPrioridade(FilaPrioridade *f);

int filaNormalVazia(FilaNormal *f);
int filaPrioridadeVazia(FilaPrioridade *f);

void inserirNormal(FilaNormal *f, int id, char *nome, int pag, char tipo);
void inserirPrioridade(FilaPrioridade *f, int id, char *nome, int pag, char tipo);

No *removerNormal(FilaNormal *f);
No *removerPrioridade(FilaPrioridade *f);

void listarFilaNormal(FilaNormal *f);
void listarFilaPrioridade(FilaPrioridade *f);

int buscarNormal(FilaNormal *f, int id);
int buscarPrioridade(FilaPrioridade *f, int id);

int idExiste(FilaNormal *fn, FilaPrioridade *fp, int id);

int cancelarNormal(FilaNormal *f, int id);
int cancelarPrioridade(FilaPrioridade *f, int id);

void liberarFilaNormal(FilaNormal *f);
void liberarFilaPrioridade(FilaPrioridade *f);

#endif
