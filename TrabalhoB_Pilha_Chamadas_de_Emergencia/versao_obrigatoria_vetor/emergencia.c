#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Registro;

Registro pilha[MAX];
int topo = -1;
int atendidas = 0;

/* Verifica se a pilha esta cheia */
int pilhaCheia() {
    return topo == MAX - 1;
}

/* Verifica se a pilha esta vazia */
int pilhaVazia() {
    return topo == -1;
}

/* Verifica se ja existe um registro com esse protocolo */
int protocoloExiste(int protocolo) {
    int i;
    for(i = 0; i <= topo; i++) {
        if(pilha[i].protocolo == protocolo)
            return 1;
    }
    return 0;
}

/* Registra uma nova chamada no topo da pilha */
void push() {

    if(pilhaCheia()) {
        printf("\nPilha cheia!\n");
        return;
    }

    Registro novo;

    printf("\nProtocolo: ");
    scanf("%d", &novo.protocolo);

    if(protocoloExiste(novo.protocolo)) {
        printf("Protocolo ja existente!\n");
        return;
    }

    getchar();

    printf("Local: ");
    fgets(novo.local, 50, stdin);
    novo.local[strcspn(novo.local, "\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, 30, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Horario: ");
    fgets(novo.horario, 20, stdin);
    novo.horario[strcspn(novo.horario, "\n")] = 0;

    topo++;
    pilha[topo] = novo;

    printf("\nChamada registrada com sucesso!\n");
}

/* Atende a chamada do topo e remove da pilha */
void pop() {

    if(pilhaVazia()) {
        printf("\nPilha vazia!\n");
        return;
    }

    printf("\nChamada atendida:\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Horario: %s\n", pilha[topo].horario);

    topo--;
    atendidas++;
}

/* Mostra a chamada do topo sem remover */
void peek() {

    if(pilhaVazia()) {
        printf("\nPilha vazia!\n");
        return;
    }

    printf("\nUltima chamada:\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Horario: %s\n", pilha[topo].horario);
}

/* Lista todas as chamadas do topo ate a base */
void listar() {

    int i;

    if(pilhaVazia()) {
        printf("\nPilha vazia!\n");
        return;
    }

    printf("\n===== PILHA =====\n");

    for(i = topo; i >= 0; i--) {
        printf("\nProtocolo: %d\n", pilha[i].protocolo);
        printf("Local: %s\n", pilha[i].local);
        printf("Tipo: %s\n", pilha[i].tipo);
        printf("Horario: %s\n", pilha[i].horario);
    }
}

/* Salva a pilha no CSV da base pro topo pra preservar a ordem ao carregar */
void salvarCSV() {

    FILE *arquivo = fopen("chamadas.csv", "w");
    int i;

    if(arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    fprintf(arquivo, "protocolo;local;tipo;horario\n");

    for(i = 0; i <= topo; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                pilha[i].protocolo,
                pilha[i].local,
                pilha[i].tipo,
                pilha[i].horario);
    }

    fclose(arquivo);
    printf("\nArquivo salvo com sucesso!\n");
}

/* Carrega as chamadas do CSV e reconstroi a pilha */
void carregarCSV() {

    FILE *arquivo = fopen("chamadas.csv", "r");
    char linha[200];

    if(arquivo == NULL) {
        printf("\nArquivo nao encontrado.\n");
        return;
    }

    topo = -1;

    /* Ignora o cabecalho */
    fgets(linha, sizeof(linha), arquivo);

    while(fgets(linha, sizeof(linha), arquivo) != NULL) {

        Registro r;

        if(sscanf(linha, "%d;%49[^;];%29[^;];%19[^\n]",
               &r.protocolo,
               r.local,
               r.tipo,
               r.horario) == 4)
        {
            if(!pilhaCheia() && !protocoloExiste(r.protocolo)) {
                topo++;
                pilha[topo] = r;
            }
        }
    }

    fclose(arquivo);
    printf("\nDados carregados com sucesso!\n");
}

/* Mostra quantas chamadas estao na pilha e quantas ja foram atendidas */
void relatorio() {

    printf("\n===== RELATORIO =====\n");
    printf("Chamadas na pilha: %d\n", topo + 1);
    printf("Chamadas atendidas: %d\n", atendidas);
}

int main() {

    int op;

    carregarCSV();

    do {
        printf("\n============================");
        printf("\n PILHA DE EMERGENCIA");
        printf("\n============================");
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

        switch(op) {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: listar(); break;
            case 5: salvarCSV(); break;
            case 6: carregarCSV(); break;
            case 7: relatorio(); break;
            case 0:
                salvarCSV();
                printf("\nPrograma encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

    } while(op != 0);

    return 0;
}
