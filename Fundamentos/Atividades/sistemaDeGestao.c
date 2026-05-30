#include <stdio.h>

#define MAX_REGISTROS 100

typedef struct {
    char nome[50];
    int tipo; 
} Registro;

Registro banco[MAX_REGISTROS];
int totalRegistros = 0;

void cadastrar() {
    printf("---------------------------------\n");
    printf("Cadastro de Cliente ou Fornecedor\n");
    printf("Escolha 1 para Cliente e 2 para Fornecedor: ");
    int tipo;
    scanf("%d", &tipo);
    if (tipo != 1 && tipo != 2) {
        printf("Tipo invalido. Retornando ao menu.\n");
        menu();
        return;
    } else if(totalRegistros >= MAX_REGISTROS) {
        printf("Limite de registros atingido. Nao e possivel cadastrar mais.\n");
        menu();
        return;
    }
    printf("Digite o nome: ");
    scanf(" %s", banco[totalRegistros].nome);
    banco[totalRegistros].tipo = tipo;

    totalRegistros++;
    printf("Cadastro realizado com sucesso!\n");
    printf("---------------------------------\n");
    menu();
}


void listar(int i, int filtro) {
    if (i >= totalRegistros) return;

    if (filtro == 0 || banco[i].tipo == filtro) {

        if(banco[i].tipo == 1) {
            printf("Cliente: %s\n", banco[i].nome);
        } else if(banco[i].tipo == 2) {
            printf("Fornecedor: %s\n", banco[i].nome);
        }
    }

    listar(i + 1, filtro);
}

void menu() {
    printf("\n--- Sistema de Gestão ---\n");
    printf("1- Cadastrar\n");
    printf("2- Listar Clientes\n");
    printf("3- Listar Fornecedores\n");
    printf("4- Listar Todos\n");
    printf("5- Sair\n");
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        cadastrar();
        menu();
        break;
    case 2:
        listar(0, 1);
        menu();
        break;
    case 3:
        listar(0, 2);
        menu();
        break;
    case 4:
        listar(0, 0);
        menu();
        break;
    case 5:
        printf("Saindo...\n");
        return 0;
        break;
    default:
        printf("Opcao invalida. Tente novamente.\n");
        menu();
        break;
    }

}

int main(){
    menu();
    return 0;
}