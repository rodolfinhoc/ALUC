#ifdef __WIN32 //se for windows define o limpar tela como cls, se for linu como clear, comandos s�o diferentes dependendo do OS
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#define MAX 100 // quantidade m�xima de letras no nome do cliente, cpf e nome do carro
 // defini��o da struct carro
typedef struct carro
{
	int id;
	int id_cliente;
	char nome[MAX], modelo[MAX];
	float diaria;
} cad_veiculo;
 // defini��o da struct cliente
typedef struct cliente
{
	int id;
	char nome[MAX];
	char cpf[MAX];
	char parceiro[MAX];
} cad_cliente;

int data;
char menuCarro();
void cadastroCliente();
void cadastroCarro();
void listar_carros();
void listar_clientes();
cad_veiculo *obter_carro(FILE *arq_carros, int id_carro);
cad_cliente *obter_cliente(FILE *arq_clientes, int id_cliente);
int existe_carro(FILE *arq_carros, int id_carro);
int existe_cliente(FILE *arq_clientes, int id_cliente);
void alugar_carro();
void entregar_carro();
void excluir_carro();
int str_somente_numeros(char str[]);
 
 
int main(int argc, char *argv[])
{
system("color 7");
printf("\n\t\t                                                                              \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                  ((((((((((((&                                \n\t\t                            #(((((((((((((((((((((((                           \n\t\t                         (((((                  *((((((                        \n\t\t                       (((#                         ((((((                     \n\t\t                     (((                               ((((#                   \n\t\t                   (((                                   ((                    \n\t\t                  ((                                                           \n\t\t                 ((       &@@%%%%&@@                                           \n\t\t                ((  &      &%                 &@                               \n\t\t               ((            &&                   @                            \n\t\t               ((              &      @%&&&&&&&%&@                             \n\t\t               (  %&&&&&%%%#%&&&&&&&&&&&&&&&&&&&&&&&&&&&% /&&                  \n\t\t              #(  &&&&&&&&&&&&&&&&&&&&(   &&&&&&&&&&&&&&&&&&&&& .@             \n\t\t               (  &&&&&&&&&&&&&&&&&&&&&&&      &&&&&&&&&&&&&&&&&&&&            \n\t\t               (   &&&&&&&&  &&%&&&&&&&&&&&&&&&&&&&&&#/(%&&&&&&&&&             \n\t\t               ((  &&&&&&&& &&& &&&    .&&&&&&&&&&&&&&&&&&&&&&&&&&             \n\t\t                (      @&&& #&& &&&&&&&&&    *%&&&&&&&&&&&&&&&&&&#             \n\t\t                ((        &&  (&&&                     &&&&&& &                \n\t\t                 (#        /&&&&                         &&&&                  \n\t\t                  ((                                                           \n\t\t                    (                                                          \n\t\t                     #(                                                        \n\t\t                       ((                                                      \n\t\t                          ((                                                   \n\t\t                              ((                #                              \n\t\t                                                                               \n\t\t                                                                               \n\t\t");
sleep(4);
system(limpar_tela);
system("color 9");
printf("\n\n\n\n\n\n\n\n\n                                                                               \n\t\t                                                                               \n\t\t               (((((((((  ((          (#      ((         #(((((((((            \n\t\t              #(       (( ((          (#      ((         ((                    \n\t\t              ((       (( ((          (#      ((         ((                    \n\t\t              ((/(((((/(( ((          (#      ((  (((((  ((                    \n\t\t              ((       (( ((((((((((( ((((((((((         ((((((((((            \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                                                               \n\t\t                                                                              ");
sleep(5);
system(limpar_tela);
system("color 7");
	char cliente_nome;
	char cliente_cpf;
	char op;	
	while(1)
	{

		op = menuCarro(); 
		// testa o valor de "op"
		if(op == '1')
			cadastroCarro();
		else if(op == '2')
			cadastroCliente();
		else if(op == '3')
			listar_carros();
		else if(op == '4')
			listar_clientes();
		else if(op == '5')
			alugar_carro();
		else if(op == '6')
			entregar_carro();
		else if(op == '7')
			excluir_carro();
		else if(op == '0') // se for igual a 0, ent�o sai do loop while
			break;
		else
		{
			printf("\n\t\tOpcao invalida! Aperte <Enter> para prosseguir...");
			scanf("%*c");
			fseek(stdin, 0, SEEK_END); // n�o recomend�vel o uso
		}
		system(limpar_tela);
	}

	return 0;
}

char menuCarro()
{
	// fazer o Menu aqui, obviamente. Lembre-se da ideia: Colocar o logo com um sleep de 5 segundos ou mais(ou menos), e ent�o dar um "limpar_tela"
	char op[2];
	printf("\n\n\n\n\n\n\t\t\t\t\tSISTEMA DE LOCACAO DE VEICULOS\n\t\t\t\t\t\t     ALU-C");
	
	printf("\n\n\t\t\t\t\t1 - Cadastrar um veiculo\n");
	printf("\t\t\t\t\t2 - Realizar cadastro de cliente\n");
	printf("\t\t\t\t\t3 - Mostrar lista de carros\n");
	printf("\t\t\t\t\t4 - Mostrar lista de clientes\n");
	printf("\t\t\t\t\t5 - Alugar um carro por ID\n");
	printf("\t\t\t\t\t6 - Devolver um carro\n");
	printf("\t\t\t\t\t7 - Apagar registro de carro\n");
	printf("\t\t\t\t\t0 - Sair\n\n");
	printf("\t\t\t\t\tEscolha uma opcao: ");
	scanf("%1s%*c", op); 
	fseek(stdin, 0, SEEK_END);

	return op[0];
}

// fun��o que verifica se uma string cont�m somente n�meros
int str_somente_numeros(char str[])
{
	int i = 0;
	int len_str = strlen(str);
 
	for(i = 0; i < len_str; i++)
	{
		if(str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}
 
// fun��o para cadastrar cliente
void cadastroCliente()
{

	FILE *arq_clientes = fopen("clientes.bin", "a+b");

	if(arq_clientes == NULL)
	{
		printf("\n\t\t\t\t\tErro ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}
	int cont_bytes = 0;

	fseek(arq_clientes, 0, SEEK_END);
	// pegamos a quantidade de bytes com a fun��o ftell
	cont_bytes = ftell(arq_clientes);
 	cad_cliente cliente;
 
	if(cont_bytes == 0)
	{
		cliente.id = 1;
	}
	else
	{
		cad_cliente ultimo_cliente;
		fseek(arq_clientes, cont_bytes - sizeof(cad_cliente), SEEK_SET);

		fread(&ultimo_cliente, sizeof(cad_cliente), 1, arq_clientes);

		cliente.id = ultimo_cliente.id + 1;
	}

	printf("\n\t\t\t\t\tEntre com  o nome do cliente: ");
	scanf("%99[^\n]%*c", cliente.nome);
	printf("\n\t\t\t\t\tEntre com  o CPF do cliente: ");
	scanf("%99[^\n]%*c", cliente.cpf);
	printf("\n\t\t\t\t\tUsuario tem parceria com a Alu-C?\n");
	scanf("%99[^\n]%*c", cliente.parceiro);
	printf("\n\t\t\t\t\tClientes parceiros e/ou maiores de 65 anos tem direito a 5/100 de desconto, aproveite!\n");

	fseek(stdin, 0, SEEK_END);
	fseek(arq_clientes, 0, SEEK_END);
	fwrite(&cliente, sizeof(cad_cliente), 1, arq_clientes);
	fclose(arq_clientes);
 
	printf("\n\t\t\t\t\tCliente \"%s\" cadastrado com sucesso!\n", cliente.nome);
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c"); // pega o Enter e descarta
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o para cadastrar carro
void cadastroCarro()
{
	FILE *arq_carros = fopen("carros.bin", "a+b");
	if(arq_carros == NULL)
	{
		printf("\n\t\t\t\t\tErro ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}
	cad_veiculo carro; //Cria��o de ID para o carro
	int cont_bytes = 0;	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_carros, 0, SEEK_END);
	cont_bytes = ftell(arq_carros);
 
	if(cont_bytes == 0)
	{
		carro.id = 1;
	}
	else
	{
		cad_veiculo ultimo_carro;
		fseek(arq_carros, cont_bytes - sizeof(cad_veiculo), SEEK_SET);
		fread(&ultimo_carro, sizeof(cad_veiculo), 1, arq_carros);	// o ID do carro � o ID do �ltimo carro acrescido em 1
		carro.id = ultimo_carro.id + 1;
	}

	printf("\n\t\t\t\t\tEntre com  o nome do carro: ");
	scanf("%99[^\n]%*c", carro.nome);
 	printf("\n\t\t\t\t\tEntre com  o modelo do carro: ");
 	scanf("%99[^\n]%*c", carro.modelo);
	fseek(stdin, 0, SEEK_END);
	do
	{
		char str_diaria[5];
		float float_diaria;
		int somente_numeros = 1;
 
		printf("\n\t\t\t\t\tEntre com  a diaria do aluguel do carro: ");
		scanf("%c", str_diaria);
		fseek(stdin, 0, SEEK_END);
		somente_numeros = str_somente_numeros(str_diaria); 	// verifica se o pre�o possui somente n�meros
		if(somente_numeros == 1)
		{
			int int_diaria; 			// exemplo: 49,50 deve digitar 4950
			sscanf(str_diaria, "%d", &int_diaria);
			float_diaria = int_diaria / 1;
			carro.diaria = float_diaria;
			break;
		}
	}
	while(1);
	carro.id_cliente = -1; // inicializa o id_cliente com -1 indicando que o carro N�O est� alugado
	fseek(arq_carros, 0, SEEK_END);	// se o ponteiro n�o estiver no final do arquivo nada � escrito
	fwrite(&carro, sizeof(cad_veiculo), 1, arq_carros);
	fclose(arq_carros);
printf("\n\t\t\t\t\tcarro \"%s\" cadastrado com sucesso!\n", carro.nome);
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o para listar todos os clientes
void listar_clientes()
{
	// rb => abre arquivo bin�rio para leitura apenas
	FILE *arq_clientes = fopen("clientes.bin", "rb");
	if(arq_clientes == NULL)
	{
		printf("\n\t\t\t\t\tErro ao abrir arquivo(s) ou ");
	printf("Nenhum cliente cadastrado.\n");
		printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
scanf("%*c");
		fseek(stdin, 0, SEEK_END);
		return;
	}
	int encontrou_clientes = 0;
	cad_cliente cliente;
 
	printf("\n\t\t\t\t\tListando todos os clientes...\n");
	while(1)
	{
		size_t result = fread(&cliente, sizeof(cad_cliente), 1, arq_clientes);
		if(result == 0)
			break;
		encontrou_clientes = 1;
		printf("\n\t\t\t\t\tID do cliente: %d\n", cliente.id);
	printf("\t\t\t\t\tNome do cliente: %s\n", cliente.nome);
			printf("\t\t\t\t\tCPF do cliente: %s\n", cliente.cpf);
		printf("\t\t\t\t\tDesconto? %s ", cliente.parceiro);
	} 
	if(encontrou_clientes == 0)
		printf("\n\t\t\t\t\tNenhum cliente cadastrado.\n");
 
	fclose(arq_clientes);
		printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o que obt�m um cliente pelo ID
cad_cliente *obter_cliente(FILE *arq_clientes, int id_cliente)
{
	rewind(arq_clientes);
	cad_cliente *cliente;
	cliente = (cad_cliente *)malloc(sizeof(cad_cliente));
	while(1)
	{
		size_t result = fread(cliente, sizeof(cad_cliente), 1, arq_clientes);
		if(result == 0)
		{
free(cliente); // libera a m�moria, pois o cliente n�o foi encontrado
			return NULL;
		}
	if(cliente->id == id_cliente)
		break;
	}
	return cliente;
}

// fun��o para listar todos os carros
void listar_carros()
{
	FILE *arq_carros = fopen("carros.bin", "rb"); // rb => abre para leitura somente, ponteiro para o in�cio do arquivo
	FILE *arq_clientes = fopen("clientes.bin", "rb");

	if(arq_carros == NULL)
	{
		printf("\n\t\t\t\t\tErro ao abrir arquivo ou ");
		printf("\t\t\t\t\tNenhum carro cadastrado.\n");
		printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
		scanf("%*c");
		fseek(stdin, 0, SEEK_END);
		return;
	}
	int encontrou_carros = 0;
	printf("\n\t\t\t\t\tListando todos os carros...\n");
	cad_veiculo carro;
	while(1)
	{
size_t result = fread(&carro, sizeof(cad_veiculo), 1, arq_carros);
		if(result == 0)
			break;
encontrou_carros = 1;
 
		printf("\n\t\t\t\t\tID do carro: %d\n", carro.id);
printf("\t\t\t\t\tNome do carro: %s\n", carro.nome);
	printf("\t\t\t\t\tdiaria: %f\n", carro.diaria);

		if(carro.id_cliente != -1) 		// se id_cliente for diferente de -1, ent�o o carro est� alugado, pois possui algum id v�lido do cliente que alugou o carro. Se id_cliente for igual a -1, indica que o carro n�o est� alugado, pois o id -1 N�O � um id v�lido
		{
			if(arq_clientes == NULL)
			{
		printf("\n\t\t\t\t\tErro ao abrir arquivo!\n");
				fclose(arq_carros);
exit(1); // aborta o programa
			}
			cad_cliente *cliente = obter_cliente(arq_clientes, carro.id_cliente);
			printf("\t\t\t\t\tAlugado? Sim. Cliente: %s\n", cliente->nome);
			free(cliente);
		}
		else
printf("\t\t\t\t\tAlugado? Nao\n");
	}

	if(encontrou_carros == 0)
		printf("\n\t\t\t\t\tNenhum carro cadastrado.\n");

	if(arq_clientes != NULL)
		fclose(arq_clientes); // apenas se foi aberto
	fclose(arq_carros);
 
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o que verifica se um carro existe
// retorna 0 se N�O existe e 1 caso contr�rio
int existe_carro(FILE *arq_carros, int id_carro)
{
	rewind(arq_carros);
	cad_veiculo carro;
	while(1)
	{
		size_t result = fread(&carro, sizeof(cad_veiculo), 1, arq_carros);
		if(result == 0)
			break;
		if(carro.id == id_carro)
			return 1;
	}
	return 0;
}
 
// fun��o que verifica se um cliente existe
// retorna 0 se N�O existe e 1 caso contr�rio
int existe_cliente(FILE *arq_clientes, int id_cliente)
{
	rewind(arq_clientes);
	cad_cliente cliente;
	while(1)
	{
		size_t result = fread(&cliente, sizeof(cad_cliente), 1, arq_clientes);
		if(result == 0)
			break;
		if(cliente.id == id_cliente)
			return 1;
	} 
	// se chegou aqui � porque N�O existe o cliente, ent�o retorna 0
	return 0;
}
  
// fun��o que obt�m um carro pelo ID
cad_veiculo *obter_carro(FILE *arq_carros, int id_carro)
{
	rewind(arq_carros);
	cad_veiculo *carro;
	carro = (cad_veiculo *)malloc(sizeof(cad_veiculo));
	while(1)
	{
		size_t result = fread(carro, sizeof(cad_veiculo), 1, arq_carros);
		if(result == 0)
			break;
		if(carro->id == id_carro)
			return carro;
	}
	free(carro);
	return NULL;
}
 
void atualizar_carros(FILE *arq_carros, cad_veiculo *carro_alugado)
{
	rewind(arq_carros); 
	cad_veiculo carro;
	while(1)
	{
 		size_t result = fread(&carro, sizeof(cad_veiculo), 1, arq_carros);

		if(result == 0)
			break; 
		if(carro.id == carro_alugado->id)
		{
			fseek(arq_carros, - sizeof(cad_veiculo), SEEK_CUR);
			fwrite(carro_alugado, sizeof(cad_veiculo), 1, arq_carros);
			break; 
		}
	}
} 
 
// fun��o respons�vel pelo aluguel dos carros
void alugar_carro()
{
	char str_id_cliente[10];
	int id_cliente;
	char cliente_nome, cliente_cpf;
	FILE *arq_carros = fopen("carros.bin", "rb+");
	FILE *arq_clientes = fopen("clientes.bin", "rb+");

	if(arq_carros == NULL)
	{
		arq_carros = fopen("carros.bin", "wb+");
		if(arq_carros == NULL)
		{
			printf("\nErro ao criar arquivo(s)!\n");
			exit(1);
		}
	}
 
	if(arq_clientes == NULL)
	{
		arq_clientes = fopen("clientes.bin", "wb+");
		if(arq_clientes == NULL)
		{
			printf("\nErro ao criar arquivo(s)!\n");
			exit(1);
		}
	}

	printf("\n\t\t\t\t\tEntre com  o ID do cliente: ");
	scanf("%10s%*c", str_id_cliente); 
	fseek(stdin, 0, SEEK_END);
	if(str_somente_numeros(str_id_cliente) == 1)
	{
		sscanf(str_id_cliente, "%d", &id_cliente);
		if(existe_cliente(arq_clientes, id_cliente))
		{
			char str_id_carro[10];
			int id_carro;
 
			printf("\n\t\t\t\t\tEntre com  o ID do carro: ");
			scanf("%10s%*c", str_id_carro);
 
			fseek(stdin, 0, SEEK_END);
 
			if(str_somente_numeros(str_id_carro) == 1)
			{
				sscanf(str_id_carro, "%d", &id_carro);
				cad_veiculo *carro = obter_carro(arq_carros, id_carro);
				if(carro != NULL)
				{
					if(carro->id_cliente != -1)
						printf("\n\t\t\t\t\tO carro \"%s\" ja esta alugado!\n", carro->nome);
					else
					{
						fclose(arq_clientes);
						carro->id_cliente = id_cliente;
		printf("\n\t\t\t\t\tcarro \"%s\" alugado com sucesso!", carro->nome);
							printf("\n\t\t\t\t\tAlugado com sucesso por: %s \nCPF: %s\n", cliente_nome, cliente_cpf);
					}
					free(carro);
				}
		else
					printf("\n\t\t\t\t\tNao existe carro com o ID \"%d\".\n", id_carro);
			}
		else
				printf("\n\t\t\t\t\tO ID so pode conter numeros!\n");
		}
		else
			printf("\n\t\t\t\t\tNao existe cliente com o ID \"%d\".\n", id_cliente);
	}
	else
		printf("\n\t\t\t\t\tO ID so pode conter numeros!\n");
	fclose(arq_clientes);
	fclose(arq_carros);
 
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
 
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o respons�vel pela entrega dos carros
void entregar_carro()
{
	char str_id_carro[10];
	int id_carro;
	FILE *arq_carros = fopen("carros.bin", "rb+");
	if(arq_carros == NULL)
	{
		arq_carros = fopen("carros.bin", "wb+");
		if(arq_carros == NULL)
		{
			printf("\n\t\t\t\t\tErro ao criar arquivo(s)!\n");
			exit(1);
		}
	} 
	printf("\n\t\t\t\t\tEntre com  o ID do carro: ");
	scanf("%10s%*c", str_id_carro);
	fseek(stdin, 0, SEEK_END);
	if(str_somente_numeros(str_id_carro) == 1)
	{
		sscanf(str_id_carro, "%d", &id_carro);
		cad_veiculo *carro = obter_carro(arq_carros, id_carro);
		if(carro != NULL)
		{
			if(carro->id_cliente == -1)
				printf("\n\t\t\t\t\tO carro \"%s\" ja esta disponivel!\n", carro->nome);
			else
			{
				carro->id_cliente = -1;
				printf("\n\t\t\t\t\tcarro \"%s\" entregue com sucesso!\n", carro->nome);
			}
			free(carro);
		}
		else
			printf("\n\t\t\t\t\tNao existe carro com o ID \"%d\".\n", id_carro);
	}
	else
		printf("\n\t\t\t\t\tO ID so pode conter numeros!\n");
	fclose(arq_carros);
 
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
 
	fseek(stdin, 0, SEEK_END);
}
 
// fun��o respons�vel por excluir carros
void excluir_carro()
{
	char str_id_carro[10];
	int id_carro;
 
	printf("\n\t\t\t\t\tEntre com  o ID do carro: ");
	scanf("%10s%*c", str_id_carro);
	fseek(stdin, 0, SEEK_END);
	if(str_somente_numeros(str_id_carro) == 1)
	{
		sscanf(str_id_carro, "%d", &id_carro);
		FILE *arq_carros = fopen("carros.bin", "rb");
		if(arq_carros == NULL)
		{
			printf("\n\t\t\t\t\tErro ao abrir arquivo(s)!\n");
			exit(1);
		}
		if(existe_carro(arq_carros, id_carro) == 1)
		{
			char nome_carro[MAX]; // abre um novo arquivo tempor�rio
			FILE *arq_temp = fopen("temp_carros.bin", "a+b");
			if(arq_temp == NULL)
			{
				printf("\n\t\t\t\t\tErro ao criar arquivo temporario!\n");
				fclose(arq_carros);
				exit(1);
			}
			rewind(arq_carros); // vai para o in�cio do arquivo
			cad_veiculo carro;
			while(1)
			{ // fread retorna o n�mero de elementos lidos com sucesso
				size_t result = fread(&carro, sizeof(cad_veiculo), 1, arq_carros);
				if(result == 0)
					break;
 
		if(carro.id != id_carro)
				{
					fwrite(&carro, sizeof(cad_veiculo), 1, arq_temp);
				}
				else
					strcpy(nome_carro, carro.nome);
			}
		fclose(arq_carros);
			fclose(arq_temp);

			if(remove("carros.bin") != 0)
				printf("\n\t\t\t\t\tErro ao deletar o arquivo \"carros.bin\"\n");
			else
			{
		int r = rename("temp_carros.bin", "carros.bin");
				if(r != 0)
				{
	printf("\n\t\t\t\t\tPermissao negada para renomear o arquivo!\n");
					printf("Encerre esse programa bem como o arquivo \"temp_carros.bin\" e renomeie manualmente para \"carros.bin\"\n");
				}
				else
					printf("\ncarro \"%s\" deletado com sucesso!\n", nome_carro);
			}
		}
		else
		{
			fclose(arq_carros);
			printf("\n\t\t\t\t\tNao existe carro com o ID \"%d\".\n", id_carro);
		}
	}
	else
		printf("\n\t\t\t\t\tO ID so pode conter numeros!\n");
 
	printf("\n\t\t\t\t\tAperte <Enter> para prosseguir...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}

