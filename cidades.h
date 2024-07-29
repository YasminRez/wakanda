#ifndef ESTRADA_H
#define ESTRADA_H

typedef struct {
    char Nome[256]; // Nome da cidade
    int Posicao;    // Posição da cidade
} Cidade;

typedef struct {
    int N;      // Número de cidades
    int T;      // Comprimento da estrada
    Cidade *C;  // Vetor de cidades
} Estrada;

// Protótipos das funções
Estrada *getEstrada(const char *NomeArquivo);
double calcularMenorVizinhanca(const char *nomeArquivo); // Retorna a menor vizinhança.
char *cidadeMenorVizinhanca(const char *nomeArquivo);

#endif