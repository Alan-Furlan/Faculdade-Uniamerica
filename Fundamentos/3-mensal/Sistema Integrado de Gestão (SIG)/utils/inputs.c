#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limparBuffer() {
    while(getchar() != '\n');
}

void lerInteiro(int *num) {
    while(scanf("%d", num) != 1) {
        printf("Entrada inválida! Digite um número inteiro: ");
        limparBuffer();
    }
}

void lerFloat(float *num) {
    while(scanf("%f", num) != 1) {
        printf("Entrada inválida! Digite um número válido: ");
        limparBuffer();
    }
}

void lerString(char *str, int tamanho) {
    limparBuffer();
    fgets(str, tamanho, stdin);
    str[strcspn(str,"\n")] = '\0';
}

void lerChar(char *charr){
    while(scanf("%c", charr ) != 1) {
        printf("Entrada inválida! Digite reposta válida: ");
        limparBuffer();
    }
}
