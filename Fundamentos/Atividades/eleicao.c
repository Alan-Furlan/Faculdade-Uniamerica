#include <stdio.h>

int main(){
    int num1 = 0, num2 = 0, num3 = 0 ,nulo = 0, branco = 0;

    for(int i = 0; i < 20; i++){
        printf("vote em um dos candidatos: \n");
        printf("0 - voto em branco \n");
        printf("1 - candidato 1 \n");
        printf("2 - candidato 2 \n");
        printf("3 - candidato 3 \n");
        printf("4 - voto nulo \n");

        printf("cartão %d, Digite o numero do candidato: \n", i + 1);
        int voto;

        int resultado = scanf("%d", &voto);

        while (resultado != 1) {
            printf("Entrada inválida! Digite um número inteiro: ");
            
            while (getchar() != '\n');
            resultado = scanf("%d", &voto);
        }

        switch (voto){
            case 0:
                branco++;
                break;
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                nulo++;
                break;
            default:
                printf("voto invalido \n");
                i--;
                break;
        }
    }

    if(num1 > num2 && num1 > num3){
        printf("O candidato 1 venceu com %d votos \n", num1);
    } else if(num2 > num1 && num2 > num3){
        printf("O candidato 2 venceu com %d votos \n", num2);
        
    } else if(num3 > num1 && num3 > num2){
        printf("O candidato 3 venceu com %d votos \n", num3);
    } else {
        printf("Houve um empate entre os candidatos \n");
    }
    printf("Votos para o candidato 1: %d \n", num1);
    printf("Votos para o candidato 2: %d \n", num2);
    printf("Votos para o candidato 3: %d \n", num3);
    printf("Votos em branco: %d \n", branco);
    printf("Votos nulos: %d \n", nulo);
    printf("Total de votos: %d \n", num1 + num2 + num3 + branco + nulo);
}