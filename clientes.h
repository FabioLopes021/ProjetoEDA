#ifndef PROJECT_CLIENTES_H      //Guarda de Ficheiro
#define PROJECT_CLIENTES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xclientes{
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF];
    float saldo;
    char password[MAX_PASSWORD];
    struct xclientes *next;
} Clientes;




#endif //final da guarda de ficheiro