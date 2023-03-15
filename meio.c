#include "meio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float custo){
    Meio *new;
    
    new = (Meio *) malloc(sizeof(Meio));

    new->codigo = cod;
    strcpy(new->tipo, tipo);
    new->bateria = bat;
    new->autonomia = aut;
    new->custo = custo;

    new->next = (*inicio);
    (*inicio) = new;
}

void lerDadosMeio(Meio** inicio){
    char tipo[MAX_NAME];
    int cod = 0,i = 0, bat;
    float aut, custo;

    while ((getchar()) != '\n');

    generico();
    printf("\n--------------- Adicionar Meio ---------------");
    printf("\nIndique o tipo de meio: ");
    fgets(tipo, MAX_NAME, stdin);
    tipo[strlen(tipo)-1] = '\0';

    do{
    if(i == 0)
        printf("Indique um codigo para o meio: ");
    if(i > 0)
        printf("Indique um codigo valido: ");
    scanf("%d", &cod);
    i++;
    }while(existeMeio((*inicio), cod));

    printf("Indique a bateria do meio: ");
    scanf("%d", &bat);

    printf("Indique a autonomia do meio: ");
    scanf("%f", &aut);

    printf("Indique o custo por km do meio: ");
    scanf("%f", &custo);
    
    inserirMeio(&(*inicio), cod, tipo, bat, aut, custo);
}

int existeMeio(Meio* inicio, int codigo){
    if (!inicio)
        return 0;
    if (inicio->codigo == codigo)   
        return 1;
    return existeMeio(inicio->next, codigo);
}

int meioLivre(Meio* inicio, int codigo){
    if (!inicio)
        return 0;

    if (inicio->codigo == codigo){
        if (inicio->aluguer == NULL)
            return 1;
        else 
            return 0;
    }
        
    return meioLivre(inicio->next, codigo);
}

int meioAlugado(Meio* inicio, int codigo, Clientes *ver){
    
    if (!inicio)
        return 0;

    if (inicio->codigo == codigo){
        if (inicio->aluguer == ver)
            return 1;
        else 
            return 0;
    }
        
    return meioAlugado(inicio->next, codigo, ver);
}


int listarMeios(Meio* inicio, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return 0;
    }
        

    
    if (i == 0){
        printf(" -------------------------------------------------------------------\n");
        printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(Km)  |\n");
        printf("|-------------------------------------------------------------------|\n");
    }
    printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo);
    

    listarMeios(inicio->next, ++i);
}

int listarMeiosLivres(Meio* inicio, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return 0;
    }
        

    if (inicio->aluguer == NULL){
        if (i == 0){
            printf(" -------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(Km)  |\n");
            printf("|-------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo);
        i++;
    }
    
    listarMeiosLivres(inicio->next, i);
}

int listarMeiosAlugados(Meio* inicio, Clientes *c, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return i;
    }
        
    if(inicio->aluguer == c){
        if (i == 0){
            printf(" -------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(Km)  |\n");
            printf("|-------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo);
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


void alterarTipoMeio(Meio *inicio, char tipo[], int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (strlen(tipo) > MIN_NAME){
        strcpy(inicio->tipo, tipo);
    }

}


void alterarBateria(Meio *inicio, int bat, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (bat > 0 && bat < 100){
        inicio->bateria = bat;
    }

}

void alterarAutonomia(Meio *inicio, float aut, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (aut > 0 && aut < 100){
        inicio->autonomia = aut;
    }
}


void alterarCusto(Meio *inicio, float custo, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (custo > 0 && custo < 100){
        inicio->custo = custo;
    }

}



void readMeios(Meio **inicio){
    FILE* fp;
    int cod, bat;
    float aut, custo;
    char tipo[MAX_CODE];
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5;

    fp = fopen("meios.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");

			cod = atoi(campo1);
			bat = atoi(campo2);
			aut = atof(campo3);
			custo = atof(campo4);
            strcpy(tipo, campo5);
            tipo[strlen(tipo) - 1] = '\0';

            inserirMeio(&(*inicio), cod, tipo, bat, aut, bat);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}


void guardarMeios(Meio* inicio){
    FILE* fp;

    fp = fopen("meios.txt","w");

    if (fp!=NULL){
        
        while (inicio != NULL){
        fprintf(fp,"%d;%d;%f;%f;%s\n", inicio->codigo, inicio->bateria, inicio->autonomia, inicio->custo, inicio->tipo);
        inicio = inicio->next;
        }

        fclose(fp);

        printf("Meios guardados com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro\n");
}



void ordenarMeios(Meio **inicio){
    Meio *h, *c, *d, *aux, *auxn;
    int b = 1,i = 0;

    h = (*inicio);
    c = h->next;
    d = c->next;
    
    if(c == NULL){

    }else   if (d == NULL){

        if ((c->autonomia > h->autonomia)){
            auxn = c->next;
            aux = h;
            (*inicio) = c;
            (*inicio)->next = aux;
            c = h;
            c->next = auxn;
        }

    }else{

        while (b) {
            b = 0;
            i = 0;
            h = (*inicio);
            c = h->next;
            d = c->next;
            for (; d != NULL; c = c->next, h = h->next, d = d->next) {
                if ((c->autonomia > h->autonomia) && (i == 0)){
                    auxn = c->next;
                    aux = h;
                    (*inicio) = c;
                    (*inicio)->next = aux;
                    c = h;
                    c->next = auxn;
                    h = (*inicio);
                    b = 1;
                }
                if (d->autonomia > c->autonomia){
                    auxn = d->next;
                    aux = c;
                    c = d;
                    c->next = aux;
                    d = aux;
                    d->next = auxn;
                    h->next = c;
                    b = 1;
                }
                i++;
            }
	    }
    }
}