#ifndef PROJECT_GRAFO_H      //Guarda de Ficheiro
#define PROJECT_GRAFO_H      //Guarda de Ficheiro

#include "helper.h"


typedef struct xAdjacente
{
    int vertice;
    float peso;
    struct xAdjacente *next;
} Adjacente;

typedef struct xVertices{
    int vertice;
    Adjacente *adj;
    struct xVertices *next;
} VerticeList;








#endif //final da guarda de ficheiro