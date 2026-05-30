#include <stdio.h>
#include <string.h>

#define MAX_PESSOAS 50

typedef struct {
    char nome[30];
    char sobrenome[30];
    int idade;
    char sexo;
} Pessoa;

void lerEntrada(char str[], int tamanho) {
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0';
}


int main() {
    Pessoa listaDePessoas[MAX_PESSOAS];
    int opcao;
    int tamanhoLista = 0;
    do{
        printf("\n1. Cadastrar pessoa\n");
        printf("2. Listar pessoas\n");
        printf("3. Buscar por sobrenome\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            if(tamanhoLista >= MAX_PESSOAS){
                printf("Limite de pessoas atingido.\n");
                break;
            }
            printf("--- Cadastro de pessoa --- \n");
            getchar();
            printf("Digite o nome: ");
            lerEntrada(listaDePessoas[tamanhoLista].nome, 30);

            printf("Digite o sobrenome: ");
            lerEntrada(listaDePessoas[tamanhoLista].sobrenome, 30);
            printf("Digite a idade: ");
            scanf(" %d", &listaDePessoas[tamanhoLista].idade);
            printf("Digite o sexo (M/F): ");
            scanf(" %c", &listaDePessoas[tamanhoLista].sexo);
            tamanhoLista++;

            break;
        case 2:
            if(tamanhoLista == 0){
                printf("Nenhuma pessoa cadastrada.\n");
                break;
            }
            printf("--- Lista de pessoas --- \n");
            printf("NOME       | SOBRENOME       | IDADE | SEXO\n");
            for (int i = 0; i < tamanhoLista; i++)
            {
                printf("%-10s %-20s %-8d %-10c\n", listaDePessoas[i].nome, listaDePessoas[i].sobrenome, listaDePessoas[i].idade, listaDePessoas[i].sexo);
            }
            printf("---------------------- \n");

            break;
        case 3:
            if(tamanhoLista == 0){
                printf("Nenhuma pessoa cadastrada.\n");
                break;
            }
            printf("Digite o sobrenome para buscar: ");
            char sobrenomeBusca[30];
            getchar();
            lerEntrada(sobrenomeBusca, 30);
            printf("--- Pessoas com sobrenome '%s' --- \n", sobrenomeBusca);
            printf("NOME       | SOBRENOME       | IDADE | SEXO\n");

            for(int i = 0; i < tamanhoLista; i++){
                if(strcmp(listaDePessoas[i].sobrenome, sobrenomeBusca) == 0){
                    printf("%-10s %-20s %-8d %-10c\n", listaDePessoas[i].nome, listaDePessoas[i].sobrenome, listaDePessoas[i].idade, listaDePessoas[i].sexo);
                   
                }
            }
            printf("---------------------- \n");

        default:
            break;
        }
    }while (opcao != 0);
    
    return 0;
}