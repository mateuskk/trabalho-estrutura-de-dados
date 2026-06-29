# Relatorio do Trabalho Pratico - Estruturas de Dados

**Disciplina:** Estruturas de Dados  
**Curso:** Sistemas de Informacao  
**Turma:** Matutino

---

## Integrantes

| Nome | Matricula |
|------|-----------|
| Mateus Santos de Sousa Bastos | 2250202356 |
| Fabio Henrique Medeiros Telles | 2250104970 |
| Luiz Otavio Britto Sales Santos | 2250104925 |
| Thalisson Gabriel Santos Nascimento | 2250201859 |

---

## Temas Escolhidos

| Trabalho | Tema | Estrutura |
|----------|------|-----------|
| Trabalho A | A2 - Controle de Estoque | Lista simples ordenada por codigo |
| Trabalho B | B2 - Chamadas de Emergencia | Pilha simples LIFO |
| Trabalho C | C2 - Fila de Impressao | Fila normal + fila circular com prioridade |

---

## 1. Introducao

Este trabalho foi dividido em tres programas independentes feitos em C, cada um trabalhando uma estrutura de dados diferente vista na disciplina. A ideia foi juntar tudo o que aprendemos na pratica: struct, vetores, funcoes, menus, validacao de entrada, leitura e gravacao de arquivos.

Cada um dos tres programas tem um menu interativo, valida o que o usuario digita e salva os dados num arquivo CSV para nao perder nada quando o programa fecha. Alem do que era obrigatorio, fizemos algumas coisas a mais, como cores no terminal, separacao do codigo em arquivos .h e .c, e uma segunda versao de cada trabalho usando alocacao dinamica com ponteiros.

---

## 2. Escolha dos Temas

### Trabalho A - Controle de Estoque

Escolhemos o controle de estoque porque e algo facil de imaginar funcionando no mundo real. Isso ajudou bastante na hora de pensar quais funcoes o programa precisava ter e como testar cada uma. Outro ponto que pesou foi a regra de manter a lista sempre ordenada pelo codigo do produto, que serviu bem como exercicio de insercao ordenada, em vez de so jogar tudo no fim do vetor.

### Trabalho B - Chamadas de Emergencia

A pilha de emergencia foi escolhida porque o comportamento dela combina com o tema. Numa pilha, o ultimo item que entra e o primeiro a sair, e isso encaixa com a ideia de atender primeiro a chamada mais recente. Como a logica do tema e simples, conseguimos focar em entender bem o funcionamento do topo, do push e do pop sem complicar demais.

### Trabalho C - Fila de Impressao

A fila de impressao foi escolhida porque ela usa dois tipos de fila ao mesmo tempo no mesmo programa: uma fila normal e uma fila circular com prioridade. Isso deu pra praticar os dois jeitos de fazer fila e entender na pratica a diferenca entre elas. Ter dois tipos de trabalho, normal e prioritario, tambem deixou os testes mais interessantes.

---

## 3. Decisoes de Implementacao

### Versao Obrigatoria - com vetor

Na versao obrigatoria usamos vetor de struct junto com variaveis de controle, do jeito que foi pedido. As principais decisoes foram:

- **Trabalho A:** a insercao caminha pelo vetor ate achar o lugar certo do codigo e empurra os outros elementos pra frente pra abrir espaco. Assim a lista fica sempre ordenada.
- **Trabalho B:** o topo comeca em -1 e sobe a cada nova chamada. Quando atende, o programa mostra os dados do topo e so depois desce o topo. Uma variavel separada conta quantas chamadas ja foram atendidas.
- **Trabalho C:** a fila normal usa um vetor simples e desloca os elementos quando alguem sai. A fila com prioridade usa vetor circular com inicio, fim e quantidade, pra nao desperdicar espaco no vetor.
- Os tres programas carregam o CSV sozinhos ao abrir e salvam sozinhos ao sair.
- O separador do CSV e o ponto e virgula, com o cabecalho na primeira linha, como pede a especificacao.

### Versao Extra - com alocacao dinamica

Na versao extra refizemos os tres trabalhos usando malloc, free e nos encadeados. As decisoes foram:

- Cada registro virou um no com um ponteiro apontando pro proximo. Com isso o programa nao tem mais o limite fixo do vetor.
- No Trabalho A, a lista encadeada continua ordenada por codigo. A insercao caminha pelos nos ate achar a posicao certa.
- No Trabalho B, a pilha encadeada sempre insere e remove no inicio da lista, que funciona como topo.
- No Trabalho C, as duas filas usam ponteiros de inicio e fim pra inserir no fim e remover do comeco, sem precisar de indice circular.
- Quando o programa fecha, uma funcao passa por todos os nos e da free em cada um, pra nao deixar memoria perdida.
- Toda vez que usamos malloc, verificamos se ele nao retornou NULL antes de continuar.

---

## 4. Dificuldades Encontradas

### Leitura do CSV

A parte de ler o CSV deu trabalho por causa do formato. Campos de texto que tem espaco precisavam de um cuidado especial na leitura pra nao parar no espaco errado. Testamos varios jeitos ate achar o formato que lia todos os campos certinho.

### Fila circular

Entender os indices da fila circular levou um tempo. O calculo que faz o indice voltar pro comeco do vetor parece simples, mas na pratica tivemos que testar bem os casos de fila cheia, fila vazia e quando sobra so um elemento. A variavel de quantidade foi importante pra saber a diferenca entre fila cheia e vazia, ja que nos dois casos o inicio e o fim podem apontar pro mesmo lugar.

### Ponteiros na versao extra

A maior dificuldade do extra foi controlar os ponteiros direito, principalmente quando o no era o primeiro da lista, ou quando sobrava so um elemento. Qualquer erro nessas horas quebrava o programa. O que resolveu foi testar cada operacao sozinha antes de juntar tudo.

### Compilar no padrao C99

Compilar com as flags mais rigorosas do C99 obrigou a declarar todas as variaveis no comeco dos blocos. Foi um ajuste pequeno, mas necessario pra deixar o codigo compilando limpo, sem nenhum aviso.

---

## 5. Extras Implementados

### Extras Gerais

- Cores no terminal: erros em vermelho, sucesso em verde, menus em destaque.
- Codigo separado em arquivos .h e .c.
- Estatisticas e busca por parte do nome no Trabalho A.
- Relatorio de chamadas atendidas no Trabalho B.
- Confirmacao antes de excluir no Trabalho A.
- Validacao de todas as entradas digitadas.
- Um arquivo main_integrador.c que junta os tres trabalhos num menu so.

### Extra com Alocacao Dinamica

- Os tres trabalhos tem uma versao extra usando malloc, free e nos encadeados.
- Ponteiros tratados com cuidado, incluindo o caso de NULL.
- Toda a memoria e liberada quando o programa fecha.

---

## 6. Conclusao

O trabalho cumpriu tudo que era obrigatorio e ainda foi um pouco alem com os extras. Testamos cada programa nos casos mais comuns: estrutura vazia, estrutura cheia, chave repetida, insercao em posicoes diferentes, salvar e abrir o CSV de novo.

Fazer o trabalho em C ajudou a fixar varios pontos importantes, como cuidar da memoria na mao, usar ponteiros do jeito certo, organizar o codigo em modulos e mexer com arquivos. A parte de alocacao dinamica foi a que mais deu trabalho, mas tambem foi a que mais ensinou.
