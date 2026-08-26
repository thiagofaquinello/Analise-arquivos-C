# Processador de Arquivos e Frequência de Palavras em C

Projeto desenvolvido para a disciplina **CAC3202 - Algoritmos e Estruturas de Dados** do curso de Engenharia de Controle e Automação na Universidade Federal de Santa Catarina (UFSC Blumenau).

Consiste em um programa em linguagem C para leitura, sanitização e análise de frequência de palavras em arquivos de texto ASCII, respeitando limites específicos de complexidade algorítmica[cite: 1].

---

## Funcionalidades

O sistema processa o arquivo de texto e disponibiliza um menu com as opções[cite: 1]:

1. Consultar a quantidade de ocorrências de uma palavra[cite: 1].
2. Listar todas as palavras e frequências em ordem crescente de ocorrência[cite: 1].
3. Listar todas as palavras e frequências em ordem decrescente de ocorrência[cite: 1].
4. Listar todas as palavras e frequências em ordem alfabética[cite: 1].
5. Listar palavras que iniciam por um caractere específico em ordem crescente[cite: 1].
6. Encerrar o programa[cite: 1].

---

## Complexidade Computacional

Considerando $n$ como o número total de palavras no arquivo[cite: 1]:

- **Leitura e armazenamento do arquivo:** $O(n \log_2 n)$[cite: 1]
- **Consulta de ocorrência por palavra:** $O(1)$[cite: 1]
- **Listagens e ordenações (opções 2 a 5):** $O(n)$[cite: 1]

---

## Regras de Processamento

- **Sanitização:** Apenas letras são consideradas; pontuações e caracteres especiais são ignorados durante a leitura[cite: 1].
- **Formato:** Projetado para textos em padrão ASCII sem acentuação[cite: 1].

---

## Como Executar

1. Compile o arquivo fonte com o GCC:
   ```bash
   gcc main.c -o programa
   ```
