#include <stdio.h>

int corretas = 0;
int statusDeCadaQuestao[10];
char respostasCorretas[10] = {'A','C','B','A','B','C','A','A','C','B'};
char respostasDigitada[10];

int validar(char resp, char gabarito, int i){

    while(resp != 'A' && resp != 'a' && resp != 'B' && resp != 'b' && resp != 'C' && resp != 'c'){
        printf("Opção inválida!\n Digite (A) (B) (C): ");
        scanf(" %c", &resp);
        respostasDigitada[i] = resp;
    }
        
    if(gabarito == 'A') {
        if(resp == 'A' || resp == 'a')return 1;
    }else if(gabarito == 'B') {
        if(resp == 'B' || resp == 'b')return 1;
    }else if(gabarito == 'C') {
        if(resp == 'C' || resp == 'c')return 1;
    }
    return 0;
}

int quantidadeDeAcertos(){
    corretas = 0; 
    for(int i = 0; i < 10; i++){
        corretas += statusDeCadaQuestao[i]; 
    }
    return corretas;
}

void questoes(){
    for(int i = 0; i < 10; i++){
        switch (i+1)
        {
        case 1:
            printf("01 Qual o tipo para números inteiros? (A) int (B) float (C) char ");
            break;

        case 2:
            printf("02 Qual símbolo indica o operador E lógico? (A) || (B) ! (C) && ");
            break;

        case 3:
            printf("03 Qual comando sai de um loop? (A) continue (B) break (C) exit ");
            break;

        case 4:
            printf("04 Caractere que indica o fim de uma string? (A) \\0 (B) \\n (C) \\t ");
            break;

        case 5:
            printf("05 Qual função lê dados do teclado? (A) printf (B) scanf (C) main ");
            break;

        case 6:
            printf("06 Qual operador indica o OU lógico? (A) && (B) ! (C) || ");
            break;

        case 7:
            printf("07 Declaração correta de vetor de 5 inteiros? (A) int v[5] (B) v{5} (C) int v5 ");
            break;

        case 8:
            printf("08 Biblioteca necessária para usar o printf? (A) stdio.h (B) math.h (C) string.h ");
            break;

        case 9:
            printf("09 Qual o resultado da operação 10 %% 3? (A) 0 (B) 3 (C) 1 ");
            break;

        case 10:
            printf("10 O que significa void em uma função? (A) Erro (B) Sem retorno (C) Inteiro ");
            break;
        }

        scanf(" %c", &respostasDigitada[i]);
        statusDeCadaQuestao[i] = validar(respostasDigitada[i], respostasCorretas[i], i);
    }
}

int main(){
    int opcao = 0;
    int quiz = 1;

    do{
        printf("\n1. Iniciar Quiz \n");
        printf("2. Ver meu Desempenho \n");
        printf("3. Sair \n");

        while(scanf(" %d", &opcao) != 1 || opcao < 0){
            printf("Entrada inválida! Digite um número válido: ");
            while(getchar() != '\n');
        }
        
        if(opcao == 2){
            if(quiz == 1){
                printf("Inicie um quiz para ver o resultado. \n");
                continue;
            }
        }

        switch (opcao)
        {
        case 1:
            printf("--- Quiz Iniciado --- \n");
            questoes();
            quiz = 0;
            break;

        case 2:
            printf("--- Seu Desempenho --- \n");
            for(int i = 0; i < 10; i++){
                printf("Q%02d: [%c] %s\n", i+1, respostasDigitada[i] , statusDeCadaQuestao[i] == 1 ? "Correto" : "ERRADO");
            }
            printf("---------------------------- \n");
            printf("NOTA FINAL: %d pontos de 10 \n", quantidadeDeAcertos());
            printf("---------------------------- \n");
            break;

        case 3:
            printf("Saindo...");
            opcao = 0;
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }

    }while(opcao != 0);

    return 0;
}