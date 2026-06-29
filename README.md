# Trabalho Pratico - Estruturas de Dados

## Integrantes

| Nome | Matricula |
|------|-----------|
| Mateus Santos de Sousa Bastos | 2250202356 |
| Fabio Henrique Medeiros Telles | 2250104970 |
| Luiz Otavio Britto Sales Santos | 2250104925 |
| Thalisson Gabriel Santos Nascimento | 2250201859 |

**Turma:** Matutino  
**Curso:** Sistemas de Informacao

---

## Temas Escolhidos

| Trabalho | Tema |
|----------|------|
| Trabalho A - Lista Simples | A2 - Controle de Estoque |
| Trabalho B - Pilha Simples | B2 - Chamadas de Emergencia |
| Trabalho C - Fila Simples | C2 - Fila de Impressao |

---

## Descricao de Cada Programa

**Trabalho A - Controle de Estoque:** programa que gerencia produtos de um estoque usando lista simples com vetor de struct. A lista fica sempre ordenada pelo codigo do produto. Permite inserir, buscar, editar, excluir e listar produtos, alem de mostrar estatisticas e buscar por parte do nome. Os dados sao salvos no arquivo estoque.csv.

**Trabalho B - Chamadas de Emergencia:** programa que simula uma pilha de chamadas de emergencia seguindo a logica LIFO, onde a ultima chamada registrada e a primeira a ser atendida. Permite registrar, atender, consultar a ultima chamada, listar e gerar um relatorio. Os dados sao salvos no arquivo chamadas.csv.

**Trabalho C - Fila de Impressao:** programa que simula uma fila de impressao com trabalhos normais e prioritarios. Usa uma fila normal simples e uma fila circular simples para os prioritarios. Trabalhos prioritarios sao processados antes dos normais. Permite cadastrar, processar, buscar, listar e cancelar trabalhos. Os dados sao salvos no arquivo trabalhos.csv.

---

## Estrutura das Pastas

```
├── README.md                               → este arquivo
├── RELATORIO.md                            → relatorio do trabalho
├── main_integrador.c                       → menu unico que chama os tres trabalhos
│
├── TrabalhoA_Lista_Controle_de_Estoque/
│   ├── versao_obrigatoria_vetor/
│   │   ├── estoque.c
│   │   └── estoque.csv
│   └── versao_extra_alocacao_dinamica/
│       ├── estoque.h
│       ├── estoque.c
│       └── main.c
│
├── TrabalhoB_Pilha_Chamadas_de_Emergencia/
│   ├── versao_obrigatoria_vetor/
│   │   ├── emergencia.c
│   │   └── chamadas.csv
│   └── versao_extra_alocacao_dinamica/
│       ├── emergencia.h
│       ├── emergencia.c
│       └── main.c
│
└── TrabalhoC_Fila_de_Impressao/
    ├── versao_obrigatoria_vetor/
    │   ├── fila.h
    │   ├── fila.c
    │   ├── arquivo.h
    │   ├── arquivo.c
    │   ├── main.c
    │   └── trabalhos.csv
    └── versao_extra_alocacao_dinamica/
        ├── fila.h
        ├── fila.c
        ├── arquivo.h
        ├── arquivo.c
        └── main.c
```

---

## Como Compilar

Todos os programas usam o padrao C99. Para compilar, abra o terminal dentro da pasta de cada versao e use o GCC.

### Trabalho A - Controle de Estoque

```
# Versao obrigatoria - vetor
cd TrabalhoA_Lista_Controle_de_Estoque/versao_obrigatoria_vetor/
gcc -std=c99 -Wall -pedantic estoque.c -o estoque

# Versao extra - alocacao dinamica
cd TrabalhoA_Lista_Controle_de_Estoque/versao_extra_alocacao_dinamica/
gcc -std=c99 -Wall -pedantic main.c estoque.c -o estoque
```

### Trabalho B - Chamadas de Emergencia

```
# Versao obrigatoria - vetor
cd TrabalhoB_Pilha_Chamadas_de_Emergencia/versao_obrigatoria_vetor/
gcc -std=c99 -Wall -pedantic emergencia.c -o emergencia

# Versao extra - alocacao dinamica
cd TrabalhoB_Pilha_Chamadas_de_Emergencia/versao_extra_alocacao_dinamica/
gcc -std=c99 -Wall -pedantic main.c emergencia.c -o emergencia
```

### Trabalho C - Fila de Impressao

```
# Versao obrigatoria - vetor
cd TrabalhoC_Fila_de_Impressao/versao_obrigatoria_vetor/
gcc -std=c99 -Wall -pedantic main.c fila.c arquivo.c -o impressao

# Versao extra - alocacao dinamica
cd TrabalhoC_Fila_de_Impressao/versao_extra_alocacao_dinamica/
gcc -std=c99 -Wall -pedantic main.c fila.c arquivo.c -o impressao
```

---

## Como Executar

Depois de compilar, rode o executavel gerado dentro da pasta:

```
# Linux ou Mac
./estoque
./emergencia
./impressao

# Windows
estoque
emergencia
impressao
```

---

## Observacoes sobre o Funcionamento

- Cada programa carrega o arquivo CSV automaticamente ao iniciar. Se o arquivo ainda nao existir, o programa avisa e continua normalmente.
- Ao sair pela opcao do menu, os dados sao salvos automaticamente no CSV.
- O separador usado nos arquivos CSV e o ponto e virgula, com cabecalho na primeira linha.
- Cada um dos tres programas pode ser compilado, executado e avaliado de forma independente.

---

## Dificuldades Encontradas

As principais dificuldades foram a leitura correta dos campos no arquivo CSV, o controle dos indices na fila circular do Trabalho C e o gerenciamento dos ponteiros na versao extra com alocacao dinamica. O detalhamento completo esta no arquivo RELATORIO.md.
