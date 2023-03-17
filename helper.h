#ifndef PROJECT_HELPER_H      //Guarda de Ficheiro
#define PROJECT_HELPER_H      //Guarda de Ficheiro


//Definiçao de algumas constantes
#define MAX_NAME 50         //Define o limite Maximo para o nome do Cliente/Gestor
#define MAX_MORADA 150      //Define o limite Maximo para as moradas
#define MAX_PASSWORD 150    //Define o limite Maximo para as passwords
#define MAX_NIF 10          //Define o limite Maximo para os NIFs
#define MAX_EMAIL 60        //Define o limite Maximo para os emails
#define MIN_NAME 2          //Define o limite Minimo para a alteraçao dos dados de qualquer conta ou meio
#define MAX_CODE 50         //Define o limite Maximo para o nome do tipo de transporte

#include "gestores.h"
#include "clientes.h"

// Verifica os dados de login e verifica qual a funçao necessaria chamar para a verificação dos dados
int funcaoLogin(Clientes **inicio, Gestores **g, char password[], char email[], Clientes **logc, Gestores **logg);

// Imprime o menu Principal na consola
int menu();

// Imprime o menu de Clientes na consola
int menuclientes(char nome[], float saldo);

// Imprime o menu de Gestores na consola
int menucGestores();

// Imprime o menu de Registo na consola
int menuCriarConta();

// Imprime o menu de alteraçao de dados de Clientes na consola
int menuAlterarDadosCliente();

// Imprime o menu de alteraçao de dados de Gestores na consola
int menuAlterarDadosGestor();

// Imprime o menu de alteraçao de dados de Meios na consola
int menuAlterarDadosMeio();

// Imprime um banner na consola
void generico();

// limpa o buffer de entrada
void clearbuffer();

// Espera que o utilizador prima ENTER para continuar
void EsperarQuePrimaEnter();

// Encripta uma Password
void encriptPassword(char *password);


#endif //final da guarda de ficheiro