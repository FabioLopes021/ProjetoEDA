#ifndef PROJECT_GRAFO_H      //Guarda de Ficheiro
#define PROJECT_GRAFO_H      //Guarda de Ficheiro

#include "helper.h"



typedef struct xAdjacente
{
    int vertice;
    int origem;
    float peso;
    struct xAdjacente *next;
} Adjacente;

typedef struct xVertices{
    int vertice;
    char geocode[MAX_GEOCODE], nome[MAX_NAME];
    Adjacente *adj;
    struct xVertices *next;
} VerticeList;

typedef struct xAuxCaminho{
    int vertice, visitado, anterior, carga, numMeios, *idmeios;
    float menor;
} AuxCaminho;


const char* NOME_PONTOS[] = { "Campo da Feira","A minha farmacia","Estatua do Bombeiro", "Pingo Doce", "Mercadona", "Digibarcelos", "Retail Parque"
, "Mc Donalds's", "Alcaides de Faria" };

int adicionarVertice(VerticeList **v, int idvertice, char geocode[], char nome[]);

int adicionarAresta(VerticeList *v, int inicio, int fim, float peso);

int existeVertice(VerticeList *v, int idvertice);

int printGrafo(VerticeList *v);

int printGrafoNomes(VerticeList *v);

int printGeocodeVertice(VerticeList *v);

int numVertices(VerticeList  *v);

int geocodePorVertice(VerticeList  *v, int vertice, char *geocode);

int verticePorGeocode(VerticeList  *v, int *vertice, char geocode[]);

int auxprinthistorico(VerticeList *v, char geocode[]);

int visitado(int sequencia[],int pos, int id);

void listarCaminhosAux(VerticeList *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal);

void listarCaminhos(VerticeList *v, int origem, int destino);

void inicializararray(AuxCaminho a[], int max);

int adicionaPesos(VerticeList *v, AuxCaminho *caminho, int vertice, int numvertices, float peso);

int escolherProximo(AuxCaminho *caminho, int numVertices, int atual,  int *anterior, float *peso);

int numVerticesViagem(AuxCaminho *caminho, int destino);

int* contruirCaminho(AuxCaminho *caminho, int destino);

float menorCaminho(VerticeList *v, int origem, int destino);

void readGrafo(VerticeList** v);

void guardarGrafo(VerticeList* v);

int lerVerticePessoa(VerticeList *v);



#endif //final da guarda de ficheiro