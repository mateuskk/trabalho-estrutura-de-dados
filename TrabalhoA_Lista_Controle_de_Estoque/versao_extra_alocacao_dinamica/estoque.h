#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== Cores ANSI ===== */
#define RESET   "\033[0m"
#define VERDE   "\033[1;32m"
#define AMARELO "\033[1;33m"
#define CIANO   "\033[1;36m"
#define VERMELHO "\033[1;31m"
#define NEGRITO "\033[1m"

#define MAX 100

/* ===== Struct do Produto ===== */
typedef struct No
{
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct No *proximo;
} No;

/* ===== Prototipos ===== */
No *criarNo(int codigo, char *nome, int quantidade, float preco);
void inserirProduto(No **inicio, int *qtd);
void listarProdutos(No *inicio);
void buscarProduto(No *inicio);
void editarProduto(No *inicio);
void excluirProduto(No **inicio, int *qtd);
void buscarPorNome(No *inicio);
void estatisticas(No *inicio, int qtd);
void salvarCSV(No *inicio);
void carregarCSV(No **inicio, int *qtd);
void liberarLista(No **inicio);

#endif
