#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database/database.h"
#include "menus/menuPrincipal.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);

    Sistema sistema;
    sistema.produto = NULL;
    sistema.qtdProdutosC = 0;
    sistema.tamanhoP = 0;

    sistema.venda = NULL;
    sistema.qtdVendasC = 0;
    sistema.tamanhoV = 0;

    sistema.caixaAberto = 0;
    sistema.valorInicialCaixa = 0;

    sqlite3 *db = abrirBanco();
    if(db == NULL){
        return 1;
    }

    criarTabelaProdutos(db);
    carregarProdutos(db, &sistema);

    menuPrincipal(db, &sistema);

    free(sistema.produto);
    free(sistema.venda);
    sistema.produto = NULL;
    sistema.venda = NULL;

    fecharBanco(db);
}