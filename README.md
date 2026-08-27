# Processador de Arquivos e Frequência de Palavras em C

Projeto desenvolvido para a disciplina **CAC3202 - Algoritmos e Estruturas de Dados** do curso de Engenharia de Controle e Automação na Universidade Federal de Santa Catarina (UFSC Blumenau).

Consiste em um programa em linguagem C para leitura, sanitização e análise de frequência de palavras em arquivos de texto ASCII, respeitando limites específicos de complexidade algorítmica.

---

## Funcionalidades

O sistema processa o arquivo de texto e disponibiliza um menu com as opções:

1. Consultar a quantidade de ocorrências de uma palavra.
2. Listar todas as palavras e frequências em ordem crescente de ocorrência.
3. Listar todas as palavras e frequências em ordem decrescente de ocorrência.
4. Listar todas as palavras e frequências em ordem alfabética.
5. Listar palavras que iniciam por um caractere específico em ordem crescente.
6. Encerrar o programa.

---

## Minha Contribuição

1. Implementação da leitura e processamento dos arquivos de entrada.
2. Organização e refatoração do código, reduzindo repetições e melhorando sua estrutura.
3. Participação na integração das diferentes partes do programa com outro integrante da equipe.
4. Participação na apresentação do projeto e explicação do funcionamento dos diferentes módulos do código.

---

## Complexidade Computacional

Considerando $n$ como o número total de palavras no arquivo:

- **Leitura e armazenamento do arquivo:** $O(n \log_2 n)$
- **Consulta de ocorrência por palavra:** $O(1)$
- **Listagens e ordenações (opções 2 a 5):** $O(n)$

---

## Regras de Processamento

- **Sanitização:** Apenas letras são consideradas; pontuações e caracteres especiais são ignorados durante a leitura.
- **Formato:** Projetado para textos em padrão ASCII sem acentuação.

---

## Como Executar

1. Compile o arquivo fonte com o GCC:
   ```bash
   gcc main.c -o programa
   ```
