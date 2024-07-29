#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"


void ordenarCidades(Estrada *estrada) {
    //quicksort
    for (int i = 0; i < estrada->N; i++) {
        int minIndex = i;

        for (int j = i + 1; j < estrada->N; j++) {
            if (estrada->C[j].Posicao < estrada->C[minIndex].Posicao) {
                minIndex = j;
            }
        }

        Cidade temp = estrada->C[minIndex];
        estrada->C[minIndex] = estrada->C[i];
        estrada->C[i] = temp;
    }
}

void ordenarCidades(int *E, int N) {
    //quicksort
    for (int i = 0; i < N; i++) {
        int minIndex = i;

        for (int j = i + 1; j < N; j++) {
            if (E[j] < E[minIndex]) {
                minIndex = j;
            }
        }

        int temp = E[minIndex];
        E[minIndex] = E[i];
        E[i] = temp;
    }
}


void calcularDivisas(Estrada *estrada, double *pontoDivisa, double *areaCidade) {
    //calculo quantidade de divisas
    int numDivisas = estrada->N - 1; 
    //posicoes das divisas e calculo media
    for (int i = 0; i < numDivisas; i++) {
        pontoDivisa[i] = ((double)(estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2); 
    }

    areaCidade[0] = pontoDivisa[0]; 
    int finalEstrada = estrada->T; 
    for (int i = 1; i < estrada->N; i++) {
        if (i + 1 == estrada->N) {

            areaCidade[i] = finalEstrada - pontoDivisa[i - 1];
        } else {
        
            areaCidade[i] = pontoDivisa[i] - pontoDivisa[i - 1];
        }
    }
}

// leitura do arquivo
Estrada *getEstrada(const char *NomeArquivo) {
    FILE *arquivo;
    arquivo = fopen(NomeArquivo, "r");

    if (arquivo == NULL) {
        printf("ERRO Verifique se o arquivo esta correto\n\n");
        exit(1);
    }

    Estrada *x = (Estrada *)malloc(sizeof(Estrada));

    if (x == NULL) {
        printf("ERRO nao foi possivel alocar memoria.\n");
        exit(1);
    }

    fscanf(arquivo, "%d\n", &x->T);
    fscanf(arquivo, "%d\n", &x->N);

    x->C = malloc(x->N * sizeof(Cidade));

    if (x->C == NULL) {
        printf("ERRO nao foi possivel alocar memoria para array de cidades.\n");
        exit(1);
    }

    int i = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d %[^#]#", &x->C[i].Posicao, &x->C[i].Nome);

        if (x->C[i].Posicao < 0 || x->C[i].Posicao > x->T) {
            printf("ERRO distancia da fronteira incompativel.\n");
            exit(1);
        }

        if (i > 0 && x->C[i].Posicao == x->C[i - 1].Posicao) {
            printf("ERRO Restricao cidade possui Xi = Xj.\n");
            exit(1);
        }

        i++;
    }

    if (i < 1 || i > x->N) {
        printf("ERRO numero de cidades lidas nao condiz com a quantidade de cidades.\n");
        exit(1);
    }

    // Chama a função para ordenar as cidades
    ordenarCidades(x);

    fclose(arquivo);

    return x;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);

    int numeroDeDivisas = estrada->N - 1;
    double posicaoDivisa[numeroDeDivisas];
    double areaCidade[estrada->N];

    // Chama a funçao para calcular as divisas
    calcularDivisas(estrada, posicaoDivisa, areaCidade);

    // Encontrar a menor vizinhança
    double menorVizinhanca = areaCidade[0];
    for (int i = 0; i < estrada->N; i++) {
        if (areaCidade[i] < menorVizinhanca) {
            menorVizinhanca = areaCidade[i];
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    char *nomeMenorCidade = NULL;

    // Encontra a cidade com a menor vizinhança
    for (int i = 0; i < estrada->N; i++) {
        double posiDivisaAntes = (i == 0) ? 0 : ((double)(estrada->C[i - 1].Posicao + estrada->C[i].Posicao) / 2);
        double posiDivisaFrente = (i == estrada->N - 1) ? estrada->T : ((double)(estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2);
        double tamanhoCidade = posiDivisaFrente - posiDivisaAntes;

        if (tamanhoCidade == menorVizinhanca) {
            nomeMenorCidade = strdup(estrada->C[i].Nome);
            break;
        }
    }

    free(estrada->C);
    free(estrada);

    return nomeMenorCidade;
}
