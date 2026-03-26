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

// Estrutura para o ônibus
typedef struct {
	int assentos[total_assentos]; // 0 = livre, 1 = ocupado
    Passageiro passageiros[total_assentos];
   	} Onibus;


// ######################### Mapa dos Assentos ##############################
// Função que abre a janela com o mapa dos assentos
void MostrarMapaVisual(Onibus b, Viagem v) {
	// Programação da janela com o código da viagem no título
	InitWindow(800, 600, TextFormat("Mapa de Assentos - Viagem %d", v.codViagem));
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
    	BeginDrawing();
        	ClearBackground(RAYWHITE);
            // Texto sobre a viagem
            DrawText(TextFormat("VIAGEM: %d", v.codViagem), 20, 60, 20, MAROON);
            DrawText(TextFormat("ROTA: %s -> %s", v.lcInicio, v.lcDestino), 20, 85, 18, DARKGRAY);
            DrawText(TextFormat("DATA: %02d/%02d/%d", v.dataViagem.dia, v.dataViagem.mes, v.dataViagem.ano), 20, 110, 18, DARKGRAY);

            // Desenho do mapa de assentos
            for (int i = 0; i < total_assentos; i++) {
				int coluna = i % 4;
				int linha = i / 4;
				int x = 200 + (coluna * 60);
				int y = 180 + (linha * 35); // Começa mais baixo

				if (coluna > 1) x += 40;

				Color cor = (b.assentos[i] == 0) ? GREEN : RED;
				DrawRectangle(x, y, 40, 25, cor);
				DrawText(TextFormat("%02d", i + 1), x + 10, y + 5, 15, WHITE);
			}

            // Legenda
            DrawRectangle(200, 550, 20, 20, GREEN);
            DrawText("Livre", 230, 550, 18, DARKGRAY);

            DrawRectangle(350, 550, 20, 20, RED);
            DrawText("Ocupado", 380, 550, 18, DARKGRAY);

            DrawText("Pressione ESC para voltar ao menu", 200, 580, 15, GRAY);
            EndDrawing();
       	}
    CloseWindow();
}

// ######################### Mapa de Embarque ##############################
void GerarListaEmbarque(Onibus o, Viagem v){
	int numembarque = 0;

	printf("LISTA DE EMBARQUE - VIAGEM %d      \n", v.codViagem);
    printf("--- ROTA: %s -> %s\n", v.lcInicio, v.lcDestino);
    printf("--- DATA: %02d/%02d/%d\n", v.dataViagem.dia, v.dataViagem.mes, v.dataViagem.ano);
    printf("\n");
    printf("--- %-10s | %-25s | %-15s\n", "POLTRONA", "NOME DO PASSAGEIRO", "CPF");
    for (int i = 0; i < total_assentos; i++) {
            if (o.assentos[i] == 1) { // Se o assento estiver ocupado
                printf("      [%02d]    | %-25s | %-15s\n",
                        i + 1,
                        o.passageiros[i].nome,
                        o.passageiros[i].cpf);
                numembarque = 1;
            }
        }

        if (!numembarque) {
            printf("\n          (Nenhum passageiro embarcado)       \n");
        }
}

// ######################### Cadastros ##############################
void CadastrarPassageiro(Passageiro *p){
	//Cadastro das informações do passageiro
    printf("\n--- Cadastro do Passageiro ---\n");
    printf("Digite seu Nome Completo:\n");
    scanf(" %[^\n]s", p->nome); //%[^\n]s linha inteira, incluindo espaços
    printf("Digite seu CPF:\n");
    scanf(" %s", p->cpf);
    printf("Digite sua data de nascimento (DiaMesAno):\n");
    scanf(" %s", p->dtNascimento);
}


void CadastrarViagem(Viagem *v){
	//Dados da viagem
    printf("\n--- Cadastro do Detalhes da Viagem ---\n");
    printf("Digite o código de sua viagem:\n");
    scanf(" %d", &v->codViagem);
    printf("Digite o Local de Origem:\n");
    scanf(" %[^\n]s", v->lcInicio);
    printf("Digite o Local de Destino:\n");
    scanf(" %[^\n]s", v->lcDestino);
    printf("Insira a data de Saída (DiaMesAno):\n");
    scanf(" %d, %d, %d", &v->dataViagem.dia, &v->dataViagem.mes, &v->dataViagem.ano);

    printf("Viagem Cadastrada\n");
}


void CadastrarPoltrona(Onibus *o){
	int num;

	//Dados da poltrona.
	printf("\n--- Selecione a poltrona ---\n");
	printf("Digite o numero da poltrona (1-40): ");
	scanf(" %d", &num);
	if (num >= 1 && num <= 40) {
		o->assentos[num - 1] = 1; // Marca como ocupado
		printf("Venda realizada!\n");
	}
}

void CancelarPassagem(Onibus *o, Viagem *v, Passageiro *p){
	int num;

	// Infomações necessárias para cancelar a passagem especifica
	printf("--- Cancelar Passagem ---\n");
	printf("Digite o Nome Completo:\n");
    scanf(" %[^\n]s", p->nome); //%[^\n]s linha inteira, incluindo espaços
    printf("Digite o CPF:\n");
    scanf(" %s", p->cpf);
    printf("Digite o código da viagem:\n");
    scanf(" %d", &v->codViagem);
    printf("Digite o numero da poltrona (1-40): ");
    scanf(" %d", &num);
    printf("--------------------------\n");
    if (num >= 1 && num <= 40) {
        o->assentos[num - 1] = 0; // Marca como desocupado
        printf("Passagem cancelada!\n");
    }
}

// ######################### Informações das Viagens ##############################
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


// ######################### Armazenamento dos dados ##############################
/*
 * Função para Salvar as informações
*/
void SalvarDados(Viagem listaV[], Onibus listaO[], int total) {
    // Abre o arquivo em modo "wb" (Write Binary - Escrita Binária)
    FILE *arquivo = fopen("banco_viagens.bin", "wb");

    if (arquivo == NULL) {
        printf("ERRO: O sistema não conseguiu criar o backup\n");
        return;
    }

    // Salva a quantidade de viagens existente
    fwrite(&total, sizeof(int), 1, arquivo);

    // Salva os arrays de Viagem e Onibus no arquivo
    if (total > 0) {
        fwrite(listaV, sizeof(Viagem), total, arquivo);
        fwrite(listaO, sizeof(Onibus), total, arquivo);
    }

    fclose(arquivo); // Fecha o arquivo de forma segura
    printf("Os dados foram salvos no sistema\n");
}

/*
 *  Função para Carregar as informações no sistema
 */
void CarregarDados(Viagem listaV[], Onibus listaO[], int *total) {
    // Abre o arquivo em modo "rb" (Read Binary - Leitura Binária)
    FILE *arquivo = fopen("banco_viagens.bin", "rb");

    // Verifica se existe arquivo de armazenamento
    if (arquivo == NULL) {
        printf("Banco de dados não encontrado \n");
        printf("Iniciando sem dados armazenados \n");
        *total = 0;
        return;
    }

    // Leitura da quantidade de dados salvos e armazenamento em total
    fread(total, sizeof(int), 1, arquivo);

    // Carrega os dados no armazenamento para os arrays
    if (*total > 0) {
        fread(listaV, sizeof(Viagem), *total, arquivo);
        fread(listaO, sizeof(Onibus), *total, arquivo);
    }

    fclose(arquivo);
    printf("Dados carregados: (%d viagens encontradas) \n", *total);
}

// Limpa buffer -- Resolve outro problema -- Não Retirar
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void Pausar() {
	printf("\n[Pressione ENTER para voltar ao menu]");
	    // Limpa o buffer: consome todos os caracteres até encontrar um \n ou o fim do ficheiro
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF);

	    // Agora que o buffer está limpo, este getchar() vai realmente esperar o utilizador
	    getchar();
}

// ######################### Programa Principal ##############################
// Programa Principal
int main() {
	// Força o console a mostrar o funcionamento do software !!Não remover, se não não funciona por bug!!
	        setvbuf(stdout, NULL, _IONBF, 0);

	Viagem listaViagem[total_viagens];
	Onibus listaOnibus[total_viagens];

    int totalviagem = 0;
	int opcao = 0;

	printf("Iniciando o Sistema Rodoviario...\n");
	CarregarDados(listaViagem, listaOnibus, &totalviagem);


	// Retorna o menu do sistema
    while (opcao != 7) {
        printf("\n--- SISTEMA Rodoviario ---\n");
        printf("1. Comprar Passagem\n");
        printf("2. Ver Mapa de Assentos (Visual)\n");
        printf("3. Criar nova Viagem\n");
        printf("4. Ver viagens disponiveis\n");
        printf("5. Cancelar passagem\n");
        printf("6. Gerar lista de Embarque\n");
        printf("7. Sair\n");
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

                // if para ver se existe a viagem
                if (id != -1) {
                	int num;
                	printf("Numero da poltrona (1-40): ");
                	scanf("%d", &num);

                    // if para ver se existe a poltrona
                    if (num >= 1 && num <= 40) {

                    	// if para ver se a poltrona está ocupada
                        if (listaOnibus[id].assentos[num - 1] == 1) {
                        	// Se não estiver diponivel
                            printf("\n Erro: A poltrona %02d ja esta ocupada nesta viagem!\n", num);
                            printf("Consulte o mapa (Opcao 2) para ver os assentos livres.\n");
                        } else {
                            // Se estiver livre, solicita os dados do passageiro, confirma e armazena as informações da passagem
                            CadastrarPassageiro(&listaOnibus[id].passageiros[num - 1]);
                            listaOnibus[id].assentos[num - 1] = 1;
                            printf("\nVenda realizada com sucesso! Poltrona %02d reservada \n", num);
                        }

                    } else{
                    	printf("\n Erro: Numero invalido. Numeros de 1 a 40.\n");
                    }
                } else {
                    printf("Viagem nao encontrada!\n");
                }
                Pausar();
        		break;

        	case 2:
        		// Busca o mapa  dos assentos de uma viagem especifica
        		printf("Codigo da viagem para ver o mapa: ");
                scanf("%d", &cod);
                id = BuscarViagem(listaViagem, totalviagem, cod);
                if (id != -1) {
                	printf("Abrindo mapa visual... feche a janela para voltar.\n");
                    MostrarMapaVisual(listaOnibus[id], listaViagem[id]);
                } else {
                    printf("Viagem nao cadastrada!\n");
                }
                Pausar();
        		break;

        	case 3:
        		// Cadastra novas viagens
        		// Verifica se pode ser criado novas viagens
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
        		Pausar();
        		break;

        	case 4:
        		// Busca para o usuário as viagens existentes no sistema
        		// Verifica se existe alguma viagem no sistema
        		if (totalviagem == 0) {
					printf("\n### Nenhuma Viagem Cadastrada ###\n");
				} else {
					printf("\n--- Viagens no Sistema ---\n");
					for (int i = 0; i < totalviagem; i++) {
						printf("[%d] %s -> %s\n", listaViagem[i].codViagem, listaViagem[i].lcInicio, listaViagem[i].lcDestino);
					}
				}
        		Pausar();
        		break;

        	case 5:
        		// Busca os dados relevantes para cancelar a viagem
        		printf("Digite o codigo da viagem: ");
				scanf("%d", &cod);
				id = BuscarViagem(listaViagem, totalviagem, cod);

				// Verifica se existem a viagem
				if (id != -1) {
					int num;
					printf("Poltrona para cancelar: ");
					scanf("%d", &num);

					// Verifica se existe o numero da poltrona
					if (num >= 1 && num <= 40) {

						// Verifica se a poltrona está disponivel
			            if (listaOnibus[id].assentos[num - 1] == 0) {
			                printf("\n Erro: A poltrona %02d esta livre \n", num);
			            } else {
			            	listaOnibus[id].assentos[num-1] = 0;
			            	printf("Passagem cancelada! A poltrona %02d esta disponivel \n", num);
			            }

					} else{
                    	printf("\n Erro: Numero invalido. Numeros de 1 a 40.\n");
                    }

				}
				Pausar();
        		break;

        	case 6:
        		printf("Digite o codigo da viagem para a lista de embarque: \n");
        		scanf("%d", &cod);
        		id = BuscarViagem(listaViagem, totalviagem, cod);

        		if (id != -1) {
        			//Verifica se o id existe
        		        GerarListaEmbarque(listaOnibus[id], listaViagem[id]);
        		    } else {
        		        printf("Viagem nao encontrada!\n");

        		}
        		Pausar();
        		break;

        	case 7:
        		// Encerra o programa
        		printf("\nSalvando informacoes...\n");
        		SalvarDados(listaViagem, listaOnibus, totalviagem);
        		printf("Encerrando o sistema. Ate logo!\n");
        		int c;
        		while ((c = getchar()) != '\n' && c != EOF);

        		// Agora que o buffer está limpo, este getchar() vai realmente esperar o utilizador
        		getchar();
        		break;
        }
    }

    return 0;
}
