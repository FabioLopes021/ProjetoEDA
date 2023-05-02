#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "historico.h"


void inserirHistorico(Historico** inicio, int idc, int idm, int ide, double custof, float custo, struct tm start, struct tm end){
    Historico *new;

    new = (Historico *) malloc(sizeof(Historico));

    new->idCliente = idc;
    new->idMeio = idm;
    new->id = ide;
    new->custoFinal = custof;
    new->Custo = custo;
    new->inicio.tm_year = start.tm_year;
    new->inicio.tm_mon = start.tm_mon;
    new->inicio.tm_mday = start.tm_mday;
    new->inicio.tm_hour = start.tm_hour;
    new->inicio.tm_min = start.tm_min;
    new->inicio.tm_sec = start.tm_sec;
    new->fim.tm_year = end.tm_year;
    new->fim.tm_mon = end.tm_mon;
    new->fim.tm_mday = end.tm_mday;
    new->fim.tm_hour = end.tm_hour;
    new->fim.tm_min = end.tm_min;
    new->fim.tm_sec = end.tm_sec;

    new->next = (*inicio);
    (*inicio) = new;
}

void inserirHistoricoInicio(Historico** inicio, int idc, int idm, float custo){
    Historico *new;
    time_t t = time(NULL);
    
    new = (Historico *) malloc(sizeof(Historico));

    new->idCliente = idc;
    new->idMeio = idm;
    new->id = generateidHistorico(*inicio);
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
    
    while(inicio != NULL && inicio->id != ide)
        inicio = inicio->next;

    inicio->fim = *localtime(&t);
    inicio->custoFinal = calculoCustoTotal(inicio); 

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

int idEntrada(Historico *entrada, int idm){
    if(!entrada)
        return 0;
        
    while(entrada != NULL){
        if (entrada->idMeio == idm && entrada->custoFinal == 0)
            return entrada->id;
        entrada = entrada->next;
    }

    return 0;
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

int imprimirHistorico(Historico *inicio){

    if(!inicio)
        return 0;

    printf("\n--------------HISTORICO------------------\n");

    while(inicio != NULL){
        printf("ID Cliente: %d\n", inicio->idCliente);
        printf("ID Meio: %d\n", inicio->idMeio);
        printf("ID Historico: %d\n", inicio->id);
        printf("Inicio do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
            inicio->inicio.tm_mday, inicio->inicio.tm_mon + 1, inicio->inicio.tm_year + 1900,
            inicio->inicio.tm_hour, inicio->inicio.tm_min, inicio->inicio.tm_sec);
        printf("Fim do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
            inicio->fim.tm_mday, inicio->fim.tm_mon + 1, inicio->fim.tm_year + 1900,
            inicio->fim.tm_hour, inicio->fim.tm_min, inicio->fim.tm_sec);
        printf("Custo Meio (minuto): %f\n", inicio->Custo);
        printf("Custo Total: %f\n", inicio->custoFinal);

        if(inicio->next != NULL)
            printf("-----------------------------------------\n");
        inicio = inicio->next;
    }

    return 1;
}

int imprimirHistoricoCliente(Historico *inicio, int id){
    if(!inicio)
        return 0;

    printf("\n----------HISTORICO CLIENTE--------------\n");

    while(inicio != NULL){
        if (inicio->idCliente == id){
            printf("ID Cliente: %d\n", inicio->idCliente);
            printf("ID Meio: %d\n", inicio->idMeio);
            printf("ID Historico: %d\n", inicio->id);
            printf("Inicio do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
                inicio->inicio.tm_mday, inicio->inicio.tm_mon + 1, inicio->inicio.tm_year + 1900,
                inicio->inicio.tm_hour, inicio->inicio.tm_min, inicio->inicio.tm_sec);
            printf("Fim do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
                inicio->fim.tm_mday, inicio->fim.tm_mon + 1, inicio->fim.tm_year + 1900,
                inicio->fim.tm_hour, inicio->fim.tm_min, inicio->fim.tm_sec);
            printf("Custo Meio (minuto): %f\n", inicio->Custo);
            printf("Custo Total: %f\n", inicio->custoFinal);

        if(inicio->next != NULL)
            printf("-----------------------------------------\n");
        }
        
        inicio = inicio->next;
    }

    return 1;
}

int numEntradasCliente(Historico *inicio, int id){
    int i = 0;

    if (!inicio)
        return 0;

    while (inicio != NULL){
        if (inicio->idCliente == id){
            i++;
        }
        inicio = inicio->next;
    }

    return i;
}

void readHistorico(Historico **inicio){
    FILE* fp;
    int id, idc, idm;
    float custo;
    double custofinal;
    struct tm aux;
    char tipo[MAX_CODE];
    struct tm inicio;
    struct tm fim;
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5;
    char *campoi1, *campoi2, *campoi3, *campoi4, *campoi5, *campoi6, *campoi7, *campoi8, *campoi9, *campoi10, *campoi11; 
    char *campof1, *campof2, *campof3, *campof4, *campof5, *campof6, *campof7, *campof8, *campof9, *campof10, *campof11; 

    fp = fopen("hist.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");

			cod = atoi(campo1);
			bat = atoi(campo2);
			aut = atof(campo3);
			custo = atof(campo4);
            idaluguer = atoi(campo5);
            strcpy(tipo, campo6);
            tipo[strlen(tipo) - 1] = '\0';

            inserirMeio(&(*inicio), cod, tipo, bat, aut, bat, idaluguer);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}

}