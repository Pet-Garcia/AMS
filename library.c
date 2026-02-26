#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 #define MAX 20

typedef struct {
    char nome[50];
    char nickname[50];
    float pontos;
    float numvitoria;
} Jogador;

Jogador ranking[MAX];
int totalJogadores = 0;

// Função para cadastrar jogador
void cadastrar() {
if (totalJogadores >= MAX) {
    printf("Limite de jogadores atingido!\n");
    return;
}

    printf("\n--- Cadastro de Jogador ---\n");

    printf("Nome: ");
    fgets(ranking[totalJogadores].nome, 50, stdin);
    //fgets() lê texto (string) do teclado ou de arquivo e é mais segura que scanf(" %s");
    ranking[totalJogadores].nome[strcspn(ranking[totalJogadores].nome, "\n")] = '\0';

    printf("Apelido/Nickname: ");
    fgets(ranking[totalJogadores].nickname, 50, stdin);
    ranking[totalJogadores].nickname[strcspn(ranking[totalJogadores].nickname, "\n")] = '\0';

    printf("Pontos: ");
    scanf(" %f", &ranking[totalJogadores].pontos);

    printf("Numero de vitorias: ");
    scanf(" %f", &ranking[totalJogadores].numvitoria);
    getchar(); // limpa buffer

    totalJogadores++;
    printf("Jogador cadastrado com sucesso!\n");
}

// Função para listar alunos
void listar() {
    if (totalJogadores == 0) {
        printf("\nNenhum jogador cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Jogadores ---\n");

    for (int i = 0; i < totalJogadores; i++) {
        printf(" %d - %s | Pontos: %.2f | %s | %.0f", i + 1, ranking[i].nome, ranking[i].pontos, ranking[i].nickname, ranking[i].numvitoria);

    }
}

// Função para mostrar o jogador com a maior pontação
void classificacao() {
    if (totalJogadores == 0) {
        printf("\nNenhum Jogador cadastrado.\n");
        return;
    }

    float maiorpontuacao = 0;
    int cont = 0;

    for (int i = 0; i < totalJogadores; i++) {
        if(maiorpontuacao < ranking[i].pontos) {
            maiorpontuacao = ranking[i].pontos;
        }
        cont++;
    }

    printf("O jogador com a maior pontuacao eh: %s", ranking->nome);
    printf("\nMaior pontuação: %.0f\n", ranking[1].pontos);
}

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE CAMPEONATO =====\n");
        printf("1 - Cadastrar Jogadore\n");
        printf("2 - Listar Jogadores\n");
        printf("3 - Maior Pontuacao\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %d", &opcao);
        getchar(); // limpa buffer

        switch(opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
                classificacao();
                break;
            case 4:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 4);

    return 0;
}