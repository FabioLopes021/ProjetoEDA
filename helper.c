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
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 4);

    return opc;
}

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
        printf("| 0 - Logout                   |\n");
        printf(" ------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opc);
    }while(opc < 0 || opc > 6);

    return opc;
}


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
    }while(opc < 0 || opc > 3);

    return opc;

}


void generico(){
    system("clear");
    printf("    ________________  __________________  __\n");
    printf("   / ____/ ____/ __ \\/ ____/  _/_  __/\\ \\/ /\n");
    printf("  / __/ / /   / / / / /    / /  / /    \\  / \n");
    printf(" / /___/ /___/ /_/ / /____/ /  / /     / /  \n");
    printf("/_____/\\____/\\____/\\____/___/ /_/     /_/   \n");
    printf("Copiryght by Fabio Lopes 2023\n");
}