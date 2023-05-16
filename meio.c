#include "meio.h"
#include "grafo.h"
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
void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float autMax, float custo, int idaluguer, char geocode[]){
    Meio *new;
    
    new = (Meio *) malloc(sizeof(Meio));

    new->codigo = cod;
    strcpy(new->tipo, tipo);
    new->bateria = bat;
    new->autonomia = aut;
    new->autonomiaMax = autMax;
    new->custo = custo;
    new->idaluger = idaluguer;
    strcpy(new->geocode, geocode);

    new->next = (*inicio);
    (*inicio) = new;
}


/**
 * @brief Funçao para ler os dados de um Meio e inseri-lo na lista ligada dos Meios
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void lerDadosMeio(Meio** inicio, VerticeList *v){
    char tipo[MAX_NAME];
    char geocode[MAX_GEOCODE];
    int cod = 0,i = 0, bat, vertice, ver, teste;
    float aut, custo, autMax;

    strcpy(geocode, "");
    clearbuffer();

    generico();
    printf("\n--------------- Adicionar Meio ---------------");
    printf("\nIndique o tipo de meio: ");
    fgets(tipo, MAX_NAME, stdin);
    tipo[strlen(tipo)-1] = '\0';

    cod = genereateCodigo(*inicio);

    printf("Indique a autonomia maxima do meio: ");
    scanf("%f", &autMax);

    printf("Indique a autonomia atual do meio: ");
    scanf("%f", &aut);

    bat = CalculoBateria(autMax, aut);

    printf("Indique o custo por km do meio: ");
    scanf("%f", &custo);

    ver = printGeocodeVertice(v);
    printf("testar meio sem localizaçao 1 para continuar sem localizaçao");
    scanf("%d", &teste);
    clearbuffer();
    if (ver == 1 && teste != 1){
        int i = 0;
        do{
            if (i == 0)
                printf("Indique a localizaçao do meio: ");
            else
                printf("Indique uma localizaçao valida: ");
            scanf("%d", &vertice);
            i++;
        }while(geocodePorVertice(v, vertice, geocode) != 1);
    }else{
        printf("De momento nao existe nenhuma localizaçao adicionada, o meio ira ser registado sem localizaçao.\n");
    }
    
    inserirMeio(&(*inicio), cod, tipo, bat, aut, custo, 0, geocode);
}


int AtualizarBateria(Meio *inicio, int id , float distPrec){
    if(!inicio)
        return 0;

    while(inicio->codigo != id)
        inicio = inicio->next;
    
    inicio->bateria = CalculoBateria(inicio->autonomiaMax, inicio->autonomia - distPrec);

    return 1; 
}


float CalculoBateria(float autonomiaMax, float autonomia ){
    
    return 100 * autonomiaMax / autonomia; 
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


char* localatual(Meio* inicio, int codigo){
    if (inicio == NULL)
        return "";

    while(inicio->codigo != codigo){
        inicio = inicio->next;
    }

    return inicio->geocode;
}

int atuallizarLocalizacao(Meio* inicio, VerticeList *v, int codigo, char novolocal[]){

    if (inicio == NULL)
        return 0;
    
    while(inicio->codigo != codigo){
        inicio = inicio->next;
    }
    
    strcpy(inicio->geocode, novolocal);
    return 1;
}

/**
 * @brief Funçao verifica o numero de meios livres
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna o numero de meios livres existentes
 */
int NumMeiosLivres(Meio* inicio){
    int count = 0;

    if (!inicio)
        return 0;

    while (inicio != NULL){
        if(inicio->idaluger == 0 && strcmp(inicio->geocode, "") != 0){
            count ++;
        }
        inicio = inicio->next;
    }
    
    return count;
}


int NumMeiosSemLocalizacao(Meio* inicio){
    int count = 0;

    if (!inicio)
        return 0;

    while (inicio != NULL){
        if(inicio->idaluger == 0 && strcmp(inicio->geocode, "") == 0){
            count ++;
        }
        inicio = inicio->next;
    }
    
    return count;
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
        if (inicio->idaluger == 0 && strcmp(inicio->geocode, "") != 0)
            return 1;
        else 
            return 0;
    }
        
    return meioLivre(inicio->next, codigo);
}


int meioSemLocalizacao(Meio* inicio, int codigo){
    if (!inicio)
        return 0;

    if (inicio->codigo == codigo){
        if (inicio->idaluger == 0 && strcmp(inicio->geocode, "") == 0)
            return 1;
        else 
            return 0;
    }
        
    return meioSemLocalizacao(inicio->next, codigo);
}


/**
 * @brief Funçao que verifica se um meio esta alugado a um determinado cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param codigo Codigo do meio a verificar
 * @param ver Cliente a verificar
 * @return int retorna 1 se o Meio estiver alugado ao cliente, 0 caso contrario
 */
int meioAlugado(Meio* inicio, int codigo, int idCliente){
    
    if (!inicio)
        return 0;

    if (inicio->codigo == codigo){
        if (inicio->idaluger == idCliente)
            return 1;
        else 
            return 0;
    }
        
    return meioAlugado(inicio->next, codigo, idCliente);
}


/**
 * @brief Funçao que lista todos os meios
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param i contador da funçao
 * @return int retorna 0 quando atingir o fim da lista ou se a mesma se encontrar vazia
 */
int listarMeios(Meio* inicio, VerticeList *v, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return 0;
    }
        

    if (i == 0){
        printf(" -------------------------------------------------------------------\n");
        printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min)  |  Local  |\n");
        printf("|-------------------------------------------------------------------|\n");
    }
    if(auxprinthistorico(v, inicio->geocode) == -1){
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |---------------|\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia
    , inicio->custo);
    }else{
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-15s  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia
    , inicio->custo, NOME_PONTOS[auxprinthistorico(v, inicio->geocode)]);
    }
    
    

    listarMeios(inicio->next, v, ++i);
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
        

    if ((inicio->idaluger == 0) && (strcmp(inicio->geocode,"") != 0)){
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


int listarMeiosSemLocalizacao(Meio* inicio, int i){
    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return 0;
    }
        

    if ((inicio->idaluger == 0) && (strcmp(inicio->geocode,"") == 0)){
        if (i == 0){
            printf(" -------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min)  |  Local  |\n");
            printf("|-------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |---------------|\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia
    , inicio->custo);
        i++;
    }
    
    listarMeiosSemLocalizacao(inicio->next, i);
}


/**
 * @brief Funçao que lista todos os meios alugados a um determinado cliente
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param c Cliente a ser verificado
 * @param i contador da funçao 
 * @return int retorna 0 quando atingir o fim da lista ou se a mesma se encontrar vazia
 */
int listarMeiosAlugados(Meio* inicio, int idCliente, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------\n");
        return i;
    }
        
    if(inicio->idaluger == idCliente){
        if (i == 0){
            printf(" -------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(Km)  |\n");
            printf("|-------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo);
        i++;
    }
    
    listarMeiosAlugados(inicio->next, idCliente, i);
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
void alugarMeio(Meio *inicio, int idCliente, int id){
    
    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->idaluger = idCliente;
}

/**
 * @brief Funçao para terminar o aluguer de um Meio
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param id Codigo do meio
 */
void terminarAluguer(Meio *inicio, int id){

    while(inicio != NULL && inicio->codigo != id){
        inicio = inicio->next;
    }

    inicio->idaluger = 0;
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

    inicio->autonomia = aut;
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
int genereateCodigo(Meio *inicio){
    int max = 1;

    if (!inicio)
        return max;

    while( inicio != NULL){
        if (max < inicio->codigo)
            max = inicio->codigo;

        inicio = inicio->next;
    }

    return ++max;
}

float custoMeio(Meio *inicio, int id){
    if (!inicio)
        return 0;

    while(inicio != NULL){
        if(inicio->codigo == id)
            return inicio->custo;
        inicio = inicio->next;
    }
    return 0;
}


/* float CalculoAutonomia(Meio *inicio, int id){
    float calc;

    if (!inicio)
        return 0;

    while(inicio->codigo != id){
            inicio = inicio->next;
    }

    calc = inicio->bateria * ;
} */


/**
 * @brief Funçao para carregar os Meios e os seus dados do ficheiro 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void readMeios(Meio **inicio){
    FILE* fp;
    int cod, bat,idaluguer;
    float aut, custo;
    char tipo[MAX_CODE], geocode[MAX_GEOCODE];
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7;

    fp = fopen("meios.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");
			campo7 = strtok(NULL, ";");

			cod = atoi(campo1);
			bat = atoi(campo2);
			aut = atof(campo3);
			custo = atof(campo4);
            idaluguer = atoi(campo5);
            strcpy(tipo, campo6);
            strcpy(geocode, campo7);
            geocode[strlen(geocode) - 1] = '\0';

            inserirMeio(&(*inicio), cod, tipo, bat, aut, custo, idaluguer, geocode);
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
        fprintf(fp,"%d;%d;%.2f;%.2f;%.2f;%d;%s;%s\n", inicio->codigo, inicio->bateria, inicio->autonomia, inicio->autonomiaMax, inicio->custo, inicio->idaluger, inicio->tipo, inicio->geocode);
        inicio = inicio->next;
        }

        fclose(fp);

        printf("Meios guardados com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro\n");
}


/**
 * @brief Funçao para guardar os Meios e os seus dados num ficheiro binario
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void guardarMeioBin(Meio *inicio){
    FILE *fp;

    fp = fopen("meioss.bin", "wb");

    if(fp != NULL){

        while (inicio != NULL) {
            fwrite(inicio, sizeof(Meio), 1, fp);
            inicio = inicio->next;
        }

        fclose(fp);

        printf("Meios guardados em binario com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}


/**
 * @brief Funçao para carregar os cliente e os seus dados do ficheiro binario
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void lerMeioBin(Meio **inicio){
    FILE *fp;
    Meio *new;

    new = (Meio *) malloc(sizeof(Meio));

    fp = fopen("meioss.bin", "rb");

    if(fp != NULL){

       while (fread(new, sizeof(Meio), 1, fp) == 1) {
            if(new != NULL){
                inserirMeio(&(*inicio), new->codigo, new->tipo, new->bateria, new->autonomia, new->autonomiaMax, new->custo, new->idaluger, new->geocode);
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
 * @brief Funçao que ordena a lista ligada dos Meios por ordem decrescente de autonomia
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 * @return int retorna 1 se a lista foi ordenada com sucesso, 0 caso contrario 
 */
int ordenarMeios(Meio **inicio){
    Meio *firstnode, *secondnode, *prev = NULL, *aux, *auxn;
    int verificar = 1, i;

    if ((*inicio) == NULL) 
        return 0;


    prev = (*inicio);
    firstnode = prev->next;
    if(firstnode != NULL){
        secondnode = firstnode->next;
    }else
        secondnode = NULL;
    

    if( firstnode == NULL){
        return 0;
    }else if(secondnode == NULL){
        if (prev->autonomia < firstnode->autonomia){
            aux = prev;
            auxn = firstnode->next;
            prev = firstnode;
            firstnode = aux;
            prev->next = firstnode;
            firstnode->next = auxn;
            (*inicio) = prev;
        }
        
    }else{
        
        while(verificar){
            verificar = 0;
            prev = (*inicio);
            firstnode = prev->next;
            secondnode = firstnode->next;
            i = 0;
            while(secondnode != NULL){
                if( prev->autonomia  < firstnode->autonomia && i == 0){
                    aux = prev;
                    auxn = firstnode->next;
                    prev = firstnode;
                    firstnode = aux;
                    prev->next = firstnode;
                    firstnode->next = auxn;
                    (*inicio) = prev;
                    verificar = 1;
                }
                if (firstnode->autonomia < secondnode->autonomia){
                    aux = firstnode;
                    auxn = secondnode->next;
                    firstnode = secondnode;
                    secondnode = aux;
                    firstnode->next = secondnode;
                    secondnode->next = auxn;
                    prev->next = firstnode;
                    verificar = 1;
                }
                i++;
                prev = prev->next;
                firstnode = firstnode->next;
                secondnode = secondnode->next;
            }

        }
    }
    return 1;
}