/*
 * TarefaOnibus.c
 *
 *  Created on: 19 de fev. de 2026
 *      Author: Petrus Garcia
*/

#include "raylib.h"
#include <stdio.h>

#define total_assentos 40
#define total_viagens 40

// Estrutura para o ônibus
typedef struct {
    int assentos[total_assentos]; // 0 = livre, 1 = ocupado
	} Onibus;

// Estrutura para a data
typedef struct {
    int dia;
    int mes;
    int ano;
    } Data;

// Estrutura para o passageiro/cliente
typedef struct{
	char nome[100];
    char dtNascimento[11];
    char cpf[16];
	} Passageiro;

// Estrutura para a viagem
typedef struct{
    char lcInicio[50];
    char lcDestino[50];
    Data dataViagem;
    int codViagem;
    } Viagem;

// Função que abre a janela com o mapa dos assentos
void MostrarMapaVisual(Onibus b, int codigo) {
	// Programação da janela com o código da viagem no título
    InitWindow(600, 600, TextFormat("Mapa de Assentos - Viagem %d", codigo));
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    	BeginDrawing();
        	ClearBackground(RAYWHITE);
            // Texto sobre a viagem
            DrawText(TextFormat("MAPA VIAGEM: %d (ESC para sair)", codigo), 20, 20, 20, DARKGRAY);

            // Desenho do mapa de assentos
            for (int i = 0; i < total_assentos; i++) {
            	int coluna = i % 4;
            	int linha = i / 4;
                int x = 150 + (coluna * 60);
                int y = 70 + (linha * 35);
                if (coluna > 1) x += 40;
                Color cor = (b.assentos[i] == 0) ? GREEN : RED;
                DrawRectangle(x, y, 40, 25, cor);
                DrawText(TextFormat("%02d", i + 1), x + 10, y + 5, 15, WHITE);
            }

            // Define se o texto escrito é livre ou ocupado
            DrawText("VERDE: Livre | VERMELHO: Ocupado", 180, 550, 15, DARKGRAY);
            EndDrawing();
       	}
    CloseWindow();
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


// Busca o código da viagem na lista ou -1 se não encontrar
int BuscarViagem(Viagem lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
    	// Análisa todos os itens do codViagem e retorna seu indice
        if (lista[i].codViagem == codigo) {
            return i;
        }
    }
    return -1;
}

void VerViagens(Viagem lista[], int total) {
	// Verifica se há alguma viagem cadastrada
    if (total == 0) {
        printf("\n### Nenhuma Viagem Cadastrada no Sistema ###\n");
        return;
    }

    // Passa as informações das viagens para o usuário
    printf("\n--- Viagens no Sistema ---\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: [%d] | Origem: %s | Destino: %s", lista[i].codViagem, lista[i].lcInicio, lista[i].lcDestino);
    }
    printf("-------------------------------\n");
}


void CancelarPassagem(Onibus *o, Viagem *v, Passageiro *p){
	int num;

	// Infomações necessárias para cancelar a passagem especifica
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

// Programa Principal
int main() {
	// Força o console a mostrar o funcionamento do software !!Não remover, se não não funciona por bug!!
	        setvbuf(stdout, NULL, _IONBF, 0);

	Viagem listaViagem[total_viagens];
	Onibus listaOnibus[total_viagens];
    Passageiro cadastro;

    int totalviagem = 0;
	int opcao = 0;

	// Retorna o menu do sistema
    while (opcao != 6) {
        printf("\n--- SISTEMA Rodoviario ---\n");
        printf("1. Comprar Passagem\n");
        printf("2. Ver Mapa de Assentos (Visual)\n");
        printf("3. Criar nova Viagem\n");
        printf("4. Ver viagens disponiveis\n");
        printf("5. Cancelar passagem\n");
        printf("6. Sair\n");
        printf("--------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        int cod, id;

        // Retorna a opção que o usuário escolheu do menu
        switch(opcao){
        	case 1:
        		//Cadastro das informações do passageiro
        		printf("Digite o codigo da viagem: ");
                scanf("%d", &cod);
                id = BuscarViagem(listaViagem, totalviagem, cod);
                if (id != -1) {
                    CadastrarPassageiro(&cadastro);
                    // Passa o ônibus específico dessa viagem
                    int num;
                    printf("Numero da poltrona (1-40): ");
                    scanf("%d", &num);
                    if (num >= 1 && num <= 40) {
                        listaOnibus[id].assentos[num - 1] = 1;
                        printf("Venda realizada na viagem %d!\n", cod);
                    }
                } else {
                    printf("Viagem nao encontrada!\n");
                }
        		break;

        	case 2:
        		// Busca o mapa  dos assentos de uma viagem especifica
        		printf("Codigo da viagem para ver o mapa: ");
                scanf("%d", &cod);
                id = BuscarViagem(listaViagem, totalviagem, cod);
                if (id != -1) {
                	printf("Abrindo mapa visual... feche a janela para voltar.\n");
                    MostrarMapaVisual(listaOnibus[id], cod);
                } else {
                    printf("Viagem nao cadastrada!\n");
                }
        		break;

        	case 3:
        		// Cadastra novas viagens
        		if (totalviagem < total_viagens) {

        			CadastrarViagem(&listaViagem[totalviagem]);

        			// Zera os assentos do ônibus que acabou de ser criado
        			for(int i = 0; i < total_assentos; i++) {
        				listaOnibus[totalviagem].assentos[i] = 0;
        			}
        			totalviagem++;
        		} else {
        			printf("Limite de viagens atingido!\n");
        		}
        		break;

        	case 4:
        		// Busca para o usuário as viagens existentes no sistema
        		if (totalviagem == 0) {
					printf("\n### Nenhuma Viagem Cadastrada ###\n");
				} else {
					printf("\n--- Viagens no Sistema ---\n");
					for (int i = 0; i < totalviagem; i++) {
						printf("[%d] %s -> %s\n", listaViagem[i].codViagem, listaViagem[i].lcInicio, listaViagem[i].lcDestino);
					}
				}
        		break;

        	case 5:
        		// Busca os dados relevantes para cancelar a viagem
        		printf("Digite o codigo da viagem: ");
				scanf("%d", &cod);
				id = BuscarViagem(listaViagem, totalviagem, cod);
				if (id != -1) {
					int num;
					printf("Poltrona para cancelar: ");
					scanf("%d", &num);
					if (num >= 1 && num <= 40) {
						listaOnibus[id].assentos[num-1] = 0;
						printf("Passagem cancelada!\n");
					}
				}
        		break;

        	case 6:
        		// Encerra o programa
        		opcao = 6;
        		break;
        }
    }

    return 0;
}
