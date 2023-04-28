#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Funçao para realizar login de um gestor ou cliente
 * 
 * @param inicio Apontador para a lista ligada de Clientes
 * @param g Apontador para a lista ligada de Gestores
 * @param password A palavra passe inserida pelo utilizador
 * @param email O email inserido pelo utilizador
 * @param logc Apontador para introduzir o endereço do cliente ao qual corresponde o login
 * @param logg Apontador para introduzir o endereço do gestor ao qual corresponde o login
 * @return int Retorna 1 se é um Cliente, 2 se é um Gestor e 0 se nao reconhecer os dados
 */
int funcaoLogin(Clientes **inicio, Gestores **g, char password[], char email[], Clientes **logc, Gestores **logg){
    int i = 0;
    

    if (existeClienteEmail((*inicio), email)){
        i = 1;
        *logc = loginClientes(&(*inicio), password, email);
    }else if(existeGestorEmail((*g), email)){
        i = 2;
        *logg = loginGestores(&(*g), password, email);
    } else {
        printf("Email ou password errados...\n");
        return 0;
    }

    return i;
}


/**
 * @brief Função para apresentar menu principal e receber a resposta do utilizador
 * 
 * @return int retorna a opção escolhida pelo utilizador
 */
int menu(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - login                    |\n");
        printf("| 2 - Criar conta              |\n");
        printf("| 0 - Sair                     |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 2);

    return opc;
}

/**
 * @brief Função para apresentar o menu de Clientes e receber as suas respostas
 * 
 * @param nome nome do cliente logado
 * @param saldo saldo do cliente logado
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menuclientes(char nome[], float saldo){
    int opc;

    generico();
    printf("\nCliente: %s\nSaldo: %.2f", nome, saldo);
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Alugar meio              |\n");
        printf("| 2 - Terminar aluguer         |\n");
        printf("| 3 - Alterar dados            |\n");
        printf("| 4 - Adicionar Saldo          |\n");
        printf("| 5 - Consultar dados conta    |\n");
        printf("| 6 - Remover Conta            |\n");
        printf("| 7 - Consultar Historico      |\n");
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 7);

    return opc;
}


/**
 * @brief Função para apresentar o menu de Gestores e receber as suas respostas
 * 
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menucGestores(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Adicionar meios          |\n");
        printf("| 2 - Consultar historico      |\n");
        printf("| 3 - Estatisticas             |\n");
        printf("| 4 - Validaçoes               |\n");
        printf("| 5 - Alterar meios            |\n");
        printf("| 6 - Alterar dados            |\n");
        printf("| 7 - Remover Meio             |\n");
        printf("| 8 - Remover Conta            |\n");
        printf("| 9 - Consultar dados conta    |\n");
        printf("| 10 - Imprimir lista clientes |\n");
        printf("| 11 - Imprimir lista Meios    |\n");
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 11);

    return opc;
}



/**
 * @brief Função para apresentar o menu criação de contas e receber as respostas dos utilizadores
 * 
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menuCriarConta(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Conta Cliente            |\n");
        printf("| 2 - Conta Gestor             |\n");
        printf("| 0 - Voltar                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 2);

    return opc;
}


/**
 * @brief Função que apresenta o menu de opções para alterar os dados de um Cliente
 * 
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menuAlterarDadosCliente(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Alterar nome             |\n");
        printf("| 2 - Alterar morada           |\n");
        printf("| 3 - Alterar NIF              |\n");
        printf("| 4 - Alterar email            |\n");
        printf("| 5 - Alterar password         |\n");
        printf("| 0 - Voltar                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 5);

    return opc;
}



/**
 * @brief Função que apresenta o menu de opções para alterar os dados de um Gestor
 * 
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menuAlterarDadosGestor(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Alterar nome             |\n");
        printf("| 2 - Alterar morada           |\n");
        printf("| 3 - Alterar NIF              |\n");
        printf("| 4 - Alterar email            |\n");
        printf("| 5 - Alterar password         |\n");
        printf("| 0 - Voltar                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 5);

    return opc;

}


/**
 * @brief Função que apresenta o menu de opções para alterar os dados de um Meio
 * 
 * @return int retorna a opçao escolhida pelo utilizador
 */
int menuAlterarDadosMeio(){
    int opc;

    generico();
    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Alterar Tipo             |\n");
        printf("| 2 - Alterar bateria          |\n");
        printf("| 3 - Alterar autonomia        |\n");
        printf("| 4 - Alterar custo            |\n");
        printf("| 0 - Voltar                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 4);

    return opc;

}



/**
 * @brief Função que limpa a consola e apresenta um banner
 * 
 */
void generico(){
    system("clear");
    printf("    ________________  __________________  __\n");
    printf("   / ____/ ____/ __ \\/ ____/  _/_  __/\\ \\/ /\n");
    printf("  / __/ / /   / / / / /    / /  / /    \\  / \n");
    printf(" / /___/ /___/ /_/ / /____/ /  / /     / /  \n");
    printf("/_____/\\____/\\____/\\____/___/ /_/     /_/   \n");
    printf("copyright by Fabio Lopes 2023\n");
}


void clearbuffer(){
    int c;

    while ( (c = getchar()) != '\n' && c != EOF ) { }
}


/**
 * @brief Função que espera que o utilizar prima o enter para continuar
 * 
 */
void EsperarQuePrimaEnter(){
    int c;

    do
    {
        c = fgetc( stdin);
    } while( c != EOF && c != '\n');

    clearerr( stdin);

    printf( "Prima [ENTER] para continuar...");
    fflush( stdout);
    getchar();
}

/**
 * @brief Funçao para encriptar a password dos utilizadores
 * 
 * @param password Apontador para a password a encriptar
 */
void encriptPassword(char *password){
    int i, key = 1914, len;
    len = strlen(password);

    for (i = 0; i < len; i++){
        if(password[i] >= 'a' && password[i] <= 'z'){
            password[i] = (password[i] - 'a' + key) % 26 + 'a';
        }else if(password[i] >= 'A' && password[i] <= 'Z'){
            password[i] = (password[i] - 'A' + key) % 26 + 'A';
        }
    }
}