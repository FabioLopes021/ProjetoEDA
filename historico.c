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
    new->inicio = start;
    new->fim = end;

    new->next = (*inicio);
    (*inicio) = new;
}

void inserirHistoricoInicio(Historico** inicio, int idc, int idm, float custo, char localinicial[]){
    Historico *new;
    time_t t = time(NULL);
    
    new = (Historico *) malloc(sizeof(Historico));

    new->idCliente = idc;
    new->idMeio = idm;
    new->id = generateidHistorico(*inicio);
    new->Custo = custo;
    new->custoFinal = 0;
    new->inicio = *localtime(&t);
    strcpy(new->localinicial, localinicial);

    new->next = (*inicio);
    (*inicio) = new;    
}


int inserirHistoricoFinal(Historico* inicio, int ide){
    time_t t = time(NULL);
    double custof;    

    if(!inicio)
        return 0;

    while(inicio != NULL && inicio->id != ide)
        inicio = inicio->next;

    inicio->fim = *localtime(&t);
    inicio->custoFinal = calculoCustoTotal(inicio, ide); 

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

double calculoCustoTotal(Historico *entrada, int ide){
    double seg, min;
    time_t startTime, endTime;

    while(entrada != NULL && entrada->id != ide)
        entrada = entrada->next;


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
        printf("ID Historico: %d\n", inicio->id);
        printf("ID Cliente: %d\n", inicio->idCliente);
        printf("ID Meio: %d\n", inicio->idMeio);
        printf("Inicio do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
            inicio->inicio.tm_mday, inicio->inicio.tm_mon + 1, inicio->inicio.tm_year + 1900,
            inicio->inicio.tm_hour, inicio->inicio.tm_min, inicio->inicio.tm_sec);
        printf("Fim do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
            inicio->fim.tm_mday, inicio->fim.tm_mon + 1, inicio->fim.tm_year + 1900,
            inicio->fim.tm_hour, inicio->fim.tm_min, inicio->fim.tm_sec);
        printf("Custo Meio (minuto): %.2f\n", inicio->Custo);
        printf("Custo Total: %.2f\n", inicio->custoFinal);

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
            printf("ID Historico: %d\n", inicio->id);
            printf("ID Cliente: %d\n", inicio->idCliente);
            printf("ID Meio: %d\n", inicio->idMeio);
            printf("Inicio do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
                inicio->inicio.tm_mday, inicio->inicio.tm_mon + 1, inicio->inicio.tm_year + 1900,
                inicio->inicio.tm_hour, inicio->inicio.tm_min, inicio->inicio.tm_sec);
            printf("Fim do aluguer: %02d/%02d/%04d %02d:%02d:%02d\n", 
                inicio->fim.tm_mday, inicio->fim.tm_mon + 1, inicio->fim.tm_year + 1900,
                inicio->fim.tm_hour, inicio->fim.tm_min, inicio->fim.tm_sec);
            printf("Custo Meio (minuto): %.2f\n", inicio->Custo);
            printf("Custo Total: %.2f\n", inicio->custoFinal);

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
    time_t t = time(NULL);
    int id, idc, idm;
    float custo;
    double custofinal;
    char teste[20];
    struct tm start;
    struct tm end;
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5;
    char *campoi1, *campoi2, *campoi3, *campoi4, *campoi5, *campoi6, *campoi7, *campoi8, *campoi9, *campoi10;// *campoi11; 
    char *campof1, *campof2, *campof3, *campof4, *campof5, *campof6, *campof7, *campof8, *campof9, *campof10;// *campof11; 
    start = *localtime(&t);
    end = *localtime(&t);
    
    fp = fopen("hist.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campoi1 = strtok(NULL, ";");
			campoi2 = strtok(NULL, ";");
			campoi3 = strtok(NULL, ";");
			campoi4 = strtok(NULL, ";");
			campoi5 = strtok(NULL, ";");
			campoi6 = strtok(NULL, ";");
			campoi7 = strtok(NULL, ";");
			campoi8 = strtok(NULL, ";");
			campoi9 = strtok(NULL, ";");
			campoi10 = strtok(NULL, ";");
			//campoi11 = strtok(NULL, ";");
            campof1 = strtok(NULL, ";");
			campof2 = strtok(NULL, ";");
			campof3 = strtok(NULL, ";");
			campof4 = strtok(NULL, ";");
			campof5 = strtok(NULL, ";");
			campof6 = strtok(NULL, ";");
			campof7 = strtok(NULL, ";");
			campof8 = strtok(NULL, ";");
			campof9 = strtok(NULL, ";");
			campof10 = strtok(NULL, ";");
			//campof11 = strtok(NULL, ";");
            
            id = atoi(campo1);
            idc = atoi(campo2);
            idm = atoi(campo3);
            custo = atof(campo4);
            custofinal = atof(campo5);
			start.tm_hour = atoi(campoi1); 
			start.tm_isdst = atoi(campoi2); 
			start.tm_mday = atoi(campoi3); 
			start.tm_min = atoi(campoi4); 
			start.tm_mon = atoi(campoi5); 
			start.tm_sec = atoi(campoi6); 
			start.tm_wday = atoi(campoi7); 
			start.tm_yday = atoi(campoi8); 
			start.tm_year = atoi(campoi9); 
			start.tm_gmtoff = atol(campoi10);


			end.tm_hour = atoi(campof1); 
			end.tm_isdst = atoi(campof2); 
			end.tm_mday = atoi(campof3); 
			end.tm_min = atoi(campof4); 
			end.tm_mon = atoi(campof5); 
			end.tm_sec = atoi(campof6); 
			end.tm_wday = atoi(campof7); 
			end.tm_yday = atoi(campof8); 
			end.tm_year = atoi(campof9); 
			end.tm_gmtoff = atol(campof10);
			
            inserirHistorico(&(*inicio), idc, idm, id, custofinal, custo, start, end);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}

}



void guardarHistorico(Historico* inicio){
    FILE* fp;

    fp = fopen("hist.txt","w");

    if (fp!=NULL){
        
        while (inicio != NULL){
        fprintf(fp,"%d;%d;%d;%.2f;%.2f", inicio->id, inicio->idCliente, inicio->idMeio, inicio->Custo, inicio->custoFinal); 
        fprintf(fp,";%d;%d;%d;%d;%d;%d;%d;%d;%d;%ld", inicio->inicio.tm_hour, inicio->inicio.tm_isdst, inicio->inicio.tm_mday
        , inicio->inicio.tm_min, inicio->inicio.tm_mon, inicio->inicio.tm_sec, inicio->inicio.tm_wday, inicio->inicio.tm_yday, inicio->inicio.tm_year,
         inicio->inicio.tm_gmtoff);
        //fprintf(fp,"%s;", inicio->inicio.tm_zone);
        fprintf(fp,";%d;%d;%d;%d;%d;%d;%d;%d;%d;%ld\n", inicio->fim.tm_hour, inicio->fim.tm_isdst, inicio->fim.tm_mday
        , inicio->fim.tm_min, inicio->fim.tm_mon, inicio->fim.tm_sec, inicio->fim.tm_wday, inicio->fim.tm_yday, inicio->fim.tm_year,
         inicio->fim.tm_gmtoff);
        //fprintf(fp,"%s\n", inicio->fim.tm_zone);
        inicio = inicio->next;
        }
        
        fclose(fp);

        printf("Historico guardado com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro do Historico\n");
}



void lerHistoricoBin(Historico **inicio){
    FILE *fp;
    Historico *new;

    new = (Historico *) malloc(sizeof(Historico));

    fp = fopen("histt.bin", "rb");

    if(fp != NULL){

       while (fread(new, sizeof(Historico), 1, fp) == 1) {
            if(new != NULL){
                inserirHistorico(&(*inicio), new->idCliente, new->idMeio, new->id, new->custoFinal, new->Custo, new->inicio, new->fim);
            }
             
        }
        free(new);
        fclose(fp);

        printf("Meios binarios lidos com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}



void guardarHistoricoBin(Historico *inicio){
    FILE *fp;

    fp = fopen("histt.bin", "wb");

    if(fp != NULL){

        while (inicio != NULL) {
            fwrite(inicio, sizeof(Historico), 1, fp);
            inicio = inicio->next;
        }

        fclose(fp);

        printf("Meios guardados em binario com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}