#ifndef PROJECT_GESTORES_H      //Guarda de Ficheiro
#define PROJECT_GESTORES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xgestores{
    int id;
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL],password[MAX_PASSWORD];
    struct xgestores *next;
} Gestores;


// Inserção de um novo registo
void inserirGestor(Gestores** inicio, char nome[], char morada[], char NIF[], char password[], char email[], int id); 

void lerDadosGestor(Gestores** inicio);

// listar na consola o conteúdo da lista ligada
int listarGestor(Gestores* inicio); 

int printGestor(Gestores* inicio);

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeGestor(Gestores* inicio, char NIF[]);

// Determinar existência do email na lista ligada 'inicio'
int existeGestorEmail(Gestores* inicio, char email[]);

// Remover um meio a partir do seu código
Gestores *removerGestor(Gestores **inicio, char NIF[], int i);

// Funçoes para verificar informaçoes de Login
Gestores *loginGestores(Gestores **inicio,char password[], char email[]);

void alterarNomeGestor(Gestores *gestor, char novonome[]);

void alterarMoradaGestor(Gestores *gestor, char novamorada[]);

void alterarNIFGestor(Gestores *gestor, char novoNIF[]);

void alterarEmailGestor(Gestores *gestor, char novoemail[]);

void alterarPasswordGestor(Gestores *gestor, char novapassword[]);

int generateidGestor(Gestores *inicio);


void readGestores(Gestores **inicio);


void guardarGestores(Gestores* inicio);



#endif //final da guarda de ficheiro