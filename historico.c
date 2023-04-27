#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "historico.h"


void inserirHistoricoInicio(Historico** inicio, int idc, int idm, float custo){
    Historico *new;
    time_t t = time(NULL);
    
    new = (Historico *) malloc(sizeof(Historico));

    new->idCliente = idc;
    new->idMeio = idm;
    new->id = generateidHistorico(inicio);
    new->Custo = custo;
    new->custoFinal = 0;
    new->inicio = *localtime(&t);

    new->next = (*inicio);
    (*inicio) = new;    
}


int inserirHistoricoFinal(Historico* inicio, int ide){
    time_t t = time(NULL);
    

    if(!inicio)
        return 0;
    
    while(inicio != NULL || inicio->id != ide)
        inicio = inicio->next;

    inicio->fim = *localtime(&t);
    inicio->Custo = calculoCustoTotal(inicio); 

    return 1;     
}

Historico *removerHistorico(Historico **inicio, int id, int i){
    Historico *aux;

    if (!*inicio){
        printf("A base de dados esta vazia\n");
        return NULL;
    }

    if(!(existeHistorico((*inicio), id))){
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
        (*inicio)->next = removerHistorico(&(*inicio)->next, id, ++i);
        return (*inicio);
    }
}

int existeHistorico(Historico* inicio, int id){
    if (!inicio)
        return 0;
    
    if (inicio->id == id)   
        return 1;
    return existeHistorico(inicio->next, id);
}

double calculoCustoTotal(Historico *entrada){
    double seg, min;
    time_t startTime, endTime;

    startTime = mktime(&(entrada->inicio));
    endTime = mktime(&(entrada->fim));
    
    seg = difftime(endTime, startTime);
    min = seg/60;

    return min * entrada->Custo;
}


int generateidHistorico(Historico *inicio){
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