#ifndef PROJECT_GESTORES_H      //Guarda de Ficheiro
#define PROJECT_GESTORES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xgestores{
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    struct xgestores *next;
} Gestores;


// Inserção de um novo registo
void inserirGestor(Gestores** inicio, char nome[], char morada[], char NIF[], char password[], char email[]); 

// listar na consola o conteúdo da lista ligada
int listarGestor(Gestores* inicio); 

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeGestor(Gestores* inicio, char NIF[]);

// Remover um meio a partir do seu código
Gestores *removerGestor(Gestores **inicio, int NIF, int i);


#endif //final da guarda de ficheiro