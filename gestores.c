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


int loginGestores(Gestores **inicio,char password[]){
    
}