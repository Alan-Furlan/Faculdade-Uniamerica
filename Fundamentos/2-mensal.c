#include <stdio.h>

#include <string.h>



#define MAX_JOGADORES 5

#define MAX_PERGUNTAS 10



typedef struct {

  char nome[30];

  int jaJogou;

  int pontos;

} Jogador;



typedef struct {

  char pergunta[30];

  char respostaCorreta;

} Pergunta;



Jogador jogadores[MAX_JOGADORES];

Pergunta perguntas[MAX_PERGUNTAS];

int jogadoresCadastrados = 0;

int perguntasCadastradas = 0;



void lerEntrada(char str[], int tamanho) {

  fgets(str, tamanho, stdin);

  str[strcspn(str, "\n")] = '\0';

}



void cadastrarPerguntas() {

  printf("\n--- Cadastro de perguntas --- \n");

  getchar();

  printf("Digite a pergunta [%d]: ", perguntasCadastradas + 1);

  lerEntrada(perguntas[perguntasCadastradas].pergunta, 30);

  printf("Digite a resposta correta (V/F): ");

  

  while(scanf(" %c", &perguntas[perguntasCadastradas].respostaCorreta) != 1 || (perguntas[perguntasCadastradas].respostaCorreta != 'V' && perguntas[perguntasCadastradas].respostaCorreta != 'v' && perguntas[perguntasCadastradas].respostaCorreta != 'F' && perguntas[perguntasCadastradas].respostaCorreta != 'f')) {

    printf("Entrada inválida! Digite reposta válida: ");

    while(getchar() != '\n');

  }

  perguntasCadastradas++;

  printf("\nPergunta cadastrada com sucesso!\n");

  printf("------------------------\n");

}



void cadastrarJogadores() {

  printf("\n--- Cadastro de jogadores --- \n");

  jogadores[jogadoresCadastrados].jaJogou = 0;

  jogadores[jogadoresCadastrados].pontos = 0;

  

  getchar();

  printf("Digite o nome do jogador [%d]: ", jogadoresCadastrados + 1);

  lerEntrada(jogadores[jogadoresCadastrados].nome, 30);

  jogadoresCadastrados++;

  printf("\nJogador cadastrado com sucesso!\n");

  printf("------------------------\n");

}

 

void questoes(int jogadorId) {

  printf("\n--- Iniciando Jogo com o jogador: %s --- \n", jogadores[jogadorId].nome);

  for(int i = 0; i < perguntasCadastradas; i++) {

    printf("Pergunta %d: %s (V/F)? ", i + 1, perguntas[i].pergunta);



    char respostaDoJogador;

    while(scanf(" %c", &respostaDoJogador) != 1 || (respostaDoJogador != 'V' && respostaDoJogador != 'v' && respostaDoJogador != 'F' && respostaDoJogador != 'f')) {

      printf("Entrada inválida! Digite reposta válida: ");

      while(getchar() != '\n');

    }

    if(perguntas[i].respostaCorreta == 'V' || perguntas[i].respostaCorreta == 'v'){

      if(respostaDoJogador == 'V' || respostaDoJogador == 'v'){

        jogadores[jogadorId].pontos += 10;

        printf("Resposta correta! +10 pontos\n");

      } else {

        printf("Resposta incorreta!\n");

      }

    }else if(perguntas[i].respostaCorreta == 'F' || perguntas[i].respostaCorreta == 'f'){

      if(respostaDoJogador == 'F' || respostaDoJogador == 'f'){

        jogadores[jogadorId].pontos += 10;

        printf("Resposta correta! +10 pontos\n");

      } else {

        printf("Resposta incorreta!\n");

      }

    }

  }

  jogadores[jogadorId].jaJogou = 1;

  printf("------------------------\n");

  printf("Jogador %s fez %d pontos!\n", jogadores[jogadorId].nome, jogadores[jogadorId].pontos);

}



void escolhaDeJogador() {

  printf("--- Iniciando jogo --- \n");

  for(int i = 0; i < jogadoresCadastrados; i++) {

    printf("[%d] %s : %s\n", i, jogadores[i].nome, jogadores[i].jaJogou ? "Já jogou" : "Ainda não jogou");

  }

  printf("Escolha o jogador que irá jogar: ");

  int jogadorEscolhido;

  scanf(" %d", &jogadorEscolhido);



  if(jogadorEscolhido < 0 || jogadorEscolhido >= jogadoresCadastrados) {

    printf("Jogador inválido!\n");

    return;

  }

  if(jogadores[jogadorEscolhido].jaJogou == 1) {

    printf("Jogador já jogou, escolha outro jogador.\n");

  } else {

    questoes(jogadorEscolhido);

  }

}



void exibirRanking() {

  Jogador listaOrdenada[MAX_JOGADORES];

  for (int i = 0; i < jogadoresCadastrados; i++) {

    listaOrdenada[i] = jogadores[i];

  }



  for (int i = 0; i < jogadoresCadastrados - 1; i++) {

    for (int j = 0; j < jogadoresCadastrados - i - 1; j++) {

      if (listaOrdenada[j].pontos < listaOrdenada[j + 1].pontos) {

        Jogador temp = listaOrdenada[j];

        listaOrdenada[j] = listaOrdenada[j + 1];

        listaOrdenada[j + 1] = temp;

      }

    }

  }



  printf("\n--- RANKING ATUAL ---\n");

  for (int i = 0; i < jogadoresCadastrados; i++) {

    printf("%d. %s - %d pontos\n", i + 1, listaOrdenada[i].nome, listaOrdenada[i].pontos);

  }

  printf("---------------------\n");

}



int main() {

  int opcao;

  do {

    printf("\n--- SISTEMA DE QUIZ V/F --- \n");

    printf("1. Cadastrar perguntas %d/%d\n", perguntasCadastradas, MAX_PERGUNTAS);

    printf("2. Cadastrar jogadores %d/%d\n", jogadoresCadastrados, MAX_JOGADORES);

    printf("3. Iniciar jogo\n");

    printf("4. Ranking dos jogadores\n");

    printf("0. Sair\n");

    printf("Escolha uma opção: ");

    while(scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 4) {

      printf("Opção inválida! Escolha uma opção entre 0 e 4: ");

      while(getchar() != '\n');

    }



    switch (opcao) {

      case 0:

        printf("Saindo...\n");

        break;

      case 1:

        if(perguntasCadastradas >= MAX_PERGUNTAS) {

          printf("Limite de perguntas atingido.\n");

        } else cadastrarPerguntas();

        break;

      case 2:

        if(jogadoresCadastrados >= MAX_JOGADORES) {

          printf("Limite de jogadores atingido.\n");

        } else cadastrarJogadores();

        break;

      case 3:

        if(jogadoresCadastrados < 2 || perguntasCadastradas < MAX_PERGUNTAS) {

          printf("Cadastre pelo menos 2 jogadores e todas as perguntas.\n");

        } else escolhaDeJogador();

        break;

      case 4:

        if (jogadoresCadastrados == 0) {

          printf("Nenhum jogador cadastrado para exibir o ranking.\n");

        } else exibirRanking();

        break;

      default:

        printf("Opção inválida!\n");

        break;

    }

  } while (opcao != 0);



  return 0;

}