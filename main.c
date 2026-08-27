#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char palavra[46];
    int ocorrencias;
}Palavra;

typedef struct{
    int TABLE_SIZE, qtd;
    Palavra **itens;
}Hash;

int contar_palavras(char *nome_arq){
    FILE *arquivo = fopen(nome_arq, "r");
    if(!arquivo){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
   
    char palavra[46];
    int n_palavras = 0;
    while(fscanf(arquivo,"%45s",palavra)==1){
        n_palavras++;
    }
   
    fclose(arquivo);
    return n_palavras;
}

Hash *cria_hash(int TABLE_SIZE){
    Hash *h = malloc(sizeof(Hash));
    int i;
    h->qtd = 0;
    h->TABLE_SIZE = TABLE_SIZE;
    h->itens = malloc(TABLE_SIZE*sizeof(Palavra*));
    for(i=0; i<TABLE_SIZE; i++){
        h->itens[i] = NULL;
    }
    return h;
}

int gera_hash(char *chave, int TABLE_SIZE){
    int i, hash = 0;
    int len_chave = strlen(chave);
    for(i=0; i<len_chave; i++){
        hash = hash + chave[i];
    }
    return hash%TABLE_SIZE;
}

void inserir_na_tabela(char *nome_arq, Hash *h){
    FILE *arquivo = fopen(nome_arq, "r");
    if(!arquivo){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
   
    char chave[46];
    while(fscanf(arquivo,"%45s",chave)==1){
        int hash = gera_hash(chave,h->TABLE_SIZE), i = 0;
        while(i!=h->TABLE_SIZE){
            if(h->itens[hash]==NULL){
                h->itens[hash] = malloc(sizeof(Palavra));
                strcpy(h->itens[hash]->palavra,chave);
                h->itens[hash]->ocorrencias = 1;
                h->qtd++;
                break;
            }
            else if(strcmp(h->itens[hash]->palavra,chave)==0){
                h->itens[hash]->ocorrencias++;
                break;
            }
            else{
                hash = (hash+1) % h->TABLE_SIZE;
                i++;
            }
        }
    }
   
    fclose(arquivo);
}

Palavra *cria_vetor(Hash *h){
    Palavra *v = malloc((h->qtd)*sizeof(Palavra));
    int i, posicao = 0;
    for(i=0; i<h->TABLE_SIZE; i++){
        if(h->itens[i]!=NULL){
            strcpy(v[posicao].palavra,h->itens[i]->palavra);
            v[posicao].ocorrencias = h->itens[i]->ocorrencias;
            posicao++;
        }
    }
    return v;
}

Palavra *merge_ocorrencias(Palavra *v1, int t1, Palavra *v2, int t2){
    Palavra *novo = malloc((t1+t2)*sizeof(Palavra));
    int i=0, j=0, k=0;
        while(i<t1 && j<t2){
            if(v1[i].ocorrencias<v2[j].ocorrencias){
                novo[k++] = v1[i++];
            }
            else{
                novo[k++] = v2[j++];
            }
        }
        while(i<t1){
            novo[k++] = v1[i++];
        }
        while(j<t2){
            novo[k++] = v2[j++];
        }
        return novo;
}

Palavra *merge_alfabetico(Palavra *v1, int t1, Palavra *v2, int t2){
    Palavra *novo = malloc((t1+t2)*sizeof(Palavra));
    int i=0, j=0, k=0;
        while(i<t1 && j<t2){
            if(strcmp(v1[i].palavra,v2[j].palavra)<0){
                novo[k++] = v1[i++];
            }
            else{
                novo[k++] = v2[j++];
            }
        }
        while(i<t1){
            novo[k++] = v1[i++];
        }
        while(j<t2){
            novo[k++] = v2[j++];
        }
        return novo;
}

void mergesort_ocorrencias(Palavra *v, int inicio, int fim){
    if(inicio<fim){
        int meio = (inicio+fim)/2;
        mergesort_ocorrencias(v,inicio,meio);
        mergesort_ocorrencias(v,meio+1,fim);
        Palavra *novo = merge_ocorrencias(v+inicio, meio-inicio+1, v+meio+1, fim-meio);
        int i;
        for(i=0; i<=fim-inicio; i++){
            strcpy(v[inicio+i].palavra,novo[i].palavra);
            v[inicio+i].ocorrencias = novo[i].ocorrencias;
        }
        free(novo);
    }
}

void mergesort_alfabetico(Palavra *v, int inicio, int fim){
    if(inicio<fim){
        int meio = (inicio+fim)/2;
        mergesort_alfabetico(v,inicio,meio);
        mergesort_alfabetico(v,meio+1,fim);
        Palavra *novo = merge_alfabetico(v+inicio, meio-inicio+1, v+meio+1, fim-meio);
        int i;
        for(i=0; i<=fim-inicio; i++){
            strcpy(v[inicio+i].palavra,novo[i].palavra);
            v[inicio+i].ocorrencias = novo[i].ocorrencias;
        }
        free(novo);
    }
}

int consulta_ocorrencias(Hash *h, char *chave){
    int hash = gera_hash(chave,h->TABLE_SIZE), i = 0;
    while(i!=h->TABLE_SIZE){
        if(h->itens[hash] != NULL && strcmp(h->itens[hash]->palavra,chave)==0){
            return h->itens[hash]->ocorrencias;
        }
        else{
            hash = (hash+1) % h->TABLE_SIZE;
            i++;
        }
    }
    return -1;
}

void print_crescente_ou_alfabetico(Hash *h, Palavra *v){
    int i;
    for(i=0; i<h->qtd; i++){
        printf("%s: %i ocorrencias\n", v[i].palavra, v[i].ocorrencias);
    }
}

void print_decrescente(Hash *h, Palavra *v){
    int i;
    for(i=h->qtd-1; i>=0; i--){
        printf("%s: %i ocorrencias\n", v[i].palavra, v[i].ocorrencias);
    }
}

void print_letra(Hash *h, Palavra *v, char letra){
    int i, j = 0;
    for(i=0; i<h->qtd; i++){
        if(v[i].palavra[0]==letra){
            printf("%s: %i ocorrencias\n", v[i].palavra, v[i].ocorrencias);
            j++;
        }
    }
    if(j==0){
        printf("Nenhuma palavra iniciada por essa letra esta  presente no arquivo.\n");
    }
}

int main()
{
    char nome_arq[256];
    printf("Informe o nome ou caminho completo do arquivo: ");
    scanf(" %[^\n]", nome_arq);
   
    int n_palavras = contar_palavras(nome_arq);
    Hash *h = cria_hash(2*n_palavras);
    inserir_na_tabela(nome_arq,h);
   
    Palavra *vetor_ocorrencias = cria_vetor(h);
    Palavra *vetor_alfabetico = cria_vetor(h);
    mergesort_ocorrencias(vetor_ocorrencias,0,h->qtd-1);
    mergesort_alfabetico(vetor_alfabetico,0,h->qtd-1);
   
    int opcao = 0;
    while(opcao!=6){
        printf("1 - Consultar o numero de ocorrencias de uma palavra\n");
        printf("2 - Listar as palavras em ordem crescente\n");
        printf("3 - Listar as palavras em ordem decrescente\n");
        printf("4 - Listar as palavras em ordem alfabetica\n");
        printf("5 - Listar as palavras iniciadas por determinada letra\n");
        printf("6 - Encerrar o programa\n");
        printf("Selecione uma opcao: ");
        scanf("%i", &opcao);
       
        if(opcao==1){
           char palavra[46];
           printf("Digite uma palavra: ");
           scanf("%s", palavra);
           int n_ocorrencias = consulta_ocorrencias(h,palavra);
           if(n_ocorrencias==-1){
               printf("A palavra nao esta presente no arquivo.\n");
           }
           else{
               printf("Numero de ocorrencias: %i\n", n_ocorrencias);
           }
        }
        else if(opcao==2){
           print_crescente_ou_alfabetico(h,vetor_ocorrencias);
        }
        else if(opcao==3){
           print_decrescente(h,vetor_ocorrencias);
        }
        else if(opcao==4){
           print_crescente_ou_alfabetico(h,vetor_alfabetico);
        }
        else if(opcao==5){
           char letra;
           printf("Digite uma letra: ");
           scanf(" %c", &letra);
           print_letra(h,vetor_ocorrencias,letra);
        }
    }
    int i;
    for(i=0; i<h->TABLE_SIZE; i++){
        if(h->itens[i] != NULL){
            free(h->itens[i]);
        }
    }
    free(h->itens);
    free(h);
    free(vetor_ocorrencias);
    free(vetor_alfabetico);
}
