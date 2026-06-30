#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <sqlite3.h>
#include "produto.h"
#include "widgets.h"

typedef struct {
    sqlite3  *db;
    Widgets  *gtk;

    int caixaAberto;             
    double valorInicialCaixa;         
    int caixa_qtd_itens_vendidos;  
    double caixa_faturamento_acumulado;
} Sistema;


#endif