#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "helper.c"
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
    int logmenu = 0;
    int menu1, menuc, menug, menuconta;
    
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    char emaillog[MAX_EMAIL], passwordlog[MAX_PASSWORD];
    float saldo;

    strcpy(nome,"Fabio Lopes");
    strcpy(morada,"Rua da Penide n236 Areias S Vicente, Barcelos");
    strcpy(NIF, "12345678");
    strcpy(password, "fabio");
    strcpy(email, "fabiolopes021@gmail.com");
    saldo = 530.67;

    inserirGestor(&g, nome, morada, NIF, password, email);


    strcpy(nome,"Andre Lopes");
    strcpy(morada,"Rua da Penide n236 Areias S Vicente, Barcelos");
    strcpy(NIF, "87654321");
    strcpy(password, "andre");
    strcpy(email, "andrelopes021@gmail.com");
    saldo = 9530.67;

    inserirCliente(&c, nome, morada, NIF, saldo, password, email);

    do{
        menu1 = menu();
        switch(menu1){
            case 1:
                printf("indique o seu email: ");
                scanf("%s", emaillog);

                printf("Indique a sua password: ");
                scanf("%s", passwordlog);

                logmenu = funcaoLogin(&c, &g, passwordlog, emaillog, &loginc, &loging);

                switch(logmenu){
                    case 1:
                        if (loginc != NULL){
                            printf("Login efetuado com sucesso. (cliente: %s)\n", loginc->name);
                            do{
                                menuc = menuclientes();
                                
                                switch(menuc){
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    case 0:
                                        printf("\nA sair da conta...\n");
                                        break;
                                }
                            }while(menuc != 0);
                        }else{
                            printf("Password ou email incorretos...\n");
                        }
                        loginc = NULL;
                        logmenu = 0;
                        break;
                    case 2:
                        if (loging != NULL){
                            printf("Login efetuado com sucesso. (Gestor: %s)\n", loging->name);
                            do{
                                menug = menucGestores();
                                
                                switch(menug){
                                    case 1:
                                        break;
                                    case 2:
                                        break;
                                    case 3:
                                        break;
                                    case 4:
                                        break;
                                    case 5:
                                        break;
                                    case 0:
                                        printf("\nA sair da conta...\n");
                                        break;
                                }
                            }while(menuc != 0);
                        }else{
                            printf("Password ou email incorretos...\n");
                        }
                        loging = NULL;
                        logmenu = 0;
                        break;
                    case 0:
                        break;
                }
            case 2:
                //Criar Conta
                do{
                    menuconta = menuCriarConta();
                    switch(menuconta){
                    case 1:
                        printf("\nCriar conta cliente\n");
                        break;
                    case 2:
                        printf("\nCriar conta gestor\n");
                        break;
                    case 0:
                        printf("\nVoltar ao menu principal\n");
                        break;
                }
                }while(menuconta != 0);
                break;
            case 0:
                printf("Deseja guardar as alteraçoes ?");
                break;
        }
    }while(menu1 != 0);

    return 1;
}
