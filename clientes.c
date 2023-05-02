#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"




/**
 * @brief Funçao para adicionar um novo Cliente a lista ligada de clientes
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 * @param nome Nome do Cliente a ser inserido
 * @param morada Morada do Cliente a ser inserido
 * @param NIF NIF do Cliente a ser inserido
 * @param saldo Saldo do Cliente a ser inserido
 * @param password Password do Cliente a ser inserido
 * @param email Email do Cliente a ser inserido
 * @param id ID do Cliente a ser inserido
 */
void inserirCliente(Clientes** inicio, char nome[], char morada[], char NIF[], float saldo, char password[], char email[], int id){
    Clientes *new;
    
    new = (Clientes *) malloc(sizeof(Clientes));

    strcpy(new->name, nome);
    strcpy(new->morada, morada);
    strcpy(new->NIF, NIF);
    strcpy(new->email, email);
    strcpy(new->password, password);
    new->saldo = saldo;
    new->id = id;

    new->next = (*inicio);
    (*inicio) = new;
}


/**
 * @brief Funçao para ler os dados de um Cliente e inseri-lo na lista ligada dos Clientes 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 */
void lerDados(Clientes** inicio){
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    int id;
    float saldo = 0;

    //while ((getchar()) != '\n');
    clearbuffer();

    system("clear");
    printf("\n--------------- Criar Conta ---------------");
    printf("\nIndique o seu nome: ");
    fgets(nome, MAX_NAME, stdin);
    nome[strlen(nome)-1] = '\0';

    //while ((getchar()) != '\n');
    clearbuffer();

    printf("\nIndique a sua morada: ");
    fgets(morada, MAX_MORADA, stdin);
    morada[strlen(morada) - 1] = '\0';

    //while ((getchar()) != '\n');
    clearbuffer();

    printf("\nIndique o seu NIF: ");
    fgets(NIF, MAX_NIF, stdin);
    NIF[MAX_NIF - 1] = '\0';

    //while ((getchar()) != '\n');
    clearbuffer();

    printf("\nIndique o seu email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strlen(email)-1] = '\0';

    clearbuffer();

    printf("\nIndique a sua password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strlen(password)-1] = '\0';
    clearbuffer();

    id = generateidCliente(*inicio);
    encriptPassword(password);    

    inserirCliente(&(*inicio), nome, morada, NIF, saldo, password, email, id);
}



/**
 * @brief Funçao que lista os dados de todos os clientes registados
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param i Contador da funçao
 * @return int retorna 0 se a lista estiver vazia ou quando a funçao chegar ao final da lista
 */
int listarCliente(Clientes* inicio, int i){

    if (!inicio){
        printf(" ------------------------------------------------------------------------------------------------------------- \n");
        return 0;
    }

    if(i == 1){
        generico();
        printf("\n\n ------------------------------------------------------------------------------------------------------------- \n");
        printf("|      Nome       |           Morada           |     NIF     |            Email            |   saldo   |  ID  |\n");
        printf(" ------------------------------------------------------------------------------------------------------------- \n");
    }
    printf("|   %-12s  |       %-14s       |  %-9s  |  %-25s  |   %-4.2f€   |  %-2d  |\n", inicio->name, inicio->morada, inicio->NIF,
    inicio->email, inicio->saldo, inicio->id);
    

    listarCliente(inicio->next, ++i);
}


/**
 * @brief Funçao que lista os dados de um cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna 1 se os dados do cliente foram listados com sucesso e 0 caso contrário.
 */
int printCliente(Clientes *inicio){
    if (!inicio)
        return 0;
    
    generico();

    printf("\n\n ------------------------------------------------------------------------------------------------------------- \n");
    printf("|      Nome       |           Morada           |     NIF     |            Email            |   saldo   |  ID  |\n");
    printf(" ------------------------------------------------------------------------------------------------------------- \n");
    printf("|   %-12s  |       %-14s       |  %-9s  |  %-25s  |   %-4.2f€   |  %-2d  |\n", inicio->name, inicio->morada, inicio->NIF,
    inicio->email, inicio->saldo, inicio->id);
    printf(" ------------------------------------------------------------------------------------------------------------- \n");

    EsperarQuePrimaEnter();
    return 1;
}



/**
 * @brief Funçao que verifica se um determinado cliete existe
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param id ID do cliente a verificar
 * @return int retorna 1 se o cliente existir, 0 caso contrario
 */
int existeCliente(Clientes* inicio, int id){
    if (!inicio)
        return 0;
    if (inicio->id == id)   
        return 1;
    return existeCliente(inicio->next, id);
}


/**
 * @brief Função que verifica se um determinado email corresponde a algum cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param email Email a ser verificado 
 * @return int retorna 1 se o email inserido corresponder ao email de algum cliente e 0 se nao corresponder
 */
int existeClienteEmail(Clientes* inicio, char email[]){
    if (!inicio)
        return 0;
    if (!strcmp(email, inicio->email))   
        return 1;
    return existeClienteEmail(inicio->next, email);
}

/**
 * @brief Funçao para remover um determinado Cliente
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 * @param NIF NIF do cliete a ser removido
 * @param i contador para a funçao
 * @return Clientes* retorna o endereço do cliente seguinte ao cliente removido da lista, NULL caso o mesmo n seja encontrado
 */
Clientes *removerCliente(Clientes **inicio, int id, int i){
    Clientes *aux;

    if (!*inicio){
        printf("A base de dados esta vazia\n");
        return NULL;
    }

    if(!(existeCliente((*inicio), id))){
        printf("Nao existe nenhum cliente resgistado com o NIF indicado...\n");
        return NULL;
    }
    
    if (((*inicio)->id == id) && i == 1){
        aux = (*inicio)->next;
        free((*inicio));
        (*inicio) = aux;
        return aux;
    }else if (((*inicio)->id == id)){
        aux = (*inicio)->next;
        free((*inicio));
        return aux;
    }else{
        (*inicio)->next = removerCliente(&(*inicio)->next, id, ++i);
        return (*inicio);
    }
}

/**
 * @brief Funçao para verificar a password e email de um cliente
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 * @param password Password a ser verificada
 * @param email Email a ser verificado
 * @return Clientes* Retorna o endereço do cliente correspondente as credenciais,NULL caso contrario 
 */
Clientes *loginClientes(Clientes **inicio,char password[], char email[]){
    
    if (!(*inicio)){
        return NULL;
    }

    if (!existeClienteEmail((*inicio), email)){
        return NULL;
    }

    if (strcmp(password, (*inicio)->password)){
        return loginClientes(&(*inicio)->next, password, email);
    }

    return (*inicio);
}


/**
 * @brief Funçao para alterar o nome de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param novonome Novo nome do cliente
 */
void alterarNomeCliente(Clientes *cliente, char novonome[]){

    if (strlen(novonome) > MIN_NAME){
        strcpy(cliente->name, novonome);
    }
}

/**
 * @brief Funçao para alterar a morada de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param novamorada Nova morada do cliente
 */
void alterarMoradaCliente(Clientes *cliente, char novamorada[]){

    if (strlen(novamorada) > MIN_NAME){
        strcpy(cliente->morada, novamorada);
    }
}


/**
 * @brief Funçao para alterar o NIF de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param novoNIF Novo NIF do cliente
 */
void alterarNIFCliente(Clientes *cliente, char novoNIF[]){

    if (strlen(novoNIF) > MIN_NAME){
        strcpy(cliente->NIF, novoNIF);
    }
}

/**
 * @brief Funçao para alterar o email de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param novoemail Novo email do cliente
 */
void alterarEmailCliente(Clientes *cliente, char novoemail[]){

    if (strlen(novoemail) > MIN_NAME){
        strcpy(cliente->email, novoemail);
    }
}


/**
 * @brief Funçao para alterar o email de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param novapassword Nova password do cliente
 */
void alterarPasswordCliente(Clientes *cliente, char novapassword[]){

    if (strlen(novapassword) > MIN_NAME){
        strcpy(cliente->password, novapassword);
    }
}


/**
 * @brief Funçao para carregar o saldo de um cliente
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param quantia Quantida a carregar
 */
void carregarSaldo(Clientes *cliente, float quantia){
    
    if(cliente == NULL){
        return;
    }

    cliente->saldo += quantia;

}

/**
 * @brief Funçao para retirar o saldo relativo ao aluguer de uma meio
 * 
 * @param cliente Endereço do cliente a alterar o nome
 * @param quantia Quantida a retirar
 */
void pagamento(Clientes *cliente, double quantia){
    
    if(cliente == NULL){
        return;
    }

    cliente->saldo -= quantia;

}

/**
 * @brief Funçao para gerar im ID unico para um novo cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna um ID unico para o novo cliente
 */
int generateidCliente(Clientes *inicio){
    int max = 1;

    if (!inicio)
        return max;

    while(inicio != NULL){
        if (max < inicio->id)
            max = inicio->id;
        inicio = inicio->next;
    }

    return ++max;
}


/**
 * @brief Funçao para carregar os cliente e os seus dados do ficheiro 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 */
void readClientes(Clientes **inicio){
    FILE* fp;
    float saldo;
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL], password[MAX_PASSWORD];
    int id;
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7;

    fp = fopen("clientes.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");
			campo7 = strtok(NULL, ";");

            strcpy(nome, campo1);
            strcpy(morada, campo2);
            strcpy(NIF, campo3);
            strcpy(email, campo4);
            strcpy(password, campo5);
			saldo = atof(campo6);
            id = atoi(campo7);

            inserirCliente(&(*inicio), nome, morada, NIF, saldo, password, email, id);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}

/**
 * @brief Funçao para guardar os Clientes e os seus dados em ficheiro
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 */
void guardarClientes(Clientes* inicio){
    FILE* fp;

    fp = fopen("clientes.txt","w");

    if (fp!=NULL){
        
        while (inicio != NULL){
        fputs(inicio->name, fp);
        fprintf(fp,";");
        fputs(inicio->morada, fp);
        fprintf(fp,";");
        fputs(inicio->NIF, fp);
        fprintf(fp,";");
        fputs(inicio->email, fp);
        fprintf(fp,";");
        fputs(inicio->password, fp);
        fprintf(fp,";");
        fprintf(fp,"%.2f", inicio->saldo);
        fprintf(fp,";");
        fprintf(fp,"%d\n", inicio->id);
        inicio = inicio->next;
        }

        fclose(fp);

        printf("Clientes guardados com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro Clientes\n");
}


/**
 * @brief Funçao para carregar os cliente e os seus dados do ficheiro binario
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Clientes
 */
void lerCLientesBin(Clientes **inicio){
    FILE *fp;
    Clientes *new;

    new = (Clientes *) malloc(sizeof(Clientes));

    fp = fopen("clientess.bin", "rb");

    if(fp != NULL){

       while (fread(new, sizeof(Clientes), 1, fp) == 1) {
            if(new != NULL){
                inserirCliente(&(*inicio), new->name, new->morada, new->NIF, new->saldo, new->password, new->email, new->id);
            }
             
        }
        free(new);
        fclose(fp);

        printf("Dados binarios lidos com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}



/**
 * @brief Funçao para guardar os Clientes e os seus dados num ficheiro binario
 * 
 * @param inicio Apontador para a lista de clientes
 */
void guardarClientesBin(Clientes *inicio){
    FILE *fp;

    fp = fopen("clientess.bin", "wb");

    if(fp != NULL){

        while (inicio != NULL) {
            fwrite(inicio, sizeof(Clientes), 1, fp);
            inicio = inicio->next;
        }

        fclose(fp);

        printf("Meios guardados em binario com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}