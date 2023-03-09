#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int menu(){
    int opc;

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


int menuCriarConta(){
    int opc;

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