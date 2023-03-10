#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestores.h"



void inserirGestor(Gestores** inicio, char nome[], char morada[], char NIF[], char password[], char email[]){
    Gestores *new;
    
    new = (Gestores *) malloc(sizeof(Gestores));

    strcpy(new->name, nome);
    strcpy(new->morada, morada);
    strcpy(new->NIF, NIF);
    strcpy(new->email, email);
    strcpy(new->password, password);

    new->next = (*inicio);
    (*inicio) = new;
}

void lerDadosGestor(Gestores** inicio){
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];

    while ((getchar()) != '\n');

    system("clear");
    printf("\n--------------- Criar Conta ---------------");
    printf("\nIndique o seu nome: ");
    fgets(nome, MAX_NAME, stdin);
    sscanf(nome,"%*s",nome);
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
    
    inserirGestor(&(*inicio), nome, morada, NIF, password, email);
}


int listarGestor(Gestores* inicio){

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
    listarGestor(inicio->next);
}


int existeGestor(Gestores* inicio, char NIF[]){
    if (!inicio)
        return 0;
    if (!strcmp(NIF, inicio->NIF))   
        return 1;
    return existeGestor(inicio->next, NIF);
}

int existeGestorEmail(Gestores* inicio, char email[]){
    if (!inicio)
        return 0;
    if (!strcmp(email, inicio->email))   
        return 1;
    return existeGestorEmail(inicio->next, email);
}

Gestores *removerGestor(Gestores **inicio, char NIF[], int i){
    Gestores *aux;

    if (!*inicio){
        printf("A base de dados esta vazia");
        return NULL;
    }

    if(!(existeGestor((*inicio), NIF))){
        printf("Nao existe nenhum gestor resgistado com o NIF indicado...\n");
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
        (*inicio)->next = removerGestor(&(*inicio)->next, NIF, ++i);
        return (*inicio);
    }
}



Gestores *loginGestores(Gestores **inicio,char password[], char email[]){

    if (!(*inicio)){
        return NULL;
    }

    if (!existeGestorEmail((*inicio), email)){
        return NULL;
    }

    if (strcmp(password, (*inicio)->password)){
        return loginGestores(&(*inicio)->next, password, email);
    }

    return (*inicio);
}