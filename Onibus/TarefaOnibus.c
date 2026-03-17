/*
 * TarefaOnibus.c
 *
 *  Created on: 19 de fev. de 2026
 *      Author: Petrus Garcia
*/

#include "raylib.h"
#include <stdio.h>

#define TOTAL_ASSENTOS 40

// Estrutura para o ônibus
typedef struct {
    int assentos[TOTAL_ASSENTOS]; // 0 = livre, 1 = ocupado
	} Onibus;

typedef struct {
    int dia;
    int mes;
    int ano;
    } Data;

typedef struct{
	char nome[100];
    char dtNascimento[11];
    char cpf[16];

	} Passageiro;

typedef struct{
    char lcInicio[50];
    char lcDestino[50];
    Data dataViagem;
    int codViagem[3];
    } Viagem;

// Função que abre a janela com o mapa dos assentos
void MostrarMapaVisual(Onibus b) {
    // Programação da janela
    InitWindow(600, 600, "Mapa de Assentos");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("MAPA DE ASSENTOS (ESC para sair)", 20, 20, 20, DARKGRAY);

            // Grade dos assentos
            for (int i = 0; i < TOTAL_ASSENTOS; i++) {
                int coluna = i % 4;
                int linha = i / 4;

                // Locais dos quadrados
                int x = 150 + (coluna * 60);
                int y = 70 + (linha * 35);

                // Se o corredor estiver no meio (entre coluna 1 e 2)
                if (coluna > 1) x += 40;

                // Muda a cor se estiver ocupado ou não
                Color cor = (b.assentos[i] == 0) ? GREEN : RED;

                // Represetação dos assentos
                DrawRectangle(x, y, 40, 25, cor);
                DrawText(TextFormat("%02d", i + 1), x + 10, y + 5, 15, WHITE);
            }

            DrawText("VERDE: Livre | VERMELHO: Ocupado", 180, 370, 15, DARKGRAY);
        EndDrawing();
    }

    CloseWindow(); // Fecha o mapa
}


void CadastrarPassageiro(Passageiro *p){
	//Cadastro das informações do passageiro
    printf("\n--- Cadastro do Passageiro ---\n");
    printf("Digite seu Nome Completo:\n");
    scanf(" %[^\n]s", p->nome); //%[^\n]s linha inteira, incluindo espaços
    printf("Digite seu CPF:\n");
    scanf(" %s", p->cpf);
    printf("Digite sua data de nascimento:\n");
    scanf(" %s", p->dtNascimento);
}


void CadastrarViagem(Viagem *v){
	//Dados da viagem
    printf("\n--- Cadastro do Detalhes da Viagem ---\n");
    printf("Digite o código de sua viagem:\n");
    scanf(" %d", v->codViagem);
    printf("Digite seu Local de Origem:\n");
    scanf(" %[^\n]s", v->lcInicio);
    printf("Digite seu Local de Destino:\n");
    scanf(" %[^\n]s", v->lcDestino);
    printf("Insira sua data de Saída (Dia Mes Ano):\n");
    scanf(" %d, %d, %d", &v->dataViagem.dia, &v->dataViagem.mes, &v->dataViagem.ano);
}


void CadastrarPoltrona(Onibus *o){
	int num;

	//Dados da poltrona.
	printf("\n--- Escolha sua poltrona ---\n");
	printf("Digite o numero da poltrona (1-40): ");
	scanf(" %d", &num);
	if (num >= 1 && num <= 40) {
		o->assentos[num - 1] = 1; // Marca como ocupado
		printf("Venda realizada!\n");
	}
}


void VerViagens(Viagem *v){
	char controle = 'z';
	while (controle != 'x'){

        printf("--- Viagens Disponiveis ---\n");
        printf("Viagem: 919\n");
        printf("Viagem: 918\n");
        printf("Viagem: 917\n");
        printf("Viagem: 916\n");
        printf("Viagem: 915\n");
        printf("--------------------------\n");
        printf("Insira x para voltar:");
        scanf(" %c", &controle);

	}
	controle = 'z';
}


void CancelarPassagem(Onibus *o, Viagem *v, Passageiro *p){
	int num;

	printf("--- Cancelar Passagem ---\n");
	printf("Digite seu Nome Completo:\n");
    scanf(" %[^\n]s", p->nome); //%[^\n]s linha inteira, incluindo espaços
    printf("Digite seu CPF:\n");
    scanf(" %s", p->cpf);
    printf("Digite o código de sua viagem:\n");
    scanf(" %d", v->codViagem);
    printf("Digite o numero da poltrona (1-40): ");
    scanf(" %d", &num);
    printf("--------------------------\n");
    if (num >= 1 && num <= 40) {
        o->assentos[num - 1] = 0; // Marca como desocupado
        printf("Passagem cancelada!\n");
    }
}
int main() {
	// Força o console a mostrar o funcionamento do software !!Não remover, se não não funciona por bug!!
	        setvbuf(stdout, NULL, _IONBF, 0);

	Onibus meuOnibus = {0}; // Todos começam disponiveis (0)
    Viagem viagem;
    Passageiro cadastro;

	int opcao = 0;

    while (opcao != 5) {
        printf("\n--- SISTEMA Rodoviario ---\n");
        printf("1. Comprar Passagem\n");
        printf("2. Ver Mapa de Assentos (Visual)\n");
        printf("3. Ver viagens disponiveis\n");
        printf("4. Cancelar passagem\n");
        printf("5. Sair\n");
        printf("--------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
        	case 1:
        		//Cadastro das informações do passageiro
        		CadastrarPassageiro(&cadastro);
        		CadastrarViagem(&viagem);
        		CadastrarPoltrona(&meuOnibus);
        		break;

        	case 2:
        		printf("Abrindo mapa visual... feche a janela para voltar.\n");
        		MostrarMapaVisual(meuOnibus);
        		break;

        	case 3:
        		VerViagens(&viagem);
        		break;

        	case 4:
        		CancelarPassagem(&meuOnibus, &viagem, &cadastro);
        }
    }

    return 0;
}
