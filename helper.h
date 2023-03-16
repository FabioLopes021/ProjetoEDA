#ifndef PROJECT_HELPER_H      //Guarda de Ficheiro
#define PROJECT_HELPER_H      //Guarda de Ficheiro


//ficheiro para guardar algumas constantes globais
#define MAX_NAME 50
#define MAX_MORADA 150
#define MAX_PASSWORD 150
#define MAX_NIF 10
#define MAX_EMAIL 60
#define MIN_NAME 2
#define MAX_CODE 50         //Definir o limite para o nome do tipo de transporte

#include "gestores.h"
#include "clientes.h"


int funcaoLogin(Clientes **inicio, Gestores **g, char password[], char email[], Clientes **logc, Gestores **logg);
int menu();
int menuclientes(char nome[], float saldo);
int menucGestores();
int menuCriarConta();
int menuAlterarDadosCliente();
int menuAlterarDadosGestor();
int menuAlterarDadosMeio();
void generico();
void clearbuffer();
void EsperarQuePrimaEnter();

#endif //final da guarda de ficheiro