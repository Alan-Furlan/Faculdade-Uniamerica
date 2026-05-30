#ifndef SISTEMA_H
#define SISTEMA_H

#include "produto.h"
#include "venda.h"

typedef struct {
    Produto *produto;
    int qtdProdutosC;
    int tamanhoP;

    Venda *venda;
    int qtdVendasC;
    int tamanhoV;

    float valorInicialCaixa;
    int caixaAberto;
} Sistema;
#endif