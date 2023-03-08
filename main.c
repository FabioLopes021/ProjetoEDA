#include <stdlib.h>
#include <stdio.h>
#include "meio.h"
#include "meio.c"
#include "clientes.h"
#include "clientes.c"
#include "gestores.h"
#include "gestores.c"

int menu();
int menuclientes();
int menucGestores();


int main(){
    Meio *h = NULL;
    Clientes *c = NULL, *loginc = NULL;
    Gestores *g = NULL, *loging = NULL;
    int menu1, menuc, menug;


    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    char emaillog[MAX_EMAIL], passwordlog[MAX_PASSWORD];
    float saldo;

    do{
        menu1 = menu();
        switch(menu1){
            case 1:
                do{
                    menuc = menuclientes();
                    switch(menuc){
                        case 1:
                            break;
                        case 2:
                            break;
                        case 0:
                            printf("Loging out...");
                    }
                }while(meuc != 0)
                
                break;
            case 2:
                menug

                break;
            case 3:
            
                break;
            case 0:
                printf("Deseja guardar as alteraçoes ?");
                break;
        }
    }while(menu1 != 0);


    return 1;
}





int menu(){
    int opc;

    do{
        printf("\n ------------------------------\n");
        printf("| 1 - login clientes           |\n");
        printf("| 2 - login gestores           |\n");
        printf("| 3 - Criar conta              |\n");
        printf("| 0 - Sair                     |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 3);
    
    return opc;
}

int menuclientes(){
    int opc;

    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Alugar meio              |\n");
        printf("| 2 - Alterar dados            |\n");
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 2);

    return opc;
}

int menucGestores(){
    int opc;

    do{
        printf("\n ------------------------------\n");
        printf("| 1 - Adicionar meios          |\n");
        printf("| 2 - Consultar historico      |\n");
        printf("| 3 - Estatisticas             |\n");
        printf("| 4 - Validaçoes               |\n");
        printf("| 5 - Alterar meios            |\n");
        printf("| 5 - Alterar dados            |\n");
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 5);

    return opc;

}