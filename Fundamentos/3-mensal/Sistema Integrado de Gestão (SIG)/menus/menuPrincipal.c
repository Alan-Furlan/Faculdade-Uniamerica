#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/inputs.h"
#include "../models/sistema.h"
#include "../services/produto_service.h"
#include "../services/venda_service.h"
#include "../services/caixa_service.h"


void menuPrincipal(sqlite3 *db, Sistema *sistema) {
    int opc;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Abrir Caixa\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Vender Produto\n");
        printf("4. Relatório de Vendas\n");
        printf("5. Lista de Produtos Vendidos\n");
        printf("6. Fechar Caixa\n");
        printf("7. Sair\n");

        lerInteiro(&opc);

        switch (opc){
            case 1:
                abrirCaixa(sistema);
                break;
            case 2:
                cadastrarProduto(sistema, db);
                break;
            case 3:
                venderProduto(sistema);
                break;
            case 4:
                relatorioVendas(sistema);
                break;
            case 5:
                listarProdutosVendidos(sistema);
                break;
            case 6:
                fecharCaixa(sistema);
                break;  
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }

    }while(opc != 7);
}