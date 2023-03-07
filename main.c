#include <stdlib.h>
#include <stdio.h>
#include "meio.h"
#include "meio.c"
#include "clientes.h"
#include "clientes.c"
#include "gestores.h"
#include "gestores.c"


int main(){
    Meio *h = NULL;
    Clientes *c = NULL, *loginc = NULL;
    Gestores *g = NULL, *loging = NULL;


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
    inserirGestor(&g, nome, morada, NIF, password, email);

    printf("\n---------LOGIN--------\n");
    printf("indique o seu email: ");
    fgets(emaillog,MAX_EMAIL,stdin);
    emaillog[strlen(emaillog) - 1] = '\0';

    printf("Indique a sua password: ");
    fgets(passwordlog,MAX_PASSWORD,stdin);
    passwordlog[strlen(passwordlog) - 1] = '\0';


    loging = loginGestores(&g, passwordlog, emaillog);
    if ( loging == NULL){
        printf("\nOcorreu um erro no login, password ou email errados...\n");
    }else{
        puts(loging->name);
    }



    return 1;
}