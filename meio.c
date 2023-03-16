#include "meio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Funçao para adicionar um novo Meio a lista ligada de Meios
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 * @param cod Codigo do meio a ser inserido
 * @param tipo Tipo do meio a ser inserido
 * @param bat Bateria do meio a ser inserido
 * @param aut Autonomia do meio a ser inserido
 * @param custo Custo por Km do meio a ser inserido
 */
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


/**
 * @brief Funçao para ler os dados de um Meio e inseri-lo na lista ligada dos Meios
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void lerDadosMeio(Meio** inicio){
    char tipo[MAX_NAME];
    int cod = 0,i = 0, bat;
    float aut, custo;

    clearbuffer();

    generico();
    printf("\n--------------- Adicionar Meio ---------------");
    printf("\nIndique o tipo de meio: ");
    fgets(tipo, MAX_NAME, stdin);
    tipo[strlen(tipo)-1] = '\0';

    cod = genereateCodigo(*inicio);

    printf("Indique a bateria do meio: ");
    scanf("%d", &bat);

    printf("Indique a autonomia do meio: ");
    scanf("%f", &aut);

    printf("Indique o custo por km do meio: ");
    scanf("%f", &custo);
    
    inserirMeio(&(*inicio), cod, tipo, bat, aut, custo);
}


/**
 * @brief Funçao que verifica se um determinado Meio existe
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param codigo Codigo do Meio a verificar
 * @return int retorna 1 se encontrar o Meio, 0 caso contrario
 */
int existeMeio(Meio* inicio, int codigo){
    if (!inicio)
        return 0;
    if (inicio->codigo == codigo)   
        return 1;
    return existeMeio(inicio->next, codigo);
}


/**
 * @brief Funçao que verifica se um meio esta livre
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param codigo Codigo do meio a verificar
 * @return int retorna 1 se o Meio estiver livre, 0 caso contrario
 */
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


/**
 * @brief Funçao que verifica se um meio esta alugado a um determinado cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param codigo Codigo do meio a verificar
 * @param ver Cliente a verificar
 * @return int retorna 1 se o Meio estiver alugado ao cliente, 0 caso contrario
 */
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


/**
 * @brief Funçao que lista todos os meios
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param i contador da funçao
 * @return int retorna 0 quando atingir o fim da lista ou se a mesma se encontrar vazia
 */
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


/**
 * @brief Funçao que lista todos os meios livres
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param i contador da funçao 
 * @return int retorna 0 quando atingir o fim da lista ou se a mesma se encontrar vazia
 */
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


/**
 * @brief Funçao que lista todos os meios alugados a um determinado cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param c Cliente a ser verificado
 * @param i contador da funçao 
 * @return int retorna 0 quando atingir o fim da lista ou se a mesma se encontrar vazia
 */
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


/**
 * @brief Funçao para remover um determinado Meio
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 * @param adr Codigo do Meio a ser removido
 * @param i contador da funçao
 * @return Meio* etorna o endereço do Meio seguinte ao Meio removido da lista, NULL caso o mesmo n seja encontrado
 */
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


/**
 * @brief Funçao para um cliente alugar um meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param alugar Endereço do cliente que quer alugar o meio
 * @param id Codigo do meio
 */
void alugarMeio(Meio *inicio, Clientes *alugar, int id){
    
    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->aluguer = alugar;
}

/**
 * @brief Funçao para terminar o aluguer de um Meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param alugar Endereço do cliente que quer terminar o aluguer o meio
 * @param id Codigo do meio
 */
void terminarAluguer(Meio *inicio, Clientes *alugar, int id){

    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->aluguer = NULL;
}


/**
 * @brief Funçao para alterar o tipo do meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param tipo Tipo novo para o meio
 * @param id Codigo do meio
 */
void alterarTipoMeio(Meio *inicio, char tipo[], int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (strlen(tipo) > MIN_NAME){
        strcpy(inicio->tipo, tipo);
    }

}

/**
 * @brief Funçao para alterar o tipo do meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param bat Nivel novo de bateria para o meio
 * @param id Codigo do meio
 */
void alterarBateria(Meio *inicio, int bat, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (bat > 0 && bat < 100){
        inicio->bateria = bat;
    }

}


/**
 * @brief Funçao para alterar a autonomia do meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param aut Autonomia nova para o meio
 * @param id Codigo do meio
 */
void alterarAutonomia(Meio *inicio, float aut, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (aut > 0 && aut < 100){
        inicio->autonomia = aut;
    }
}



/**
 * @brief Funçao para alterar o custo do meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param custo Custo novo para o meio
 * @param id Codigo do meio
 */
void alterarCusto(Meio *inicio, float custo, int id){

    while(inicio->codigo != id)
        inicio = inicio->next;

    if (custo > 0 && custo < 100){
        inicio->custo = custo;
    }

}


/**
 * @brief Funçao para gerar um codigo unico para um meio 
 * 
 * @param inico Apontador para o inicio da lista ligada
 * @return int retorna o codigo unico para um meio novo
 */
int genereateCodigo(Meio *inico){
    int max = 1;

    if (!inico)
        return max;

    while( inico != NULL){
        if (max < inico->codigo)
            max = inico->codigo;

        inico = inico->next;
    }

    return ++max;
}

/**
 * @brief Funçao para carregar os Meios e os seus dados do ficheiro 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
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

/**
 * @brief Funçao para guardar os Meios e os seus dados em ficheiro
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
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




/**
 * @brief Funçao que ordena a lista ligada dos Meios por ordem decrescente de autonomia
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
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