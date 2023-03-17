#ifndef PROJECT_GESTORES_H      //Guarda de Ficheiro
#define PROJECT_GESTORES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xgestores{       //Declaraçao da estrutura de Clientes 
    int id;                     // ID unico de cada Cliente
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL],password[MAX_PASSWORD];     //Dados pessoais de Gestores
    struct xgestores *next;     //Next node
} Gestores;


// Inserção de um novo registo
void inserirGestor(Gestores** inicio, char nome[], char morada[], char NIF[], char password[], char email[], int id); 

// Funçao para ler os dados do Gestor e de seguida envia-los a funçao "inserirgestor"
void lerDadosGestor(Gestores** inicio);

// listar na consola o conteúdo da lista ligada
int listarGestor(Gestores* inicio); 

// Listar na Consola os dados de um cliente
int printGestor(Gestores* inicio);

// Determinar existência do 'ID' na lista ligada 'inicio'
int existeGestor(Gestores* inicio, int id);

// Determinar existência do email na lista ligada 'inicio'
int existeGestorEmail(Gestores* inicio, char email[]);

// Remover um meio a partir do seu ID
Gestores *removerGestor(Gestores **inicio, int id, int i);

// Verificar informaçoes de Login
Gestores *loginGestores(Gestores **inicio,char password[], char email[]);

// Alterar o nome de um gestor
void alterarNomeGestor(Gestores *gestor, char novonome[]);

// Alterar a morada de um gestor
void alterarMoradaGestor(Gestores *gestor, char novamorada[]);

// Alterar o NIF de um gestor
void alterarNIFGestor(Gestores *gestor, char novoNIF[]);

// Alterar o email de um gestor
void alterarEmailGestor(Gestores *gestor, char novoemail[]);

// Alterar a password de um gestor
void alterarPasswordGestor(Gestores *gestor, char novapassword[]);

// Gera um codigo unico para um novo Cliente
int generateidGestor(Gestores *inicio);

// Carrega para memoria os dados dos Gestores guardados num ficheiro
void readGestores(Gestores **inicio);

// Guarda num ficheiro os dados dos Clientes em memoria
void guardarGestores(Gestores* inicio);

// Carrega para memoria os dados dos Gestores guardados num ficheiro binario
void lerGestoresBin(Gestores **inicio);

// Guarda num ficheiro binario os dados dos Clientes em memoria
void guardarGestoresBin(Gestores *inicio);

#endif //final da guarda de ficheiro