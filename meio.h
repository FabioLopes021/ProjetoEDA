#ifndef PROJECT_MEIO_H      //Guarda de Ficheiro
#define PROJECT_MEIO_H      //Guarda de Ficheiro

#include "clientes.h"
#include "grafo.h"


typedef struct xMeio{       //Declaraçao da estrutura de Meios de Transporte
    int codigo;             //Codigo unico para identificar cada meio
    int metrosQ;           //Numero de metros quadrados que o meios ocupa (importate para a recolha dos meios)
    char tipo[MAX_CODE];    //Nome do tipo de transporte
    int bateria;            //Percentagem de Bateria do meio
    char geocode[MAX_GEOCODE];            //Codigo que permite saber a localizaçao do meio
    float autonomia, autonomiaMax;        //Autonomia do meio
    float custo;            //custo por km do meio
    int idaluger;           //id do cliente que tem o meio alugado
    struct xMeio *next;     //Next node
} Meio;


void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float autMax, float custo, int idaluguer, char geocode[], int metrosQ);
void lerDadosMeio(Meio** inicio, VerticeList *v);
int recarregarMeios(Meio *inicio, VerticeList *v, int idmeio, int verticePosto);
int AtualizarAutonomia(Meio *inicio, int id , float distPrec);
int AtualizarBateria(Meio *inicio, int id , float distPrec);
float CalculoBateria(float autonomiaMax, float autonomia );
int existeMeio(Meio* inicio, int codigo);
char* localatual(Meio* inicio, int codigo);
int atuallizarLocalizacao(Meio* inicio, VerticeList *v, int codigo, char novolocal[]);
int NumMeiosLivres(Meio* inicio);
int NumMeiosSemLocalizacao(Meio* inicio);
int meioLivre(Meio* inicio, int codigo);
int meioSemLocalizacao(Meio* inicio, int codigo);
int meioAlugado(Meio* inicio, int codigo, int idCliente);
int listarMeios(Meio* inicio, VerticeList *v, int i);
int listarMeiosLivres(Meio* inicio, VerticeList *v, int i);
int listarMeiosSemLocalizacao(Meio* inicio, int i);
int listarMeiosAlugados(Meio* inicio, VerticeList *v, int idCliente, int i);
int auxPrintMeios(VerticeList *v, Meio * inicio);
int listarDeterminadosMeiosRaio(Meio* inicio, VerticeList *v, int origem, float raio, char tipomeio[]);
int listarMeiosRaio(Meio* inicio, VerticeList *v, int origem, float raio);
int listarMeiosLocal(Meio* inicio, VerticeList *v, int local);
Meio *removerMeio(Meio **inicio, int adr, int i);
void alugarMeio(Meio *inicio, int idCliente, int id);
void terminarAluguer(Meio *inicio, int id);
void alterarTipoMeio(Meio *inicio, char tipo[], int id);
void alterarBateria(Meio *inicio, int bat, int id);
void alterarAutonomia(Meio *inicio, float aut, int id);
void alterarCusto(Meio *inicio, float custo, int id);
int genereateCodigo(Meio *inicio);
float custoMeio(Meio *inicio, int id);
void readMeios(Meio **inicio);
void guardarMeios(Meio* inicio);
void guardarMeioBin(Meio *inicio);
void lerMeioBin(Meio **inicio);
int ordenarMeios(Meio **inicio);
int cargaPorId(Meio *inicio, int id);



#endif //final da guarda de ficheiro