/*
 * TarefaOnibus.c
 *
 *  Created on: 19 de fev. de 2026
 *      Author: Petrus Garcia
*/

#include "raylib.h"
#include <stdio.h>
#include <string.h>

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
    Data dataViagem; // Insere na struct de Data
    int codViagem;
    } Viagem;

// Estrutura para o ônibus
typedef struct {
	int assentos[total_assentos]; // 0 = livre, 1 = ocupado
    Passageiro passageiros[total_assentos]; // Insere na Struct de Passageiro
   	} Onibus;


// ######################### Mapa dos Assentos ##############################
// Função que abre a janela com o mapa dos assentos
void MostrarMapaVisual(Onibus b, Viagem v) {
	// Programação da janela com o código da viagem no título
	InitWindow(800, 600, TextFormat("Mapa de Assentos - Viagem %d", v.codViagem));
    SetTargetFPS(60);

    // Loop para saber quando voltar ao console, só volta quando o esc ou x(da janela) é pressionado
    while (!WindowShouldClose()) {
    	BeginDrawing();
        	ClearBackground(RAYWHITE);
            // Informações sobre a viagem
            DrawText(TextFormat("VIAGEM: %d", v.codViagem), 20, 60, 20, MAROON);
            DrawText(TextFormat("ROTA: %s -> %s", v.lcInicio, v.lcDestino), 20, 85, 18, DARKGRAY);
            DrawText(TextFormat("DATA: %02d/%02d/%d", v.dataViagem.dia, v.dataViagem.mes, v.dataViagem.ano), 20, 110, 18, DARKGRAY);

            // Loop que pega todas as poltronas e desenha o mapa de assentos
            for (int i = 0; i < total_assentos; i++) {
            	// Indica as informações das coordenadas de onde os retangulos que representam as poltronas vão estar
				int coluna = i % 4;
				int linha = i / 4;
				int x = 200 + (coluna * 60);
				int y = 180 + (linha * 35);

				if (coluna > 1) x += 40;

				// Indica se o assento está disponivel ou não. Verde: Disponivel. Vermelho: Ocupado
				Color cor = (b.assentos[i] == 0) ? GREEN : RED;
				DrawRectangle(x, y, 40, 25, cor); //Desenha o retangulo onde vai representar a poltrona
				DrawText(TextFormat("%02d", i + 1), x + 10, y + 5, 15, WHITE);
			}

            // Legenda
            // Livre: Verde
            DrawRectangle(200, 550, 20, 20, GREEN);
            DrawText("Livre", 230, 550, 18, DARKGRAY);

            // Ocupado: Vermelho
            DrawRectangle(350, 550, 20, 20, RED);
            DrawText("Ocupado", 380, 550, 18, DARKGRAY);

            // Para voltar pressione esc
            DrawText("Pressione ESC para voltar ao menu", 200, 580, 15, GRAY);
            EndDrawing();
       	}
    CloseWindow();
}

// ######################### Validação ##############################
// Garante que a data inserida no sistema seja valida
int ValidarData(Data d) {
    if (d.dia < 1 || d.dia > 31) return 0; // Verifica se o dia existe
    if (d.mes < 1 || d.mes > 12) return 0; // Verifica se o mes existe
    if (d.ano < 2026){}; // Desligado a verificação do ano
    return 1;
}

// ######################### Mapa de Embarque ##############################
// Gera uma lista com as informações de todos que vão na viagem
void GerarListaEmbarque(Onibus o, Viagem v){
	int numembarque = 0;

	printf("LISTA DE EMBARQUE - VIAGEM %d      \n", v.codViagem);
    printf("--- ROTA: %s -> %s\n", v.lcInicio, v.lcDestino); // Indica o local de saida e seu destino
    printf("--- DATA: %02d/%02d/%d\n", v.dataViagem.dia, v.dataViagem.mes, v.dataViagem.ano); //Sua data
    printf("\n");
    printf("--- %-10s | %-25s | %-15s\n", "POLTRONA", "NOME DO PASSAGEIRO", "CPF"); // As informações dos passageiros
    // Loop que verifica os assentos
    for (int i = 0; i < total_assentos; i++) {
            if (o.assentos[i] == 1) { // Se o assento estiver ocupado apresenta as informações do passageiro
                printf("      [%02d]    | %-25s | %-15s\n",
                        i + 1,
                        o.passageiros[i].nome,
                        o.passageiros[i].cpf);
                numembarque = 1;
            }
        }

    // Não tem ninguem na viagem
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

    int validadata = 0;
    // Loop para validar a data
    while(validadata != 1){
    	printf("Insira a data de Saída (Dia Mes Ano):\n");
    	scanf("%d %d %d", &v->dataViagem.dia, &v->dataViagem.mes, &v->dataViagem.ano); // Insere as informações da daya

    	// Puxa a função de validação
    	if(ValidarData(v->dataViagem)){
    		validadata = 1;
    	}
    	else{
    		printf("Erro: Insira a data no formato dia mes ano (26 03 2026):\n");
    	}
    }

    printf("Viagem Cadastrada\n");
}


// Cadastra as informações da poltrona
void CadastrarPoltrona(Onibus *o){
	int num;

	//Dados da poltrona.
	printf("\n--- Selecione a poltrona ---\n");
	printf("Digite o numero da poltrona (1-40): ");
	scanf(" %d", &num);

	// Loop das poltronas
	if (num >= 1 && num <= 40) {
		o->assentos[num - 1] = 1; // Marca como ocupado
		printf("Venda realizada!\n");
	}

}

// Função que cancela as passagens
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

    // Loop das poltronas
    if (num >= 1 && num <= 40) {
        o->assentos[num - 1] = 0; // Marca como desocupado
        printf("Passagem cancelada!\n");
    }
}

// Função que procura os dados do passageiro pelo cpf
void BuscarPassageiroCPF(Viagem listaV[], Onibus listaO[], int totalV, char cpfBusca[]) {
    int encontrado = 0;

    printf("\n--- Busca pelo CPF: %s ---\n", cpfBusca);

    // Percorre as viagens/onibus
    for (int viagem = 0; viagem < totalV; viagem++) {

        // Percorre as poltronas da viagem
        for (int poltrona = 0; poltrona < total_assentos; poltrona++) {

            // Verifica se o assento está ocupado E se o CPF é igual
            if (listaO[viagem].assentos[poltrona] == 1 && strcmp(listaO[viagem].passageiros[poltrona].cpf, cpfBusca) == 0) {
                // Informa as informações do passageiro
            	printf("\nNome: %s", listaO[viagem].passageiros[poltrona].nome);
                printf("\nViagem: [%d] %s -> %s", listaV[viagem].codViagem, listaV[viagem].lcInicio, listaV[viagem].lcDestino);
                printf("\nPoltrona: %02d\n", poltrona + 1);
                encontrado = 1;
            }
        }
    }

    // Indica que não existe esse cpf no banco de dados
    if (encontrado != 1) {
        printf("\nCPF não encontrado\n");
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
    // Loop sobre as viagens existentes no banco
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

    // Caso não consiga criar o arquivo
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

// Limpa buffer -- Resolve outros problema -- Não Retirar
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void Pausar() {
	printf("\n[Pressione ENTER para voltar ao menu]");
	    // Limpa o buffer: consome todos os caracteres até encontrar um \n ou o fim do ficheiro
	    LimparBuffer();

	    // Agora que o buffer está limpo, este getchar() vai realmente esperar o utilizador
	    getchar();
}

// ######################### Programa Principal ##############################
// Programa Principal
int main() {
	// Força o console a mostrar o funcionamento do software !!Não remover, se não não funciona por bug!!
	        setvbuf(stdout, NULL, _IONBF, 0);

	// Inicializa os arrays das Viagens e Onibus(Passageiros + poltronas)
	Viagem listaViagem[total_viagens];
	Onibus listaOnibus[total_viagens];

    int totalviagem = 0;
	int opcao = 0;

	// Inicializa o arquivo do banco de dados e puxa as informações dentro para o sistema
	printf("Iniciando o Sistema Rodoviario...\n");
	CarregarDados(listaViagem, listaOnibus, &totalviagem);


	// Retorna o menu do sistema
    while (opcao != 8) {
    	// Menu do sistema
        printf("\n--- SISTEMA Rodoviario ---\n");
        printf("1. Comprar Passagem\n"); // Compra a passagem indicando as informações do passageiro e da viagem que está pegando
        printf("2. Ver Mapa de Assentos (Visual)\n"); // Mostra o mapa dos assentos de uma viagem escolhida de forma visual
        printf("3. Criar nova Viagem\n"); // Cria novas viagens
        printf("4. Ver viagens disponiveis\n"); // Puxa as viagens já existentes no sistema
        printf("5. Cancelar passagem\n"); // Cancela a passagem de um passageiro pelo cpf ou pelas informações sobre a viagem e poltrona
        printf("6. Gerar lista de Embarque\n"); // Gera uma lista sobre quem vai estar na Viagem
        printf("7. Buscar Viagens do Passageiro pelo cpf\n"); // Busca as viagens do passageiro pelo cpf
        printf("8. Sair\n"); // Salva os dados e fecha o sistema
        printf("--------------------------\n");
        printf("Escolha: "); // Seleciona qual função funcionar
        scanf("%d", &opcao);

        int cod, id;

        // Retorna a opção que o usuário escolheu do menu
        switch(opcao){

			//Cadastro das informações do passageiro
        	case 1:

        		printf("Digite o codigo da viagem: ");
                scanf("%d", &cod);
                // Busca as informações da viagem e armazena em uma variavel
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
                    	// Indica o erro do usuario sobre numero da poltrona inexistente
                    	printf("\n Erro: Numero invalido. Numeros de 1 a 40.\n");
                    }
                } else {
                	// Indica o erro de não existir a viagem com esse codigo
                    printf("Erro: Viagem nao encontrada!\n");
                }
                Pausar();
        		break;

        	// Busca o mapa  dos assentos de uma viagem especifica
        	case 2:
        		printf("Codigo da viagem para ver o mapa: ");
                scanf("%d", &cod);
                // Busca as informações da viagem e armazena em uma variavel
                id = BuscarViagem(listaViagem, totalviagem, cod);

                // Verifica se a viagem existe
                if (id != -1) {
                	printf("Abrindo mapa visual... feche a janela para voltar.\n");
                	// Mostra a representação gráfica da viagem
                    MostrarMapaVisual(listaOnibus[id], listaViagem[id]);
                } else {
                	// Indica o erro para o usuario sobre não existir tal viagem
                    printf("Erro: Viagem nao cadastrada!\n");
                }
                Pausar();
        		break;

        	// Cadastra novas viagens
        	case 3:
        		// Verifica se pode ser criado novas viagens
        		if (totalviagem < total_viagens) {

        			// Cadastra as informações sobre a viagem e gera as informações necessárias
        			CadastrarViagem(&listaViagem[totalviagem]);

        			// Zera os assentos do ônibus que acabou de ser criado
        			for(int i = 0; i < total_assentos; i++) {
        				listaOnibus[totalviagem].assentos[i] = 0;
        			}

        			// Aumenta a contagem de viagens existentes
        			totalviagem++;
        		} else {
        			// Indica que o sistema não tem espaço para mais viagens
        			printf("Erro: Limite de viagens atingido!\n");
        		}
        		Pausar();
        		break;

        	// Busca para o usuário as viagens existentes no sistema
        	case 4:
        		// Verifica se existe alguma viagem no sistema
        		if (totalviagem == 0) {
					printf("\n### Nenhuma Viagem Cadastrada ###\n");
				} else {
					// Mostra as viagens que existem no sistema para o usuario
					printf("\n--- Viagens no Sistema ---\n");
					// Loop que verifica se tem alguma viagem no array
					for (int i = 0; i < totalviagem; i++) {
						printf("[%d] %s -> %s\n", listaViagem[i].codViagem, listaViagem[i].lcInicio, listaViagem[i].lcDestino);
					}
				}
        		Pausar();
        		break;

        	// Busca os dados relevantes para cancelar a viagem
        	case 5: {
        		int opcao2 = 0;

        		// Inserção da variavel de busca
        		printf("Digite o codigo da viagem: ");
				scanf("%d", &cod);
				// Busca as informações da viagem e armazena em uma variavel
				id = BuscarViagem(listaViagem, totalviagem, cod);


				// Verifica se existe a viagem
				if (id != -1) {
					// Menu para saber como vai ser cancelado
					printf("Como deseja cancelar:");
					printf("1. Buscar por poltrona\n"); // Pelas informações sobre a poltrona
					printf("2. Buscar por cpf\n"); // Pelas informações do usuario
					printf("Escolha: ");
					scanf("%d", &opcao2);

					switch(opcao2) {

						//Busca por poltrona
						case 1: {
							int num;
							printf("Digite o numero da poltrona (1-40): ");
							scanf("%d", &num);

							// Verifica se o numero da poltrona é valido
							if (num >= 1 && num <= 40) {
								// Verifica se a poltrona está livre
								if (listaOnibus[id].assentos[num - 1] == 0) {
									printf("\nErro: A poltrona %02d está livre\n", num);
								} else {
									// Se estiver ocupada permite cancelar a passagem
									listaOnibus[id].assentos[num - 1] = 0; //Deixa a poltrona livre
									// Limpar o nome do passageiro para ficar vazio
									strcpy(listaOnibus[id].passageiros[num - 1].nome, "");
									printf("\nPassagem da poltrona %02d cancelada\n", num);
								}
							} else {
								// Indica que o numero da poltrona é invalido
								printf("\nErro: Numero de poltrona invalido\n");
							}
							break;
						}

						// Busca pelo usuario
						case 2: {
							char cpfBusca[16];
							int achei = 0;
							printf("Digite o CPF do passageiro: ");
							scanf("%s", cpfBusca);

							// Percorre as 40 poltronas do ônibus
							for (int j = 0; j < total_assentos; j++) {
								// Verifica se o assento está ocupado e compara cada caracter do cpf para ver sse é existe no sistema
								if (listaOnibus[id].assentos[j] == 1 && strcmp(listaOnibus[id].passageiros[j].cpf, cpfBusca) == 0) {
									listaOnibus[id].assentos[j] = 0; // Cancela e deixa a poltrona livre
									printf("\nPassagem encontrada na poltrona %02d e cancelada!\n", j + 1);
									achei = 1;
									break; // Para de procurar após achar o dono do CPF
								}
							}

							if (achei != 1) {
								// Indica que não foi encontrado o cpf
								printf("\nErro: CPF nao encontrado na Viagem %d\n", cod);
							}
							break;
						}

						// Verifica se a opção de menu é valida
						default:
							printf("\nOpcao de cancelamento inexistente. Opcao valida: 1 e 2\n");
							break;
					}
				} else {
					//  Inforam que a viagem não foi encontrada
					printf("\nErro: Viagem nao encontrada\n");
				}
				Pausar();
        		break;
        	}

        	// Gera a lista de embarque
        	case 6:
        		// Inserção de variavel de busca
        		printf("Digite o codigo da viagem para a lista de embarque: \n");
        		scanf("%d", &cod);
        		// Busca as informações da viagem e armazena em uma variavel
        		id = BuscarViagem(listaViagem, totalviagem, cod);

        		if (id != -1) {
        			//Verifica se a viagem existe
        		        GerarListaEmbarque(listaOnibus[id], listaViagem[id]);
        		    } else {
        		    	// Informa que a viagem não existe
        		        printf("\nErro: Viagem nao encontrada!\n");

        		}
        		Pausar();
        		break;

        	// Busca por cpf da passagem do cliente
        	case 7:
        		char cpfProcurado[16];
        		// Inserção da variavel de busca
        		printf("Digite o CPF para busca: (apenas numeros): \n");
        		scanf("%s", cpfProcurado);

        		// Função que verifica o sistema em busca do cpf
        		BuscarPassageiroCPF(listaViagem, listaOnibus, totalviagem, cpfProcurado);

        		Pausar();
        		break;

        	// Encerra o programa
        	case 8:
        		// Salva no armazenamento os dados inseridos
        		printf("\nSalvando informacoes...\n");
        		SalvarDados(listaViagem, listaOnibus, totalviagem); // Função que salva
        		printf("Encerrando o sistema. Ate logo!\n");

        		LimparBuffer();
        		break;

        	default:
        		printf("\nOpcao de Menu inexistente. Opcao valida: 1 a 8\n");
        		break;
        }
    }

    return 0;
}
