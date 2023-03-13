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
    int menu1, menuc, menug, menuconta, id, num = 0, menualtc, menualtm, menualtg, bateria, idmeio, count;
    
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL], tipo[MAX_CODE];
    char emaillog[MAX_EMAIL], passwordlog[MAX_PASSWORD];
    float saldo, autonomia, custo;

    readMeios(&h);
    readClientes(&c);
    readGestores(&g);

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
                                    case 1:     //Alugar meio
                                        listarMeiosLivres(h);
                                        printf("Indique o id do meio que deseja alugar: ");
                                        scanf("%d", &id);
                                        alugarMeio( h, c, id);
                                        id = 0;
                                        break;
                                    case 2:     //Terminar aluguer 
                                        num = listarMeiosAlugados(h, c, 0);
                                        if (num == 0){
                                            printf("\nEste utilizador nao tem meios alugados\n");
                                        }else{
                                            printf("\nIndique o id do meio que deseja terminar o aluger: ");
                                            scanf("%d", &id);
                                            terminarAluguer(h ,c ,id);
                                        }
                                        num = 0;
                                        id = 0;                                        
                                        break;
                                    case 3:
                                        do{
                                            menualtc = menuAlterarDadosCliente();
                                            switch(menualtc){
                                                case 1:     // Alterar nome
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu nome: ");
                                                    fgets(nome, MAX_NAME, stdin);
                                                    sscanf(nome,"%*s",nome);
                                                    nome[strlen(nome)-1] = '\0';
                                                    alterarNomeCliente(loginc, nome);
                                                    break;
                                                case 2:     // Alterar morada
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique a sua morada: ");
                                                    fgets(morada, MAX_MORADA, stdin);
                                                    morada[strlen(morada) - 1] = '\0';
                                                    alterarMoradaCliente(loginc, morada);
                                                    break;
                                                case 3:     // Alterar NIF
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu NIF: ");
                                                    fgets(NIF, MAX_NIF, stdin);
                                                    NIF[MAX_NIF] = '\0';
                                                    alterarNIFCliente(loginc, NIF);
                                                    break;
                                                case 4:     // Alterar email
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu email: ");
                                                    fgets(email, MAX_EMAIL, stdin);
                                                    email[strlen(email)-1] = '\0';
                                                    alterarEmailCliente(loginc, email);
                                                    break;
                                                case 5:     // Alterar  password
                                                    while ((getchar()) != '\n');    
                                                    printf("\nIndique a sua password: ");
                                                    fgets(password, MAX_PASSWORD, stdin);
                                                    password[strlen(password)-1] = '\0';
                                                    alterarPasswordCliente(loginc, password);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                        }while(menualtc != 0);
                                        
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
                                    case 1:     //Adicionar meios
                                        lerDadosMeio(&h);
                                        break;
                                    case 2:     //Consultar historico
                                    
                                        break;
                                    case 3:     //Estatisticas

                                        break;
                                    case 4:     //Validaçoes

                                        break;
                                    case 5:     //Alterar meios
                                        do{
                                            count = 0;
                                            system("clear");
                                            listarMeios(h);
                                            
                                            do{
                                                if(count == 0)  
                                                    printf("\nIndique o meio que deseja alterar:");
                                                else   
                                                    printf("\nIndique um meio valido:"); 
                                                scanf("%d", &idmeio);
                                                count++;
                                            }while(!existeMeio(h,idmeio));
                                            menualtm = menuAlterarDadosMeio();
                                            switch(menualtm){
                                                case 1:     // Alterar tipo
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o tipo: ");
                                                    fgets(tipo, MAX_CODE, stdin);
                                                    sscanf(tipo,"%*s",tipo);
                                                    tipo[strlen(tipo)-1] = '\0';
                                                    alterarTipoMeio(h, tipo, idmeio);
                                                    break;
                                                case 2:     // Alterar bateria
                                                    printf("\nIndique a bateria do meio:");
                                                    scanf("%d", &bateria);
                                                    alterarBateria(h, bateria, idmeio);
                                                    break;
                                                case 3:     // Alterar autonomia
                                                    printf("\nIndique a autonomia do meio");
                                                    scanf("%f", &autonomia);
                                                    alterarAutonomia(h, autonomia, idmeio);
                                                    break;
                                                case 4:     // Alterar custo
                                                    printf("\nIndique a autonomia do meio");
                                                    scanf("%f", &custo);
                                                    alterarCusto(h, custo, idmeio);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                            break;
                                        }while(menualtc != 0);
                                        break;
                                    case 6:     //Alterar dados
                                        do{
                                            menualtg = menuAlterarDadosGestor();
                                            switch(menualtg){
                                                case 1:     // Alterar nome
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu nome: ");
                                                    fgets(nome, MAX_NAME, stdin);
                                                    sscanf(nome,"%*s",nome);
                                                    nome[strlen(nome)-1] = '\0';
                                                    alterarNomeGestor(loging, nome);
                                                    break;
                                                case 2:     // Alterar morada
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique a sua morada: ");
                                                    fgets(morada, MAX_MORADA, stdin);
                                                    morada[strlen(morada) - 1] = '\0';
                                                    alterarMoradaGestor(loging, morada);
                                                    break;
                                                case 3:     // Alterar NIF
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu NIF: ");
                                                    fgets(NIF, MAX_NIF, stdin);
                                                    NIF[MAX_NIF] = '\0';
                                                    alterarNIFGestor(loging, NIF);
                                                    break;
                                                case 4:     // Alterar email
                                                    while ((getchar()) != '\n');
                                                    printf("\nIndique o seu email: ");
                                                    fgets(email, MAX_EMAIL, stdin);
                                                    email[strlen(email)-1] = '\0';
                                                    alterarEmailGestor(loging, email);
                                                    break;
                                                case 5:     // Alterar  password
                                                    while ((getchar()) != '\n');    
                                                    printf("\nIndique a sua password: ");
                                                    fgets(password, MAX_PASSWORD, stdin);
                                                    password[strlen(password)-1] = '\0';
                                                    alterarPasswordGestor(loging, password);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                        }while(menualtg != 0);
                                        break;
                                    case 0:
                                        printf("\nA sair da conta...\n");
                                        break;
                                }
                            }while(menug != 0);
                        }else{
                            printf("Password ou email incorretos...\n");
                        }
                        loging = NULL;
                        logmenu = 0;
                        break;
                    case 0:
                        break;
                }
                break;
            case 2:
                //Criar Conta
                do{
                    menuconta = menuCriarConta();
                    switch(menuconta){
                    case 1:
                        printf("\nCriar conta cliente\n");
                        lerDados(&c);
                        break;
                    case 2:
                        printf("\nCriar conta gestor\n");
                        lerDadosGestor(&g);
                        break;
                    case 0:
                        printf("\nVoltar ao menu principal\n");
                        break;
                }
                }while(menuconta != 0);
                break;
            case 0:
                break;
        }
    }while(menu1 != 0);
    /*
    char ver;
    printf("Deseja guardar as alteraçoes ? (s,n)");
    scanf("%c", &ver);
    if (ver == 's'){
        guardarMeios(h);
    }
    */
    //guardarGestores(g);
    //guardarClientes(c);
    //guardarMeios(h);
    return 1;
}
