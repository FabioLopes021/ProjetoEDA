#ifndef PROJECT_CLIENTES_H      //Guarda de Ficheiro
#define PROJECT_CLIENTES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xclientes{
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    float saldo;
    struct xclientes *next;
} Clientes;


// Inserção de um novo registo
void inserirCliente(Clientes** inicio, char nome[], char morada[], char NIF[], float saldo, char password[], char email[]); 

// listar na consola o conteúdo da lista ligada
int listarCliente(Clientes* inicio); 

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeCliente(Clientes* inicio, char NIF[]);

// Remover um meio a partir do seu código
Clientes *removerCliente(Clientes **inicio, int NIF, int i);



#endif //final da guarda de ficheiro