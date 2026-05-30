#include <stdio.h>

void calculo(char op, float mA[3][3], float mB[3][3], float mC[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(op == '+')
                mC[i][j] = mA[i][j] + mB[i][j];
            else if(op == '-')
                mC[i][j] = mA[i][j] - mB[i][j];
            else if(op == '*')
                mC[i][j] = mA[i][j] * mB[i][j];
            else if(op == '/')
                 if(mB[i][j] == 0){
                    printf("\n Erro: divisao por zero em [%d][%d]\n", i, j);
                    mC[i][j] = 0; 
                 } else {
                    mC[i][j] = mA[i][j] / mB[i][j];
                 }
        }
    }
}

void print(char op, float mA[3][3], float mB[3][3], float mC[3][3]){
    printf("\nMatriz A     Matriz B     Resultado\n\n");

    for(int i = 0; i < 3; i++){

        
        for(int j = 0; j < 3; j++){
            printf("%5.1f ", mA[i][j]);
        }

        if(i == 1) printf(" %c ", op);
        else printf("   ");

        
        for(int j = 0; j < 3; j++){
            printf("%5.1f ", mB[i][j]);
        }

        if(i == 1) printf(" = ");
        else printf("   ");

        
        for(int j = 0; j < 3; j++){
            printf("%5.1f ", mC[i][j]);
        }

        printf("\n");
    }
}

int main(){
    int opcao = 0;
    int cadastrouMatriz = 0;

    float mA[3][3];
    float mB[3][3];
    float mC[3][3];

    do{
        printf("\n=== Menu ===\n");
        printf("1. Cadastrar Matrizes A e B\n");
        printf("2. Somar\n");
        printf("3. Subtrair\n");
        printf("4. Multiplicacar\n");
        printf("5. dividir\n");
        printf("6. Sair\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrouMatriz = 1;

            printf("\nMatriz A:\n");
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    printf("[%d][%d]: ", i, j);
                    scanf("%f", &mA[i][j]);
                }
            }

            printf("\nMatriz B:\n");
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    printf("[%d][%d]: ", i, j);
                    scanf("%f", &mB[i][j]);
                }
            }

            break;

        case 2:
            if(cadastrouMatriz){
                calculo('+', mA, mB, mC);
                print('+', mA, mB, mC);
            } else {
                printf("Cadastre as matrizes primeiro!\n");
            }
            break;

        case 3:
            if(cadastrouMatriz){
                calculo('-', mA, mB, mC);
                print('-', mA, mB, mC);
            } else {
                printf("Cadastre as matrizes primeiro!\n");
            }
            break;
        case 4:
            if(cadastrouMatriz){
                calculo('*', mA, mB, mC);
                print('*', mA, mB, mC);
            } else {
                printf("Cadastre as matrizes primeiro!\n");
            }
            break;
        case 5:
            if(cadastrouMatriz){
                calculo('/', mA, mB, mC);
                print('/', mA, mB, mC);
            } else {
                printf("Cadastre as matrizes primeiro!\n");
            }
            break;
        }
    }while(opcao != 6);

    return 0;
}