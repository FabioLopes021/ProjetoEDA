#include <stdlib.h>
#include <stdio.h>
#include "meio.h"
#include "meio.c"
#include "clientes.h"
#include "clientes.c"
#include "gestores.h"
#include "gestores.c"


// Funçao de apoio as funçoes de Login, serve para reduzir o menu para apenas uma opçao de login
int funcaoLogin(Clientes **inicio, Gestores **g, char password[], char email[], Clientes **logc, Gestores **logg);


int main(){
    Meio *h = NULL;
    Clientes *c = NULL, *loginc = NULL;
    Gestores *g = NULL, *loging = NULL;
    int logmenu = 0;
    
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    char emaillog[MAX_EMAIL], passwordlog[MAX_PASSWORD];
    float saldo;

    strcpy(nome,"Fabio Lopes");
    strcpy(morada,"Rua da Penide n236 Areias S Vicente, Barcelos");
    strcpy(NIF, "12345678");
    strcpy(password, "fabio");
    strcpy(email, "fabiolopes021@gmail.com");
    saldo = 530.67;
    
    //inserirCliente(&c,nome,morada,NIF,saldo,password,email);
    inserirGestor(&g, nome, morada, NIF, password, email);


    strcpy(nome,"Andre Lopes");
    strcpy(morada,"Rua da Penide n236 Areias S Vicente, Barcelos");
    strcpy(NIF, "87654321");
    strcpy(password, "andre");
    strcpy(email, "andrelopes021@gmail.com");
    saldo = 9530.67;
    
    //inserirCliente(&c,nome,morada,NIF,saldo,password,email);
    //inserirGestor(&g, nome, morada, NIF, password, email);
    inserirCliente(&c, nome, morada, NIF, saldo, password, email);

    printf("\n---------LOGIN--------\n");
    printf("indique o seu email: ");
    fgets(emaillog,MAX_EMAIL,stdin);
    emaillog[strlen(emaillog) - 1] = '\0';

    printf("Indique a sua password: ");
    fgets(passwordlog,MAX_PASSWORD,stdin);
    passwordlog[strlen(passwordlog) - 1] = '\0';

    // teste login unico
    logmenu = funcaoLogin(&c, &g, passwordlog, emaillog, &loginc, &loging);
    
    switch(logmenu){
        case 1:
            if (loginc != NULL){
                printf("Login efetuado com sucesso. (cliente: %s)\n", loginc->name);
            }else{
                printf("Password ou email incorretos...\n");
            }
            break;
        case 2:
            if (loging != NULL){
                printf("Login efetuado com sucesso. (cliente: %s)\n", loginc->name);
            }else{
                printf("Password ou email incorretos...\n");
            }
            break;
        case 0:
            break;
    }


    return 1;
}




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

