#include "meio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut){
    Meio *new;
    
    new = (Meio *) malloc(sizeof(Meio));

    new->codigo = cod;
    strcpy(new->tipo, tipo);
    new->bateria = bat;
    new->autonomia = aut;

    new->next = (*inicio);
    (*inicio) = new;
}


int existeMeio(Meio* inicio, int codigo){
    if (!inicio)
        return 0;
    if (inicio->codigo == codigo)   
        return 1;
    return existeMeio(inicio->next, codigo);
}



int listarMeios(Meio* inicio){

    if (!inicio)
        return 0;

    printf("#############################################\n");
    printf("codigo: %d\n", inicio->codigo);
    printf("Tipo: %s\n", inicio->tipo);
    printf("Bateria: %d\n", inicio->bateria);
    printf("Autonomia: %f\n", inicio->autonomia);
    listarMeios(inicio->next);
}

int listarMeiosLivres(Meio* inicio){

    if (!inicio)
        return 0;

    if (inicio->aluguer == NULL){
        printf("#############################################\n");
        printf("codigo: %d\n", inicio->codigo);
        printf("Tipo: %s\n", inicio->tipo);
        printf("Bateria: %d\n", inicio->bateria);
        printf("Autonomia: %f\n", inicio->autonomia);
    }
    
    listarMeios(inicio->next);
}

int listarMeiosAlugados(Meio* inicio, Clientes *c, int i){

    if (!inicio)
        return i;
        
    if(inicio->aluguer == c){
        printf("#############################################\n");
        printf("codigo: %d\n", inicio->codigo);
        printf("Tipo: %s\n", inicio->tipo);
        printf("Bateria: %d\n", inicio->bateria);
        printf("Autonomia: %f\n", inicio->autonomia);
        i++;
    }
    
    listarMeiosAlugados(inicio->next, c, i);
}

Meio *removerMeio(Meio **inicio, int adr, int i){ 
    Meio *aux;

    if (!*inicio){
        printf("A base de dados esta vazia");
        return NULL;
    }

    if(!(existeMeio((*inicio), adr))){
        printf("Nao existe nenhum meio de transporte resgistado com esse codigo...\n");
        return NULL;
    }
    
    if (((*inicio)->codigo == adr) && i == 1){
        aux = (*inicio)->next;
        free((*inicio));
        (*inicio) = aux;
        return aux;
    }else if ((*inicio)->codigo == adr){
        aux = (*inicio)->next;
        free((*inicio));
        return aux;
    }else{
        (*inicio)->next = removerMeio(&(*inicio)->next, adr, ++i);
        return (*inicio);
    }
}



void alugarMeio(Meio *inicio, Clientes *alugar, int id){
    
    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->aluguer = alugar;
}


void terminarAluguer(Meio *inicio, Clientes *alugar, int id){

    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->aluguer = NULL;
}