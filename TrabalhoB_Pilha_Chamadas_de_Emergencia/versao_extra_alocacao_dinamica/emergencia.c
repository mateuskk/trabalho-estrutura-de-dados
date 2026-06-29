#include "emergencia.h"

/* =========================================================
   Criar No
   ========================================================= */
/* Aloca e retorna um novo no com os dados da chamada */
No *criarNo(int protocolo, char *local, char *tipo, char *horario)
{
    No *novo = (No *)malloc(sizeof(No));

    if(novo == NULL)
    {
        printf(VERMELHO "\nErro ao alocar memoria!\n" RESET);
        return NULL;
    }

    novo->protocolo = protocolo;
    novo->proximo   = NULL;

    strncpy(novo->local,   local,   sizeof(novo->local)   - 1);
    strncpy(novo->tipo,    tipo,    sizeof(novo->tipo)    - 1);
    strncpy(novo->horario, horario, sizeof(novo->horario) - 1);

    novo->local[sizeof(novo->local)     - 1] = '\0';
    novo->tipo[sizeof(novo->tipo)       - 1] = '\0';
    novo->horario[sizeof(novo->horario) - 1] = '\0';

    return novo;
}

/* =========================================================
   Verificar se protocolo ja existe
   ========================================================= */
/* Verifica se ja existe um registro com esse protocolo */
int protocoloExiste(No *topo, int protocolo)
{
    No *atual = topo;

    while(atual != NULL)
    {
        if(atual->protocolo == protocolo)
            return 1;
        atual = atual->proximo;
    }

    return 0;
}

/* =========================================================
   Push - Registrar chamada (insere no topo)
   ========================================================= */
/* Registra uma nova chamada no topo da pilha encadeada */
void push(No **topo, int *total)
{
    int protocolo;
    char local[50], tipo[30], horario[20];

    printf("\nProtocolo: ");
    scanf("%d", &protocolo);

    if(protocoloExiste(*topo, protocolo))
    {
        printf(VERMELHO "Protocolo ja existente!\n" RESET);
        return;
    }

    getchar();

    printf("Local: ");
    fgets(local, sizeof(local), stdin);
    local[strcspn(local, "\n")] = '\0';

    printf("Tipo: ");
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    printf("Horario: ");
    fgets(horario, sizeof(horario), stdin);
    horario[strcspn(horario, "\n")] = '\0';

    No *novo = criarNo(protocolo, local, tipo, horario);
    if(novo == NULL) return;

    /* novo no aponta para o topo atual */
    novo->proximo = *topo;
    *topo = novo;
    (*total)++;

    printf(VERDE "\nChamada registrada com sucesso!\n" RESET);
}

/* =========================================================
   Pop - Atender chamada (remove do topo)
   ========================================================= */
/* Atende a chamada do topo, remove e libera a memoria */
void pop(No **topo, int *atendidas)
{
    if(*topo == NULL)
    {
        printf(VERMELHO "\nPilha vazia!\n" RESET);
        return;
    }

    No *remover = *topo;

    printf(CIANO "\nChamada atendida:\n" RESET);
    printf("Protocolo: %d\n", remover->protocolo);
    printf("Local: %s\n",     remover->local);
    printf("Tipo: %s\n",      remover->tipo);
    printf("Horario: %s\n",   remover->horario);

    *topo = remover->proximo;
    free(remover);
    (*atendidas)++;
}

/* =========================================================
   Peek - Consultar topo sem remover
   ========================================================= */
/* Mostra a chamada do topo sem remover */
void peek(No *topo)
{
    if(topo == NULL)
    {
        printf(VERMELHO "\nPilha vazia!\n" RESET);
        return;
    }

    printf(CIANO "\nUltima chamada:\n" RESET);
    printf("Protocolo: %d\n", topo->protocolo);
    printf("Local: %s\n",     topo->local);
    printf("Tipo: %s\n",      topo->tipo);
    printf("Horario: %s\n",   topo->horario);
}

/* =========================================================
   Listar todas as chamadas (topo para base)
   ========================================================= */
/* Lista todas as chamadas do topo ate a base */
void listar(No *topo)
{
    No *atual = topo;

    if(atual == NULL)
    {
        printf(VERMELHO "\nPilha vazia!\n" RESET);
        return;
    }

    printf(CIANO "\n===== PILHA =====" RESET "\n");

    while(atual != NULL)
    {
        printf("\nProtocolo: %d\n", atual->protocolo);
        printf("Local: %s\n",      atual->local);
        printf("Tipo: %s\n",       atual->tipo);
        printf("Horario: %s\n",    atual->horario);
        atual = atual->proximo;
    }
}

/* =========================================================
   Salvar CSV (da base para o topo para reconstruir correto)
   ========================================================= */
/* Salva a pilha no CSV da base pro topo pra preservar a ordem */
void salvarCSV(No *topo, int total)
{
    /* inverte em array para salvar da base para o topo */
    No **arr = (No **)malloc(total * sizeof(No *));
    int i = 0;
    No *atual = topo;
    FILE *arquivo;

    if(arr == NULL && total > 0)
    {
        printf(VERMELHO "\nErro ao alocar memoria para salvar!\n" RESET);
        return;
    }

    while(atual != NULL)
    {
        arr[i++] = atual;
        atual = atual->proximo;
    }

    arquivo = fopen("chamadas.csv", "w");

    if(arquivo == NULL)
    {
        printf(VERMELHO "Erro ao criar arquivo.\n" RESET);
        free(arr);
        return;
    }

    fprintf(arquivo, "protocolo;local;tipo;horario\n");

    /* salva da base (ultimo) para o topo (primeiro) */
    for(i = total - 1; i >= 0; i--)
    {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                arr[i]->protocolo,
                arr[i]->local,
                arr[i]->tipo,
                arr[i]->horario);
    }

    fclose(arquivo);
    free(arr);
    printf(VERDE "\nArquivo salvo com sucesso!\n" RESET);
}

/* =========================================================
   Carregar CSV
   ========================================================= */
/* Carrega as chamadas do CSV e reconstroi a pilha encadeada */
void carregarCSV(No **topo, int *total)
{
    FILE *arquivo = fopen("chamadas.csv", "r");
    char linha[200];

    if(arquivo == NULL)
    {
        printf(AMARELO "\nArquivo nao encontrado.\n" RESET);
        return;
    }

    liberarPilha(topo);
    *total = 0;

    /* ignora cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int protocolo;
        char local[50], tipo[30], horario[20];

        if(sscanf(linha, "%d;%49[^;];%29[^;];%19[^\n]",
                  &protocolo, local, tipo, horario) == 4)
        {
            if(!protocoloExiste(*topo, protocolo))
            {
                No *novo = criarNo(protocolo, local, tipo, horario);
                if(novo == NULL) continue;

                novo->proximo = *topo;
                *topo = novo;
                (*total)++;
            }
        }
    }

    fclose(arquivo);
    printf(VERDE "\nDados carregados com sucesso!\n" RESET);
}

/* =========================================================
   Relatorio
   ========================================================= */
/* Mostra quantas chamadas estao na pilha e quantas foram atendidas */
void relatorio(No *topo, int atendidas)
{
    No *atual = topo;
    int total = 0;

    while(atual != NULL)
    {
        total++;
        atual = atual->proximo;
    }

    printf(CIANO "\n===== RELATORIO =====" RESET "\n");
    printf("Chamadas na pilha : %d\n", total);
    printf("Chamadas atendidas: %d\n", atendidas);
}

/* =========================================================
   Liberar toda a pilha da memoria
   ========================================================= */
/* Libera toda a memoria percorrendo e dando free em cada no */
void liberarPilha(No **topo)
{
    No *atual = *topo;
    No *proximo;

    while(atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    *topo = NULL;
}
