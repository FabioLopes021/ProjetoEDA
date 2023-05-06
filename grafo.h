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
    char geocode[MAX_GEOCODE];
    Adjacente *adj;
    struct xVertices *next;
} VerticeList;


const char* NOME_PONTOS[] = { "Campo da Feira","A minha farmacia","Estatua do Bombeiro", "Pingo Doce", "Mercadona", "Digibarcelos", "Retail Parque"
, "Mc Donalds's", "Alcaides de Faria" };

int adicionarVertice(VerticeList **v, int idvertice, char geocode[]);

int adicionarAresta(VerticeList *v, int inicio, int fim, float peso);

int existeVertice(VerticeList *v, int idvertice);

int printGrafo(VerticeList *v);

int printGrafoNomes(VerticeList *v);

int printGeocodeVertice(VerticeList *v);

int numVertices(VerticeList  *v);

int geocodePorVertice(VerticeList  *v, int vertice, char *geocode);

int verticePorGeocode(VerticeList  *v, int *vertice, char geocode[]);

int visitado(int sequencia[],int pos, int id);

void listarCaminhosAux(VerticeList *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal);

void listarCaminhos(VerticeList *v, int origem, int destino);

void readGrafo(VerticeList** v);

void guardarGrafo(VerticeList* v);





#endif //final da guarda de ficheiro