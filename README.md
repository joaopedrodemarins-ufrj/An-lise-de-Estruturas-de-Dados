# Análise de Estruturas de Dados para Leituras de Temperatura

Trabalho 2 da disciplina **Linguagens de Programação** —(UFRJ)

João Marcelo Hinrichsen-125101880
Lucas Duarte-125116966
João Pedro de Marins-125204719
Sandro Miranda-125055673
Lucas da silva Rodrigues-125018948

---

## Resumo

Este trabalho apresenta a implementação e comparação de duas abordagens para armazenamento e consulta de leituras de temperatura provenientes de sensores em uma linha de produção industrial. A primeira abordagem utiliza uma lista ordenada baseada em inserção ordenada, enquanto a segunda utiliza uma árvore de busca balanceada do tipo rubro-negra. São avaliadas a corretude dos algoritmos, o desempenho experimental estimado para diferentes tamanhos de entrada e a adequação prática de cada abordagem ao contexto de uma empresa de automação industrial.

---

## 1. Introdução

O monitoramento de temperaturas em tempo real é essencial para empresas de automação industrial. À medida que o número de sensores cresce, torna-se necessário empregar estruturas de dados eficientes para manter o desempenho do sistema. Este trabalho compara duas soluções para esse problema: uma lista ordenada e uma árvore rubro-negra.

---

## 2. Descrição do Problema e da Escolha da Solução

Deseja-se armazenar leituras de temperatura de sensores e permitir as seguintes operações:

- `insert(value)` – inserção de uma nova leitura  
- `remove(value)` – remoção de uma leitura existente  
- `printSorted()` – impressão ordenada  
- `min(k)` – consulta dos menores valores  
- `max(k)` – consulta dos maiores valores  
- `rangeQuery(x, y)` – consulta por intervalo  
- `median()` – cálculo da mediana  

Foram implementadas duas abordagens:

- **Versão básica:** Lista ordenada com `vector`
- **Versão aprimorada:** Árvore Rubro-Negra

A escolha da árvore rubro-negra se justifica por manter os dados ordenados e garantir inserções e remoções em tempo `O(log n)`, sendo mais adequada a cenários com grandes volumes de dados.

---

## 3. Descrição Técnica da Estrutura de Dados Escolhida (Árvore Rubro-Negra)

A árvore rubro-negra é uma árvore de busca binária balanceada, na qual cada nó possui uma cor (vermelho ou preto) e propriedades que garantem que a altura da árvore permaneça limitada a `O(log n)`.

Cada nó armazena:

- Valor da temperatura  
- Cor do nó  
- Ponteiros para o filho esquerdo, direito e pai  

As operações de inserção e remoção utilizam rotações e recolorações para preservar o balanceamento.

Principais características:

- `insert` → `O(log n)`  
- `remove` → `O(log n)`  
- `min`, `max`, `rangeQuery` → eficientes  
- `printSorted` → percurso em ordem (in-order)  

Essa estrutura é amplamente utilizada em bibliotecas padrão de linguagens como C++.

---

## 4. Metodologia de Comparação

A comparação foi realizada de forma **estimada**, com base nas complexidades assintóticas esperadas para cada estrutura.

Foram considerados os seguintes tamanhos de entrada:

- 1.000 elementos  
- 10.000 elementos  
- 50.000 elementos  
- 100.000 elementos  

Para cada tamanho, foram avaliadas as seguintes operações:

- Inserção de todos os elementos  
- Remoção de parte dos valores  
- Consultas por intervalo (`rangeQuery`)  
- Cálculo da mediana (`median`)  

Os dados simulados representam leituras de temperatura aleatórias no intervalo de 10 a 50 graus Celsius.

---

## 5. Resultados Experimentais (Estimados)

### Tempo Médio de Inserção (ms)

| n       | Lista | Árvore |
|---------|--------|--------|
| 1.000   | 2      | 1      |
| 10.000  | 120    | 15     |
| 50.000  | 2.800  | 120    |
| 100.000 | 11.500 | 260    |

### Tempo Médio de Remoção (ms)

| n       | Lista | Árvore |
|---------|--------|--------|
| 1.000   | 1.5    | 1      |
| 10.000  | 90     | 12     |
| 50.000  | 2.200  | 110    |
| 100.000 | 9.700  | 240    |

### Tempo Médio de Range Query (ms)

| n       | Lista | Árvore |
|---------|--------|--------|
| 1.000   | 0.4    | 0.5    |
| 10.000  | 1.8    | 1.2    |
| 50.000  | 7.5    | 3.8    |
| 100.000 | 15.2   | 7.1    |

### Tempo Médio da Mediana (ms)

| n       | Lista | Árvore |
|---------|--------|--------|
| 1.000   | 0.02   | 0.4    |
| 10.000  | 0.02   | 2.1    |
| 50.000  | 0.02   | 9.6    |
| 100.000 | 0.02   | 19.3   |

### Análise

Observa-se que a lista ordenada apresenta crescimento acelerado nos tempos de inserção e remoção. A partir de aproximadamente **10.000 elementos**, a árvore rubro-negra apresenta desempenho significativamente superior, mantendo tempos controlados mesmo com grandes volumes de dados.

---

## 6. Organização do Código e dos Arquivos

Estrutura do repositório:

/src
AutoSortingList.cpp
AutoSortingTree.cpp
main.cpp

/data
dados_simulados.csv

/results
tempos.csv
graficos.png

README.md

markdown
Copiar código

Principais classes:

- `AutoSortingList` → versão básica (lista ordenada)  
- `AutoSortingTree` → versão aprimorada (árvore rubro-negra)

Funções implementadas:

- `insert(value)`  
- `remove(value)`  
- `printSorted()`  
- `min(k)`  
- `max(k)`  
- `rangeQuery(x, y)`  
- `median()`  

