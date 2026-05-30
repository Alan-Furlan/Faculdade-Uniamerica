#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/inputs.h"
#include "../models/sistema.h"
#include "../services/produto_service.h"

void venderProduto(Sistema *sistema) {
    do{
        if(!sistema->caixaAberto){
            printf("O caixa está fechado!\n");
            break;
        }
        int opcMP;

        do{
            printf("\n===== VENDER PRODUTO =====\n");
            printf("1. Mercado \n2. Padaria \n0. Voltar \n");
            printf("Escolha uma opção: ");
            lerInteiro(&opcMP);

        }while(opcMP != 1 && opcMP != 2 && opcMP != 0);
        if(opcMP == 0) break;
    
        int qtdPEncontrados = 0;
        for(int i = 0; i < sistema->qtdProdutosC; i++){

            if(sistema->produto[i].tipo == opcMP && sistema->produto[i].estoque > 0){
                printf("id: %d | nome: %s | preço: %.2f| estoque: %d\n", sistema->produto[i].id, sistema->produto[i].nome, sistema->produto[i].preco, sistema->produto[i].estoque);

                qtdPEncontrados++;
            }
        }

        if(qtdPEncontrados == 0){
            printf("Nenhum produto encontrado :(\n");
            continue;
        }

        int opcPId;
        Produto produtoEncontrado;

        do{
            printf("Digite o ID do produto: ");
            lerInteiro(&opcPId);

            produtoEncontrado = findById(sistema->produto, opcPId, sistema->qtdProdutosC);

            if(produtoEncontrado.id == -1 || produtoEncontrado.tipo != opcMP || produtoEncontrado.estoque <= 0){
                printf("Produto não encontrado!\n");
                continue;
            }

            int qtd = 0;

            do{
                printf("Escolha a quantidade: ");
                lerInteiro(&qtd);

                if(qtd > produtoEncontrado.estoque){
                    printf("O estoque possui apenas %d.\n", produtoEncontrado.estoque);
                }else{
                    sistema->produto[produtoEncontrado.id - 1].estoque -= qtd;
                    
                    if(sistema->qtdVendasC == sistema->tamanhoV){
                        sistema->tamanhoV++;

                        Venda *temp = realloc(sistema->venda, sistema->tamanhoV * sizeof(Venda));

                        if(temp == NULL){
                            free(temp);
                            printf("Erro ao alocar memória!\n");
                            return;
                        }

                        sistema->venda = temp;
                    }

                    Venda novaVenda;

                    novaVenda.id = sistema->qtdVendasC;
                    novaVenda.idDoProduto = produtoEncontrado.id;
                    novaVenda.quantidade = qtd;
                    novaVenda.preco = produtoEncontrado.preco;

                    
                    sistema->venda[sistema->qtdVendasC] = novaVenda;

                    sistema->qtdVendasC++;

                    printf("Venda realizada com sucesso!\n");
                    break;
                }
            }while(1);

            break;

        }while(1);

    }while(1);
}

void relatorioVendas(Sistema *sistema){
    printf("\n===== RELATÓRIO DE VENDAS =====\n");
    if(sistema->qtdVendasC == 0){
        printf("Nenhuma venda realizada.\n");
        printf("--------------------------------\n");
        return;
    }

    for(int i = 0; i < sistema->qtdVendasC; i++){
        Venda venda = sistema->venda[i];
        Produto produto = findById(sistema->produto, venda.idDoProduto, sistema->qtdProdutosC);

        printf("ID da Venda: %d | Produto: %s | Quantidade: %d | Preço Unitario: %.2f | Total: %.2f\n",
            venda.id,
            produto.nome,
            venda.quantidade,
            venda.preco,
            venda.quantidade * venda.preco
        );
    };
    printf("--------------------------------\n");
}


void listarProdutosVendidos(Sistema *sistema){

    printf("\n===== LISTA DE PRODUTOS VENDIDOS =====\n");

    if(sistema->qtdVendasC == 0){
        printf("Nenhuma venda realizada.\n");
        printf("--------------------------------\n");
        return;
    }

    Venda *vendasOrdenadas = malloc(sistema->qtdVendasC * sizeof(Venda));

    if(vendasOrdenadas == NULL){
        printf("Erro de memória\n");
        return;
    }

    for(int i = 0; i < sistema->qtdVendasC; i++){
        vendasOrdenadas[i] = sistema->venda[i];
    }

    for(int i = 0; i < sistema->qtdVendasC - 1; i++){

        for(int j = 0; j < sistema->qtdVendasC - 1 - i; j++){

            float total1 = vendasOrdenadas[j].quantidade * vendasOrdenadas[j].preco;

            float total2 = vendasOrdenadas[j + 1].quantidade * vendasOrdenadas[j + 1].preco;

            if(total1 < total2){

                Venda temp = vendasOrdenadas[j];

                vendasOrdenadas[j] = vendasOrdenadas[j + 1];

                vendasOrdenadas[j + 1] = temp;
            }
        }
    }

    for(int i = 0; i < sistema->qtdVendasC; i++){

        Venda venda = vendasOrdenadas[i];

        Produto produto = findById(
            sistema->produto,
            venda.idDoProduto,
            sistema->qtdProdutosC
        );

        float total = venda.quantidade * venda.preco;

        printf(
            "Produto: %s | Quantidade: %d | Preco Unitário: %.2f | Total: %.2f\n",
            produto.nome,
            venda.quantidade,
            venda.preco,
            total
        );
    }

    printf("--------------------------------\n");

    free(vendasOrdenadas);
}