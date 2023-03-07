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
    Clientes *c = NULL;
    Gestores *g = NULL;

    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    float saldo;

    strcpy(nome, "Fabio Lopes");
    strcpy(morada, "Rua da penide n236, Areias S vicente");
    strcpy(NIF, "12345678");
    strcpy(email, "fabiolopes021@gmail.com");
    strcpy(password, "fabiolopes");

    inserirGestor(&g, nome, morada, NIF, password, email);

    strcpy(nome, "Andre Lopes");
    strcpy(morada, "Rua da penide n236, Areias S vicente");
    strcpy(NIF, "98765431");
    strcpy(email, "andrelopes021@gmail.com");
    strcpy(password, "andrelopes");

    inserirGestor(&g, nome, morada, NIF, password, email);

    printf("-----------Listagem---------------\n");
    listarGestor(g);

    removerGestor(&g,"98765431",1);

    printf("\n\n\n\n");

    printf("-----------Listagem---------------\n");
    listarGestor(g);


    /*
    for (int i = 0; i < 3; i++){
        printf("codigo, bateria, autonomia, tipo\n");
        scanf("%d", &code);
        scanf("%d", &bateria);
        scanf("%f", &autonomia);
        scanf("%s", tip);
        inserirMeio(&h, code, tip, bateria, autonomia);
    }
    printf("existe: %d",existeMeio(h,10));
    printf("-----------Listagem---------------\n");
    listarMeios(h);
    

    strcpy(nome, "Fabio Lopes");
    strcpy(morada, "Rua da penide n236, Areias S vicente");
    strcpy(NIF, "12345678");
    strcpy(email, "fabiolopes021@gmail.com");
    strcpy(password, "fabiolopes");
    saldo = 500.59;

    inserirCliente(&c, nome, morada, NIF, saldo, password, email);

    strcpy(nome, "Andre Lopes");
    strcpy(morada, "Rua da penide n236, Areias S vicente");
    strcpy(NIF, "98765431");
    strcpy(email, "andrelopes021@gmail.com");
    strcpy(password, "andrelopes");
    saldo = 5500.59;

    inserirCliente(&c, nome, morada, NIF, saldo, password, email);

    printf("-----------Listagem---------------\n");
    listarCliente(c);

    removerCliente(&c,"12345678",1);

    printf("\n\n\n\n");

    printf("-----------Listagem---------------\n");
    listarCliente(c);
    */

    return 1;
}