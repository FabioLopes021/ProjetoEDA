#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestores.h"


/**
 * @brief Funçao para adicionar um novo Gestor a lista ligada de Gestores
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 * @param nome Nome do Gestor a ser inserido
 * @param morada Morada do Gestor a ser inserido
 * @param NIF NIF do Gestor a ser inserido
 * @param password Password do Gestor a ser inserido
 * @param email Email do Gestor a ser inserido
 * @param id ID do Gestor a ser inserido
 */
void inserirGestor(Gestores** inicio, char nome[], char morada[], char NIF[], char password[], char email[], int id){
    Gestores *new;
    
    new = (Gestores *) malloc(sizeof(Gestores));

    strcpy(new->name, nome);
    strcpy(new->morada, morada);
    strcpy(new->NIF, NIF);
    strcpy(new->email, email);
    strcpy(new->password, password);
    new->id = id;

    new->next = (*inicio);
    (*inicio) = new;
}


/**
 * @brief Funçao para ler os dados de um Gestor e inseri-lo na lista ligada dos gestores 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 */
void lerDadosGestor(Gestores** inicio){
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    int id;

    clearbuffer();

    system("clear");
    printf("\n--------------- Criar Conta ---------------");
    printf("\nIndique o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome)-1] = '\0';

    clearbuffer();

    printf("\nIndique a sua morada: ");
    fgets(morada, MAX_MORADA, stdin);
    morada[strlen(morada) - 1] = '\0';

    clearbuffer();

    printf("\nIndique o seu NIF: ");
    fgets(NIF, MAX_NIF, stdin);
    NIF[MAX_NIF - 1] = '\0';

    clearbuffer();

    printf("\nIndique o seu email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strlen(email)-1] = '\0';

    clearbuffer();

    printf("\nIndique a sua password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strlen(password)-1] = '\0';
    clearbuffer();

    //chamar funçao para verificar qual o proximo id
    id = generateidGestor(*inicio);

    encriptPassword(password);
    
    inserirGestor(&(*inicio), nome, morada, NIF, password, email, id);
}



/**
 * @brief Funçao que lista os dados de todos os gestores registados
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna 0 se a lista estiver vazia ou quando a funçao chegar ao final da lista
 */
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


/**
 * @brief Funçao que lista os dados de um gestor
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna 1 se os dados do cliente foram listados com sucesso e 0 caso contrário.
 */
int printGestor(Gestores* inicio){
    if (!inicio)
        return 0;
    
    generico();

    printf("\n\n --------------------------------------------------------------------------------------------------------- \n");
    printf("|  ID  |       Nome       |           Morada           |     NIF     |            Email            |  ID  |\n");
    printf(" --------------------------------------------------------------------------------------------------------- \n");
    printf("|  %-3d |  %-14s  |       %-14s       |  %-9s  |  %-25s  |  %-2d  |\n",inicio->id, inicio->name, inicio->morada, inicio->NIF,
    inicio->email, inicio->id);
    printf(" --------------------------------------------------------------------------------------------------------- \n");

    EsperarQuePrimaEnter();
    return 1;

}


/**
 * @brief Funçao que verifica se um determinado gestor existe
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param id ID do gestor a verificar
 * @return int retorna 1 se o gestor existir, 0 caso contrario
 */
int existeGestor(Gestores* inicio, int id){
    if (!inicio)
        return 0;
    if (inicio->id == id)   
        return 1;
    return existeGestor(inicio->next, id);
}


/**
 * @brief Função que verifica se um determinado email corresponde a algum gestor
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @param email Email a ser verificado 
 * @return int retorna 1 se o email inserido corresponder ao email de algum gestor e 0 se nao corresponder
 */
int existeGestorEmail(Gestores* inicio, char email[]){
    if (!inicio)
        return 0;
    if (!strcmp(email, inicio->email))   
        return 1;
    return existeGestorEmail(inicio->next, email);
}


/**
 * @brief Funçao para remover um determinado gestor
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 * @param id ID do gestor a ser removido
 * @param i Contador da funçao
 * @return Gestores* retorna o endereço do gestor seguinte ao cliente removido da lista, NULL caso o mesmo n seja encontrado
 */
Gestores *removerGestor(Gestores **inicio, int id, int i){
    Gestores *aux;

    if (!*inicio){
        printf("A base de dados esta vazia");
        return NULL;
    }

    if(!(existeGestor((*inicio), id))){
        printf("Nao existe nenhum gestor resgistado com o ID indicado...\n");
        return NULL;
    }
    
    if (((*inicio)->id == id) && i == 1){
        aux = (*inicio)->next;
        free((*inicio));
        (*inicio) = aux;
        return aux;
    }else if ((*inicio)->id == id){
        aux = (*inicio)->next;
        free((*inicio));
        return aux;
    }else{
        (*inicio)->next = removerGestor(&(*inicio)->next, id, ++i);
        return (*inicio);
    }
}


/**
 * @brief Funçao para verificar a password e email de um gestor
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 * @param password Password a ser verificada
 * @param email Email a ser verificado
 * @return Gestores* Retorna o endereço do gestor correspondente as credenciais,NULL caso contrario 
 */
Gestores *loginGestores(Gestores **inicio,char password[], char email[]){

    if (!(*inicio)){
        return NULL;
    }

    if (!existeGestorEmail((*inicio), email)){
        return NULL;
    }

    if (strcmp(password, (*inicio)->password)){
        return loginGestores(&(*inicio)->next, password, email);
    }

    return (*inicio);
}


/**
 * @brief Funçao para alterar o nome de um Gestor
 * 
 * @param gestor Endereço do gestor a alterar o nome
 * @param novonome Novo nome do gestor
 */
void alterarNomeGestor(Gestores *gestor, char novonome[]){

    if (strlen(novonome) > MIN_NAME){
        strcpy(gestor->name, novonome);
    }
}


/**
 * @brief Funçao para alterar a morada de um Gestor
 * 
 * @param gestor Endereço do gestor a alterar a morada
 * @param novamorada Nova morada do cliente
 */
void alterarMoradaGestor(Gestores *gestor, char novamorada[]){

    if (strlen(novamorada) > MIN_NAME){
        strcpy(gestor->morada, novamorada);
    }
}


/**
 * @brief Funçao para alterar o NIF de um Gestor
 * 
 * @param gestor Endereço do gestor a alterar o NIF
 * @param novoNIF Novo NIF do gestor
 */
void alterarNIFGestor(Gestores *gestor, char novoNIF[]){

    if (strlen(novoNIF) > MIN_NAME){
        strcpy(gestor->NIF, novoNIF);
    }
}

/**
 * @brief Funçao para alterar o email de um Gestor
 * 
 * @param gestor Endereço do gestor a alterar o email
 * @param novoemail Novo email do gestor
 */
void alterarEmailGestor(Gestores *gestor, char novoemail[]){

    if (strlen(novoemail) > MIN_NAME){
        strcpy(gestor->email, novoemail);
    }
}


/**
 * @brief Funçao para alterar a password de um Gestor
 * 
 * @param gestor Endereço do gestor a alterar a password
 * @param novapassword Nova password do gestor
 */
void alterarPasswordGestor(Gestores *gestor, char novapassword[]){

    if (strlen(novapassword) > MIN_NAME){
        strcpy(gestor->password, novapassword);
    }
}

/**
 * @brief Funçao para gerar im ID unico para um novo Gestor
 * 
 * @param inicio Apontador para o inicio da lista ligada
 * @return int retorna um ID unico para o novo gestor
 */
int generateidGestor(Gestores *inicio){
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
 * @brief Funçao para carregar os gestores e os seus dados do ficheiro 
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 */
void readGestores(Gestores **inicio){
    FILE* fp;
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL], password[MAX_PASSWORD];
    int id;
    char line[1024];
	char* campo1, * campo2, * campo3, * campo4, * campo5, *campo6;

    fp = fopen("gestores.txt","r");

    if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {

			campo1 = strtok(line, ";");
			campo2 = strtok(NULL, ";");
			campo3 = strtok(NULL, ";");
			campo4 = strtok(NULL, ";");
			campo5 = strtok(NULL, ";");
			campo6 = strtok(NULL, ";");

            strcpy(nome, campo1);
            strcpy(morada, campo2);
            strcpy(NIF, campo3);
            strcpy(email, campo4);
            strcpy(password, campo5);
            id = atoi(campo6);

            inserirGestor(&(*inicio), nome, morada, NIF, password, email, id);
		}
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro");
	}
}

/**
 * @brief Funçao para guardar os Gestores e os seus dados em ficheiro
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 */
void guardarGestores(Gestores* inicio){
    FILE* fp;

    fp = fopen("gestores.txt","w");

    if (fp!=NULL){
        
        while (inicio != NULL){
        fputs(inicio->name, fp);
        fprintf(fp,";");
        fputs(inicio->morada, fp);
        fprintf(fp,";");
        fputs(inicio->NIF, fp);
        fprintf(fp,";");
        fputs(inicio->email, fp);
        fprintf(fp,";");
        fputs(inicio->password, fp);
        fprintf(fp,";");
        fprintf(fp,"%d\n", inicio->id);
        inicio = inicio->next;
        }

        fclose(fp);

        printf("Gestores guardados com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro Clientes\n");
}


/**
 * @brief Funçao para carregar os Gestores e os seus dados do ficheiro binario
 * 
 * @param inicio Apontador para a variavel que guarda o apontador para a cabeça da lista ligada dos Gestores
 */
void lerGestoresBin(Gestores **inicio){
    FILE *fp;
    Gestores *new;

    new = (Gestores *) malloc(sizeof(Gestores));

    fp = fopen("gestoress.bin", "rb");

    if(fp != NULL){

       while (fread(new, sizeof(Gestores), 1, fp) == 1) {
            if(new != NULL){
                inserirGestor(&(*inicio), new->name, new->morada, new->NIF, new->password, new->email, new->id);
            }
             
        }
        free(new);
        fclose(fp);

        printf("Dados binarios lidos com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}

/**
 * @brief Funçao para guardar os gestores e os seus dados do ficheiro binario
 * 
 * @param inicio Apontador a cabeça da lista ligada dos Clientes
 */
void guardarGestoresBin(Gestores *inicio){
    FILE *fp;

    fp = fopen("gestoress.bin", "wb");

    if(fp != NULL){

        while (inicio != NULL) {
            fwrite(inicio, sizeof(Gestores), 1, fp);
            inicio = inicio->next;
        }

        fclose(fp);

        printf("Gestores guardados em binario com sucesso\n");
    }else{
        printf("Erro ao abrir ficheiro binario\n");
    }
}