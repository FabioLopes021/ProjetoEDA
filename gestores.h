#ifndef PROJECT_GESTORES_H      //Guarda de Ficheiro
#define PROJECT_GESTORES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xgestores{
    char name[MAX_NAME], morada[MAX_MORADA];
    int nif;
    char password[MAX_PASSWORD];
    struct xgestores *next;
} Gestores;




#endif //final da guarda de ficheiro