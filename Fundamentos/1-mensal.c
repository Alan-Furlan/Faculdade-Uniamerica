
#include <stdio.h>

#include <stdlib.h>

int quantidadeVendas = 0;
int caixaLiberado = 1;
int opcao;
float valorDeAbertura = 0;
int opcaoProduto = 0;
int quantidadeDeProduto = 0;
int opcaoEscolhidaPeloMenu;
float valorTotalDasVendas = 0;
int produtoEscolhido;
float valorVendaAtual = 0;
int qtdVendaAtual = 0;
int verificaValores;

int menu()
{
    printf("\n--- Menu ---\n");
    printf("1 - Abrir caixa\n");
    printf("2 - Iniciar uma nova venda\n");
    printf("3 - Encerrar programa\n");
    while (scanf("%d", &opcaoEscolhidaPeloMenu) != 1 || opcaoEscolhidaPeloMenu < 1 || opcaoEscolhidaPeloMenu > 3)
    {
        printf("Entrada inválida! Digite um número válido: ");
        while (getchar() != '\n')
            ;
    }

    return opcaoEscolhidaPeloMenu;
}

void telaEscolhaQuantidade(float preco)
{
    printf("Quantidade: ");

    while (scanf("%d", &quantidadeDeProduto) != 1 || quantidadeDeProduto <= 0)
    {
        printf("Entrada inválida! Digite um número válido: ");

        while (getchar() != '\n')
            ;
    }

    qtdVendaAtual += quantidadeDeProduto;
    quantidadeVendas += quantidadeDeProduto;
    valorVendaAtual += preco * quantidadeDeProduto;
}

int telaEscolhaProduto()
{
    printf("\nValor parcial da venda: R$ %.2f\n", valorVendaAtual);
    printf("1 - Arroz - R$ 10,00\n");
    printf("2 - Feijao - R$ 8,00\n");
    printf("3 - Macarrao - R$ 5,00\n");
    printf("4 - Coca 2L - R$ 7,00\n");
    printf("5 - Leite 1L - R$ 6,00\n");
    printf("6 - Fechar venda\n");
    printf("Escolha um produto: ");

    while (scanf("%d", &opcaoProduto) != 1 || opcaoProduto < 1 || opcaoProduto > 6)
    {

        printf("Entrada inválida! Digite um número válido: ");

        while (getchar() != '\n')
            ;
    }

    return opcaoProduto;
}

int main()
{

    do
    {
        switch (menu())
        {

        case 1:
            if (caixaLiberado == 0)
            {

                printf("Caixa ja foi aberto com valor de abertura: R$ %.2f\n", valorDeAbertura);
            }
            else
            {
                printf("Informe o valor de abertura: R$ ");

                while (scanf("%f", &valorDeAbertura) != 1 || valorDeAbertura < 0)
                {

                    printf("Entrada inválida! Digite um número válido: ");

                    while (getchar() != '\n')
                        ;
                }

                caixaLiberado = 0;

                printf("Caixa aberto com sucesso!\n");
            }

            break;

        case 2:

            if (caixaLiberado == 1)
            {

                printf("Caixa fechado, por favor abra o caixa para iniciar a venda.\n");
            }
            else
            {

                valorVendaAtual = 0;

                qtdVendaAtual = 0;

                telaEscolhaProduto();

                while (opcaoProduto != 6)
                {

                    switch (opcaoProduto)
                    {

                    case 1:

                        printf("Produto escolhido: Arroz - R$ 10,00\n");

                        telaEscolhaQuantidade(10);

                        break;

                    case 2:

                        printf("Produto escolhido: Feijao - R$ 8,00\n");

                        telaEscolhaQuantidade(8);

                        break;

                    case 3:

                        printf("Produto escolhido: Macarrao - R$ 5,00\n");

                        telaEscolhaQuantidade(5);

                        break;

                    case 4:

                        printf("Produto escolhido: Coca 2L - R$ 7,00\n");

                        telaEscolhaQuantidade(7);

                        break;

                    case 5:

                        printf("Produto escolhido: Leite 1L - R$ 6,00\n");

                        telaEscolhaQuantidade(6);

                        break;

                    default:

                        printf("Produto invalido, por favor escolha um produto valido.\n");
                    }

                    telaEscolhaProduto();
                }

                valorTotalDasVendas += valorVendaAtual;

                printf("\n--- Venda Finalizada ---\n");

                printf("Total de itens nesta venda: %d\n", qtdVendaAtual);

                printf("Valor total da venda: R$ %.2f\n", valorVendaAtual);
            }

            break;

        case 3:

            printf("\n--- Encerrando programa ---\n");

            printf("Quantidade total de produtos vendidos: %d\n", quantidadeVendas);

            printf("Valor total faturado: R$ %.2f\n", valorTotalDasVendas);

            printf("Valor de abertura: R$ %.2f\n", valorDeAbertura);

            printf("Saldo final do caixa: R$ %.2f\n", valorTotalDasVendas + valorDeAbertura);

            break;

        default:

            printf("Opcao invalida, tente novamente.\n");
        }

    } while (opcaoEscolhidaPeloMenu != 3);

    return 0;
}