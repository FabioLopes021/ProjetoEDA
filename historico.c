#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "historico.h"
#include "grafo.h"


/**
 * @brief Insere um novo registo de histórico no início da lista ligada.
 *
 * @param inicio Apontador para o ponteiro do início da lista ligada.
 * @param idc ID do cliente.
 * @param idm ID do meio de transporte.
 * @param ide ID do histórico.
 * @param custof Custo final.
 * @param custo Custo.
 * @param localinicial Local inicial.
 * @param localfinal Local final.
 * @param start Struct contendo o horário de início.
 * @param end Struct contendo o horário de fim.
 */
void inserirHistorico(Historico** inicio, int idc, int idm, int ide, double custof, float custo, char localinicial[], char localfinal[], struct tm start, struct tm end){
    Historico *new;

    new = (Historico *) malloc(sizeof(Historico));

    new->idCliente = idc;
    new->idMeio = idm;
    new->id = ide;
    new->custoFinal = custof;
    new->Custo = custo;
    new->inicio = start;
    new->fim = end;
    strcpy(new->localinicial, localinicial);
    strcpy(new->localfinal, localfinal);

    new->next = (*inicio);
    (*inicio) = new;
}


/**
 * @brief Insere um novo registo de histórico no início da lista ligada (apenas com os dados de inicio do aluguer).
 *
 * @param inicio apontador para o apontador do início da lista ligada.
 * @param idc ID do cliente.
 * @param idm ID do meio de transporte.
 * @param custo Custo.
 * @param localinicial Local inicial.
 */
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
    t = 0;
    new->fim = *localtime(&t);
    strcpy(new->localinicial, localinicial);
    strcpy(new->localfinal, "");

    new->next = (*inicio);
    (*inicio) = new;    
}


/**
 * @brief Insere o local final e calcula o custo final de um registro de histórico.
 *
 * @param inicio Apontador para o início da lista ligada.
 * @param ide ID do histórico.
 * @param localfinal Local final.
 *
 * @return 1 se o registro de histórico for encontrado e atualizado com sucesso, 0 caso contrário.
 */
int inserirHistoricoFinal(Historico* inicio, int ide, char localfinal[]){
    time_t t = time(NULL);
    double custof;    

    if(!inicio)
        return 0;

    while(inicio != NULL && inicio->id != ide)
        inicio = inicio->next;

    inicio->fim = *localtime(&t);
    inicio->custoFinal = calculoCustoTotal(inicio, ide);
    strcpy(inicio->localfinal, localfinal);

    return 1;     
}

/**
 * @brief Remove um registro de histórico da lista ligada.
 *
 * @param inicio Apontador para o apontador do início da lista ligada.
 * @param id ID do histórico a ser removido.
 * @param i Variável auxiliar para controle recursivo.
 *
 * @return Apontador para o início da lista após a remoção.
 */
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


/**
 * @brief Verifica se um registro de histórico com o ID especificado existe na lista.
 *
 * @param inicio Apontador para o início da lista ligada.
 * @param id ID do histórico a ser verificado.
 *
 * @return 1 se o registro de histórico existe, 0 caso contrário.
 */
int existeHistorico(Historico* inicio, int id){
    if (!inicio)
        return 0;
    
    if (inicio->id == id)   
        return 1;
    return existeHistorico(inicio->next, id);
}


/**
 * @brief Calcula o custo total de um registro de histórico com base no tempo de início e fim.
 *
 * @param entrada Apontador para a lista ligada do historico.
 * @param ide ID do histórico.
 *
 * @return Custo total do registro de histórico.
 */
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



/**
 * @brief Calcula a distância entre dois pontos de um registro de histórico.
 *
 * @param entrada Apontador para a lista ligada do historico.
 * @param v Apontador para a lista ligada de vértices.
 * @param ide ID do histórico.
 *
 * @return A distância entre os pontos de início e fim do registro de histórico.
 */
float calculoDist(Historico *entrada, VerticeList *v, int ide){
    int inicial, final;

    if (entrada == NULL)
        return -1;

    while(entrada != NULL && entrada->id != ide)
        entrada = entrada->next;

    verticePorGeocode(v, &inicial, entrada->localinicial);
    verticePorGeocode(v, &final, entrada->localfinal);

    return menorCaminho(v, inicial, final);
}

/**
 * @brief Obtém o ID de um registro de histórico com base no ID do meio.
 *
 * @param entrada Apontador para o início da lista ligada de históricos.
 * @param idm ID do meio.
 *
 * @return O ID do histórico correspondente ao ID do meio, se existir. Caso contrário, retorna 0.
 */
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

/**
 * @brief Gera um novo ID para um registro de histórico.
 *
 * @param inicio Apontador para o início da lista ligada de históricos.
 *
 * @return O novo ID gerado para o histórico.
 */
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


/**
 * @brief Imprime todos os registros de histórico.
 *
 * @param inicio Apontadro para o início da lista ligada do histórico.
 * @param v Apontador para a lista ligada de vértices.
 *
 * @return 1 se houver registros de histórico para imprimir, 0 caso contrário.
 */
int imprimirHistorico(Historico *inicio,VerticeList *v){

    if(!inicio)
        return 0;

    printf("\n--------------HISTORICO------------------\n");

    while(inicio != NULL){
        printf("ID Historico: %d\n", inicio->id);
        printf("ID Cliente: %d\n", inicio->idCliente);
        printf("ID Meio: %d\n", inicio->idMeio);
        printf("Local inicio: %s\n", NOME_PONTOS[auxprinthistorico(v, inicio->localinicial)]);
        printf("Local final: %s\n", NOME_PONTOS[auxprinthistorico(v, inicio->localfinal)]);
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


/**
 * @brief Imprime os registros de histórico de um cliente específico.
 *
 * @param inicio Apontador para o início da lista ligada do histórico.
 * @param v Apontador para a lista ligada de vértices.
 * @param id ID do cliente.
 *
 * @return 1 se houver registros de histórico do cliente para imprimir, 0 caso contrário.
 */
int imprimirHistoricoCliente(Historico *inicio,VerticeList *v, int id){
    if(!inicio)
        return 0;

    printf("\n----------HISTORICO CLIENTE--------------\n");

    while(inicio != NULL){
        if (inicio->idCliente == id){
            printf("ID Historico: %d\n", inicio->id);
            printf("ID Cliente: %d\n", inicio->idCliente);
            printf("ID Meio: %d\n", inicio->idMeio);
            printf("Local inicio: %s\n", NOME_PONTOS[auxprinthistorico(v, inicio->localinicial)]);
            printf("Local final: %s\n", NOME_PONTOS[auxprinthistorico(v, inicio->localfinal)]);
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



/**
 * @brief Obtém o número de registros de histórico associados a um cliente específico.
 *
 * @param inicio Apontadro para o início da lista ligada do histórico.
 * @param id ID do cliente.
 *
 * @return O número de registros de histórico associados ao cliente.
 */
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


/**
 * @brief Lê os registros de histórico de um ficheiro txt e os insere na lista ligada.
 *
 * @param inicio Apontador para o apontador do início da lista ligada do histórico.
 */
void readHistorico(Historico **inicio){
    FILE* fp;
    int id, idc, idm;
    float custo;
    double custofinal;
    struct tm start;
    struct tm end;
    char line[1024], localinicial[MAX_GEOCODE], localfinal[MAX_GEOCODE];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7, *campo8, *campo9, *aux = NULL;
    time_t tempoinic, tempofinal;
    
    fp = fopen("hist.txt","r");


    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

            campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");
			campo7 = strtok(NULL, ";");
			campo8 = strtok(NULL, ";");
			campo9 = strtok(NULL, ";");

            id = atoi(campo1);
            idc = atoi(campo2);
            idm = atoi(campo3);
            custo = atof(campo4);
            custofinal = atof(campo5);
            strcpy(localinicial, campo6);
            strcpy(localfinal, campo7);
            tempoinic = strtol(campo8,&aux,10);
            aux = NULL;
            tempofinal = strtol(campo9,&aux,10);

            start = *localtime(&tempoinic);
            end = *localtime(&tempofinal);

            if(strcmp(localfinal,"Nao atribuido") == 0)
                strcpy(localfinal, "");
			
            inserirHistorico(&(*inicio), idc, idm, id, custofinal, custo, localinicial, localfinal, start, end);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	} 

}


/**
 * @brief guarda os registros de histórico da lista ligada num ficheiro txt.
 *
 * @param inicio Apontador para o início da lista ligada do histórico.
 */
void guardarHistorico(Historico* inicio){
    FILE* fp;
    time_t timeinit, fim;

    fp = fopen("hist.txt","w");

    if (fp!=NULL){
        
        while (inicio != NULL){
            if(strcmp(inicio->localfinal, "") == 0){
                strcpy(inicio->localfinal, "Nao atribuido");
            }
            timeinit = mktime(&(inicio->inicio));
            fim = mktime(&(inicio->fim));
            fprintf(fp,"%d;%d;%d;%.2f;%.2f;%s;%s;", inicio->id, inicio->idCliente, inicio->idMeio, inicio->Custo, inicio->custoFinal, inicio->localinicial, inicio->localfinal); 
            fprintf(fp,"%ld;%ld\n", timeinit, fim);
            inicio = inicio->next;
        }
        
        fclose(fp);

        printf("Historico guardado com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro do Historico\n");
}


/**
 * @brief Lê os registros de histórico de um arquivo binário e os insere na lista ligada.
 *
 * @param inicio Apontador para o apontador do início da lista de históricos.
 */
void lerHistoricoBin(Historico **inicio){
    FILE *fp;
    Historico *new;

    new = (Historico *) malloc(sizeof(Historico));

    fp = fopen("histt.bin", "rb");

    if(fp != NULL){

       while (fread(new, sizeof(Historico), 1, fp) == 1) {
            if(new != NULL){
                inserirHistorico(&(*inicio), new->idCliente, new->idMeio, new->id, new->custoFinal, new->Custo, new->localinicial, new->localfinal, new->inicio, new->fim);
            }
             
        }
        free(new);
        fclose(fp);

        printf("Meios binarios lidos com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}


/**
 * @brief Guarda os registros de histórico da lista ligada num ficheiro binário.
 *
 * @param inicio Apontador para o início da lista ligada de históricos.
 */
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