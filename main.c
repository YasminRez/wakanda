#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main() {
    // Lê os dados da estrada do arquivo
    Estrada *T1 = getEstrada("cidades.txt");
    if (T1 == NULL) {
        printf("Erro ao ler dados da estrada.\n");
        return 1; // Saída com erro
    }

    // Calcula a menor vizinhança usando os dados lidos
    printf("Menor vizinhanca: %.2lf\n", calcularMenorVizinhanca(T1));

    // Encontra a cidade com a menor vizinhança usando os dados lidos
    char *menorCidade = cidadeMenorVizinhanca(T1);
    if (menorCidade != NULL) {
        printf("Cidade com menor vizinhanca: %s\n", menorCidade);
        free(menorCidade); // Libera a memória alocada para menorCidade
    } else {
        printf("Nenhuma cidade encontrada.\n");
    }

    // Libera a memória alocada para T1
    free(T1);

    return 0;
}
