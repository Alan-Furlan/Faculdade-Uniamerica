#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "../database/database.h"
#include "../utils/inputs.h"
#include "../utils/utils.h"
#include "../models/sistema.h"

void cadastrarProduto(Sistema *sistema, sqlite3 *db) {
    
    //realloc
    aumentarCapacidadeProdutos(sistema);

    do{
        printf("\n===== CADASTRAR PRODUTO =====\n");
        printf("1. Mercado \n2. Padaria \n0. Voltar \n");
        printf("Escolha uma opção: ");
        lerInteiro(&sistema->produto[sistema->qtdProdutosC].tipo);

    }while(sistema->produto[sistema->qtdProdutosC].tipo != 1 && sistema->produto[sistema->qtdProdutosC].tipo != 2 && sistema->produto[sistema->qtdProdutosC].tipo != 0);
    if(sistema->produto[sistema->qtdProdutosC].tipo == 0) return;
        
    printf("Escolha o nome do Produto: ");
    lerString(sistema->produto[sistema->qtdProdutosC].nome, 50);

    printf("Escolha o preço do Produto: ");
    lerFloat(&sistema->produto[sistema->qtdProdutosC].preco);

    printf("Quantidade no estoque: ");
    lerInteiro(&sistema->produto[sistema->qtdProdutosC].estoque);

    enviarProdutobanco(db, sistema->produto[sistema->qtdProdutosC]);

    sistema->produto[sistema->qtdProdutosC].id = sqlite3_last_insert_rowid(db);
    
    sistema->qtdProdutosC++;

    
    printf("Produto cadastrado\n");
}

Produto findById(Produto *produto, int id, int qtdProdutoC){
    Produto vazio;
    vazio.id = -1;
    vazio.tipo = -1;
    vazio.estoque = 0;  

    for(int i = 0; i < qtdProdutoC; i++){
        if(produto[i].id == id){
            return produto[i];
        }
    }

    return vazio;
}