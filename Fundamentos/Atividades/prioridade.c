#include <stdio.h>

void filtrarPrioridade(int processos[]) {
    int i;
    int maior = processos[0];
    int menor = processos[0];
    int diferenca;

    for (i = 1; i < 10; i++) {

        if (processos[i] > maior) {
            maior = processos[i];
        }

        if (processos[i] < menor) {
            menor = processos[i];
        }
    }

    diferenca = maior - menor;

    printf("\nMaior prioridade: %d\n", maior);
    printf("Menor prioridade: %d\n", menor);
    printf("Gap (diferenca): %d\n", diferenca);

    if (maior > 90) {
        printf("ALERTA: Processo Critico Detectado!\n");
    }
}

int main() {
    int processos[10];
    int i;

    printf("Digite 10 prioridades (1 a 100):\n");

    for (i = 0; i < 10; i++) {
        scanf("%d", &processos[i]);
    }

    filtrarPrioridade(processos);

    return 0;
}