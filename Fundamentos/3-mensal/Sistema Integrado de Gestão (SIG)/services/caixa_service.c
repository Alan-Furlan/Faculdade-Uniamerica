#include <stdio.h>
#include <stdlib.h>
#include "../models/sistema.h"
#include "../utils/inputs.h"
void abrirCaixa(Sistema *sistema) {
    if(sistema->caixaAberto){
            printf("O caixa já esta aberto!\n");
            return;
    }
    printf("\nCaixa aberto!\n");
    printf("Digite o valor inicial do caixa: ");
    lerFloat(&sistema->valorInicialCaixa);
    sistema->caixaAberto = 1;
}


void fecharCaixa(Sistema *sistema){
    if(!sistema->caixaAberto){
        printf("O caixa já esta fechado!\n");
        return;
    }

    float faturamento = 0;
    for(int i = 0; i < sistema->qtdVendasC; i++){
        faturamento += sistema->venda[i].quantidade * sistema->venda[i].preco;
    }

    printf("\n===== FECHAMENTO DE CAIXA =====\n");
    printf("Faturamento bruto: %.2f\n", faturamento);
    printf("Valor inicial do caixa: %.2f\n", sistema->valorInicialCaixa);
    printf("Valor total em caixa: %.2f\n",faturamento + sistema->valorInicialCaixa);
    printf("Caixa fechado!\n");
    printf("==============================\n");

    free(sistema->venda);

    sistema->venda = NULL;

    sistema->qtdVendasC = 0;
    sistema->tamanhoV = 0;
    
    sistema->valorInicialCaixa = 0;
    sistema->caixaAberto = 0;
}