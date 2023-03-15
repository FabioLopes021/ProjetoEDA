#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"



void inserirCliente(Clientes** inicio, char nome[], char morada[], char NIF[], float saldo, char password[], char email[]){
    Clientes *new;
    
    new = (Clientes *) malloc(sizeof(Clientes));

    strcpy(new->name, nome);
    strcpy(new->morada, morada);
    strcpy(new->NIF, NIF);
    strcpy(new->email, email);
    strcpy(new->password, password);
    new->saldo = saldo;

    new->next = (*inicio);
    (*inicio) = new;
}

void lerDados(Clientes** inicio){
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    float saldo = 0;

    while ((getchar()) != '\n');

    system("clear");
    printf("\n--------------- Criar Conta ---------------");
    printf("\nIndique o seu nome: ");
    fgets(nome, MAX_NAME, stdin);
    nome[strlen(nome)-1] = '\0';

    while ((getchar()) != '\n');

    printf("\nIndique a sua morada: ");
    fgets(morada, MAX_MORADA, stdin);
    morada[strlen(morada) - 1] = '\0';

    while ((getchar()) != '\n');

    printf("\nIndique o seu NIF: ");
    fgets(NIF, MAX_NIF, stdin);
    NIF[MAX_NIF] = '\0';

    while ((getchar()) != '\n');

    printf("\nIndique o seu email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strlen(email)-1] = '\0';

    while ((getchar()) != '\n');

    printf("\nIndique a sua password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strlen(password)-1] = '\0';

    while ((getchar()) != '\n');
    inserirCliente(&(*inicio), nome, morada, NIF, saldo, password, email);
}

int listarCliente(Clientes* inicio){

    if (!inicio)
        return 0;

    printf("#############################################\n");
    printf("nome: ");
    puts(inicio->name);
    printf("\nmorada: ");
    puts(inicio->morada);
    printf("\nNIF: ");
    puts(inicio->NIF);
    printf("\n email: ");
    puts(inicio->email);
    printf("\nsaldo: %.2f\n", inicio->saldo);
    listarCliente(inicio->next);
}


int existeCliente(Clientes* inicio, char NIF[]){
    if (!inicio)
        return 0;
    if (!strcmp(NIF, inicio->NIF))   
        return 1;
    return existeCliente(inicio->next, NIF);
}

int existeClienteEmail(Clientes* inicio, char email[]){
    if (!inicio)
        return 0;
    if (!strcmp(email, inicio->email))   
        return 1;
    return existeClienteEmail(inicio->next, email);
}

Clientes *removerCliente(Clientes **inicio, char NIF[], int i){
    Clientes *aux;

    if (!*inicio){
        printf("A base de dados esta vazia\n");
        return NULL;
    }

    if(!(existeCliente((*inicio), NIF))){
        printf("Nao existe nenhum cliente resgistado com o NIF indicado...\n");
        return NULL;
    }
    
    if (!strcmp((*inicio)->NIF, NIF) && i == 1){
        aux = (*inicio)->next;
        free((*inicio));
        (*inicio) = aux;
        return aux;
    }else if (!strcmp((*inicio)->NIF, NIF)){
        aux = (*inicio)->next;
        free((*inicio));
        return aux;
    }else{
        (*inicio)->next = removerCliente(&(*inicio)->next, NIF, ++i);
        return (*inicio);
    }
}


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

void alterarNomeCliente(Clientes *cliente, char novonome[]){

    if (strlen(novonome) > MIN_NAME){
        strcpy(cliente->name, novonome);
    }
}

void alterarMoradaCliente(Clientes *cliente, char novamorada[]){

    if (strlen(novamorada) > MIN_NAME){
        strcpy(cliente->morada, novamorada);
    }
}

void alterarNIFCliente(Clientes *cliente, char novoNIF[]){

    if (strlen(novoNIF) > MIN_NAME){
        strcpy(cliente->NIF, novoNIF);
    }
}

void alterarEmailCliente(Clientes *cliente, char novoemail[]){

    if (strlen(novoemail) > MIN_NAME){
        strcpy(cliente->email, novoemail);
    }
}

void alterarPasswordCliente(Clientes *cliente, char novapassword[]){

    if (strlen(novapassword) > MIN_NAME){
        strcpy(cliente->password, novapassword);
    }
}

void carregarSaldo(Clientes *cliente, float quantia){
    
    if(cliente == NULL){
        return;
    }

    cliente->saldo += quantia;

}


void readClientes(Clientes **inicio){
    FILE* fp;
    float saldo;
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL], password[MAX_PASSWORD];
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6;

    fp = fopen("clientes.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");

            strcpy(nome, campo1);
            strcpy(morada, campo2);
            strcpy(NIF, campo3);
            strcpy(email, campo4);
            strcpy(password, campo5);
			saldo = atof(campo6);

            inserirCliente(&(*inicio), nome, morada, NIF, saldo, password, email);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


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
        fprintf(fp,"%.2f\n", inicio->saldo);
        inicio = inicio->next;
        }

        fclose(fp);

        printf("Clientes guardados com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro Clientes\n");
}

