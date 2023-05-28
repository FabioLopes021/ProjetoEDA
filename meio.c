#include "meio.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * @brief Insere um novo meio no início da lista ligada de meios.
 *
 * @param inicio Apontador para o apontador do início da lista de meios.
 * @param cod Código do meio.
 * @param tipo Tipo do meio.
 * @param bat Bateria do meio.
 * @param aut Autonomia atual do meio.
 * @param autMax Autonomia máxima do meio.
 * @param custo Custo por quilômetro do meio.
 * @param idaluguer ID do aluguer associado ao meio.
 * @param geocode Geocode do meio.
 * @param metrosQ Número de metros quadrados ocupados pelo meio.
 */
void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float autMax, float custo, int idaluguer, char geocode[], int metrosQ){
    Meio *new;
    
    new = (Meio *) malloc(sizeof(Meio));

    new->codigo = cod;
    strcpy(new->tipo, tipo);
    new->bateria = bat;
    new->autonomia = aut;
    new->autonomiaMax = autMax;
    new->custo = custo;
    new->idaluger = idaluguer;
    new->metrosQ = metrosQ;
    strcpy(new->geocode, geocode);

    new->next = (*inicio);
    (*inicio) = new;
}



/**
 * @brief Lê os dados de um novo meio a partir da entrada do utilizador e o insere na lista ligada.
 *
 * @param inicio Apontador para o apontador do início da lista de meios.
 * @param v apontador para a lista de vértices.
 */
void lerDadosMeio(Meio** inicio, VerticeList *v){
    char tipo[MAX_NAME];
    char geocode[MAX_GEOCODE];
    int cod = 0,i = 0, bat, vertice, ver, teste, metQuad;
    float aut, custo, autMax;

    strcpy(geocode, "");
    clearbuffer();

    generico();
    printf("\n--------------- Adicionar Meio ---------------");
    printf("\nIndique o tipo de meio: ");
    fgets(tipo, MAX_NAME, stdin);
    tipo[strlen(tipo)-1] = '\0';

    cod = genereateCodigo(*inicio);

    printf("Indique o numero de metros quadrados que o meio ocupa (inteiro): ");
    scanf("%d", &metQuad);

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
    
    inserirMeio(&(*inicio), cod, tipo, bat, aut, autMax, custo, 0, geocode, metQuad);
}



/**
 * @brief Recarrega a bateria de um meio específico e atualiza sua localização para um posto de carregamento.
 *
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param v Apontador para a lista ligada de vértices.
 * @param idmeio ID do meio a ser recarregado.
 * @param verticePosto ID do vértice do posto de carregamento.
 * @return int Retorna 1 se o meio foi encontrado e recarregado, 0 caso contrário.
 */
int recarregarMeios(Meio *inicio, VerticeList *v, int idmeio, int verticePosto){
    Meio *aux = inicio;
    char geocode[MAX_GEOCODE];

    if (inicio == NULL)
        return 0;

    while( aux != NULL){
        if(aux->codigo == idmeio)
            break;
        aux = aux->next;
    }

    geocodePorVertice(v, verticePosto, geocode);

    aux->autonomia = aux->autonomiaMax;
    aux->bateria = 100;
    strcpy(aux->geocode, geocode);

    return 1;
}


/**
 * @brief Atualiza a autonomia de um meio após um aluger.
 *
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param id ID do meio a ser atualizado.
 * @param distPrec Distância percorrida na operação.
 * @return int Retorna 1 se o meio foi encontrado e a autonomia atualizada, 0 caso contrário.
 */
int AtualizarAutonomia(Meio *inicio, int id , float distPrec){
    if(!inicio)
        return 0;

    while(inicio->codigo != id)
        inicio = inicio->next;
    
    inicio->autonomia -= distPrec;

    return 1; 
}


/**
 * @brief Atualiza a porcentagem de bateria de um meio após um aluguer.
 *
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param id ID do meio a ser atualizado.
 * @param distPrec Distância percorrida na operação.
 * @return int Retorna 1 se o meio foi encontrado e a bateria atualizada, 0 caso contrário.
 */
int AtualizarBateria(Meio *inicio, int id , float distPrec){
    if(!inicio)
        return 0;

    while(inicio->codigo != id)
        inicio = inicio->next;
    
    inicio->bateria = CalculoBateria(inicio->autonomiaMax, inicio->autonomia - distPrec);

    return 1; 
}


/**
 * @brief Calcula a porcentagem de bateria com base na autonomia atual e máxima.
 *
 * @param autonomiaMax Autonomia máxima do meio.
 * @param autonomia Autonomia atual do meio.
 * @return float Porcentagem de bateria.
 */
float CalculoBateria(float autonomiaMax, float autonomia ){
    
    return 100 * autonomia / autonomiaMax; 
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
 * @brief Retorna a localização atual de um meio com base no seu código.
 *
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param codigo Código do meio.
 * @return char* Geocode da localização atual do meio.
 */
char* localatual(Meio* inicio, int codigo){
    if (inicio == NULL)
        return "";

    while(inicio->codigo != codigo){
        inicio = inicio->next;
    }

    return inicio->geocode;
}


/**
 * @brief Atualiza a localização de um meio com base no seu código.
 *
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param v Apontador para a lista ligada de vértices.
 * @param codigo Código do meio.
 * @param novolocal Nova localização do meio.
 * @return int Retorna 1 se o meio foi encontrado e a localização atualizada, 0 caso contrário.
 */
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

/**
 * @brief Conta o número de meios sem localização.
 * 
 * Esta função percorre a lista ligada de meios e conta o número de meios
 * que não possuem uma localização atribuída (geocode é uma string vazia)
 * e que não estão atualmente em uso (idaluger é 0).
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @return O número de meios sem localização.
 */
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

/**
 * @brief Verifica se um determinado meio não possui localização atribuída.
 * 
 * Esta função percorre a lista ligada de meios e verifica se o meio com o
 * código especificado não possui uma localização atribuída (geocode é uma
 * string vazia) e não está atualmente em uso (idaluger é 0).
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @param codigo Código do meio a ser verificado.
 * @return 1 se o meio não possui localização atribuída, 0 caso contrário.
 */
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
 * @param idCliente Id do cliente a verificar
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
 * @brief Lista os meios disponíveis e as suas informações.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @param v Apontador para a lista ligada de vértices contendo as informações de localização.
 * @param i Valor auxiliar para controlar a exibição do cabeçalho da tabela.
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
 * @brief Lista os meios livres e as suas informações.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @param v Apontador para a lista ligada de vértices contendo as informações de localização.
 * @param i Valor auxiliar para controlar a exibição do cabeçalho da tabela.
 */
int listarMeiosLivres(Meio* inicio, VerticeList *v, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------------------------------------\n");
        return 0;
    }
        

    if ((inicio->idaluger == 0) && (strcmp(inicio->geocode,"") != 0)){
        if (i == 0){
            printf(" -------------------------------------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min) |             Local           |\n");
            printf("|-------------------------------------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-25s  | %d\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo,
        NOME_PONTOS[auxPrintMeios(v,inicio)], inicio->metrosQ);
        i++;
    }
    
    listarMeiosLivres(inicio->next, v, i);
}


/**
 * @brief Lista os meios sem localização e as suas informações.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @param i Valor auxiliar para controlar a exibição do cabeçalho da tabela.
 */
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
 * @brief Lista os meios alugados por um determinado cliente e as suas informações.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada.
 * @param v Apontador para a lista de vértices contendo as informações de localização.
 * @param idCliente Identificador do cliente.
 * @param i Valor auxiliar para controlar a exibição do cabeçalho da tabela.
 * @return O número total de meios alugados pelo cliente.
 */
int listarMeiosAlugados(Meio* inicio, VerticeList *v, int idCliente, int i){

    if (!inicio){
        printf(" -------------------------------------------------------------------------------------------------\n");
        return i;
    }
        
    if(inicio->idaluger == idCliente){
        if (i == 0){
            printf(" -------------------------------------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min) |             Local           |\n");
            printf("|-------------------------------------------------------------------------------------------------|\n");
        }
        printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-25s  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo,
        NOME_PONTOS[auxPrintMeios(v,inicio)]);
        i++;
    }
    
    listarMeiosAlugados(inicio->next,v , idCliente, i);
}


/**
 * @brief Obtém o vértice correspondente ao geocode do meio na lista de vértices.
 * 
 * 
 * @param v Apontador para a lista ligada de vértices.
 * @param inicio Apontador para o meio cujo geocode será pesquisado.
 * @return O número do vértice correspondente ao geocode do meio, ou -1 se não encontrado.
 */
int auxPrintMeios(VerticeList *v, Meio * inicio){
    if(v == NULL)
        return -1;


    while(v != NULL){
        if (strcmp(v->geocode, inicio->geocode) == 0){
            return v->vertice;
        }
        v = v->next;
    }

    return -1;
}

/**
 * @brief Lista os meios dentro de um determinado raio a partir de um vértice de origem.
 * 
 * 
 * @param inicio Aopntador para o início da lista ligada de meios.
 * @param v Aopntador para a lista ligada de vértices contendo as informações de localização.
 * @param origem O número do vértice de origem.
 * @param raio O raio máximo para inclusão dos meios na lista.
 * @param tipomeio O tipo de meio para filtrar os resultados.
 * @return 1 se houver meios dentro do raio e do tipo especificado, 0 caso contrário.
 */
int listarDeterminadosMeiosRaio(Meio* inicio, VerticeList *v, int origem, float raio, char tipomeio[]){
    int aux, *a, i, j = 0, vertice;
    float  aux1 = INFINITO;
    Meio *lista = inicio;

    if (!inicio)
        return 0;
        
    aux = numVertices(v);

    a = malloc(sizeof(float)*aux);

    for(i = 0; i < aux; i++){
        a[i] = -1;
    }

    for(i = 0; i < aux; i++){
        if(i != origem)
            a[i] = menorCaminho(v, origem, i);
        else
            a[i] = 0;
    }

    i = 0;
    while(lista != NULL){
        verticePorGeocode(v,&vertice, lista->geocode);
        if(a[vertice] <= raio && a[vertice] != -1 && (strcmp(tipomeio, lista->tipo) == 0))
            j++;
        if(a[vertice] < aux1)
            aux1 = a[vertice];
        lista = lista->next;
    }

    if( j > 0){
        while( inicio != NULL){
        if(i== 0){
            printf(" -------------------------------------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min) |             Local           |\n");
            printf("|-------------------------------------------------------------------------------------------------|\n");
        }
        verticePorGeocode(v,&vertice, inicio->geocode);
        if( a[vertice] <= raio && a[vertice] != -1 && (strcmp(tipomeio, inicio->tipo) == 0))
            printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-25s  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo,
            NOME_PONTOS[auxPrintMeios(v,inicio)]);
        inicio = inicio->next;
        i++;
        }
        printf(" -------------------------------------------------------------------------------------------------\n");
    }else{
        printf("De momento nao existe o meio escolhido no raio indicado");
    }
    

    free(a);
    return 1;
}


/**
 * @brief Lista os meios dentro de um determinado raio a partir de um vértice de origem.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param v Apontador para a lista de vértices contendo as informações de localização.
 * @param origem O número do vértice de origem.
 * @param raio O raio máximo para inclusão dos meios na lista.
 * @return 1 se houver meios dentro do raio, 0 caso contrário.
 */
int listarMeiosRaio(Meio* inicio, VerticeList *v, int origem, float raio){
    int aux, *a, i, j = 0, vertice;
    float  aux1 = INFINITO;
    Meio *lista = inicio;

    if (!inicio)
        return 0;
        
    aux = numVertices(v);

    a = malloc(sizeof(float)*aux);

    for(i = 0; i < aux; i++){
        a[i] = -1;
    }

    for(i = 0; i < aux; i++){
        if(i != origem)
            a[i] = menorCaminho(v, origem, i);
        else
            a[i] = 0;
    }

    i = 0;
    while(lista != NULL){
        verticePorGeocode(v,&vertice, lista->geocode);
        if(a[vertice] <= raio && a[vertice] != -1)
            j++;
        if(a[vertice] < aux1)
            aux1 = a[vertice];
        lista = lista->next;
    }

    if( j > 0){
        while( inicio != NULL){
        if(i== 0){
            printf(" -------------------------------------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min) |             Local           |\n");
            printf("|-------------------------------------------------------------------------------------------------|\n");
        }
        verticePorGeocode(v,&vertice, inicio->geocode);
        if( a[vertice] <= raio && a[vertice] != -1)
            printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-25s  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo,
            NOME_PONTOS[auxPrintMeios(v,inicio)]);
        inicio = inicio->next;
        i++;
        }
        printf(" -------------------------------------------------------------------------------------------------\n");
    }else{
        printf("De momento nao existem meios no raio indicado, o meio mais proximo esta a %.2f m\n", aux1);
    }
    

    free(a);
    return 1;
}

/**
 * @brief Lista os meios disponíveis num determinado local.
 * 
 * 
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param v Apontador para a lista ligada de vértices contendo as informações de localização.
 * @param local O número do vértice correspondente ao local.
 * @return 1 se houver meios no local, 0 caso contrário.
 */
int listarMeiosLocal(Meio* inicio, VerticeList *v, int local){
    int i = 0,j = 0, vertice;
    Meio *lista = inicio;

    if (!inicio)
        return 0;

    
    while(lista != NULL){
        verticePorGeocode(v,&vertice, lista->geocode);
        if(vertice == local)
            j++;
        lista = lista->next;
    }

    if( j > 0){
        while( inicio != NULL){
        if(i== 0){
            printf(" -------------------------------------------------------------------------------------------------\n");
            printf("|  codigo  |      Tipo      |  Bateria  |  Autonomia  |  Custo(min) |             Local           |\n");
            printf("|-------------------------------------------------------------------------------------------------|\n");
        }
        verticePorGeocode(v,&vertice, inicio->geocode);
        if( vertice == local)
            printf("|    %-4d  |   %-9s    |    %-5d  |  %-9.2f  |  %-9.2f  |  %-25s  |\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo,
            NOME_PONTOS[auxPrintMeios(v,inicio)]);
        inicio = inicio->next;
        i++;
        }
        printf(" -------------------------------------------------------------------------------------------------\n");
    }else{
        printf("De momento nao existem meios no local escolhido\n" );
    }
    
    return 1;
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


/**
 * @brief Retorna o custo de um meio específico.
 * 
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param id O código do meio.
 * @return float O custo do meio especificado. Retorna 0 se o meio não for encontrado.
 */
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


/**
 * @brief Funçao para carregar os Meios e os seus dados do ficheiro 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Meios
 */
void readMeios(Meio **inicio){
    FILE* fp;
    int cod, bat,idaluguer, metQuad;
    float aut, autMax, custo;
    char tipo[MAX_CODE], geocode[MAX_GEOCODE];
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, * campo6, * campo7, * campo8, * campo9;

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
			campo8 = strtok(NULL, ";");
			campo9 = strtok(NULL, ";");

			cod = atoi(campo1);
			bat = atoi(campo2);
			aut = atof(campo3);
			autMax = atof(campo4);
			custo = atof(campo5);
            idaluguer = atoi(campo6);
            strcpy(tipo, campo7);
            strcpy(geocode, campo8);
            metQuad = atoi(campo9);
            //geocode[strlen(geocode) - 1] = '\0';

            inserirMeio(&(*inicio), cod, tipo, bat, aut, autMax, custo, idaluguer, geocode, metQuad);
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
        fprintf(fp,"%d;%d;%.2f;%.2f;%.2f;%d;%s;%s;%d\n", inicio->codigo, inicio->bateria, inicio->autonomia, inicio->autonomiaMax, inicio->custo, inicio->idaluger, inicio->tipo, inicio->geocode, inicio->metrosQ);
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
                inserirMeio(&(*inicio), new->codigo, new->tipo, new->bateria, new->autonomia, new->autonomiaMax, new->custo, new->idaluger, new->geocode, new->metrosQ);
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

/**
 * @brief Retorna a carga de um meio específico.
 * 
 * @param inicio Apontador para o início da lista ligada de meios.
 * @param id O código do meio.
 * @return int A carga do meio especificado. Retorna INFINITO se o meio não for encontrado.
 */
int cargaPorId(Meio *inicio, int id){
    if(inicio == NULL)
        return INFINITO;

    while(inicio != NULL){
        if(inicio->codigo == id)
            break;
        inicio = inicio->next;
    }

    return inicio->metrosQ;
}