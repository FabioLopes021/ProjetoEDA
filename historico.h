#ifndef PROJECT_HISTORICO_H      //Guarda de Ficheiro
#define PROJECT_HISTORICO_H      //Guarda de Ficheiro

#include "helper.h"
#include <time.h>

typedef struct xhistorico{       // Declaraçao da estrutura de Clientes 
    int idCliente, idMeio, id ;  // ID do Cliente, do meio que o mesmo alugou e id da entrada no historico
    double custoFinal;           // Custo total da viagem (Apenas é calculado quando é terminado o aluguer)
    float Custo;                 // Custo por minuto do meio   
    char localinicial[MAX_GEOCODE],localfinal[MAX_GEOCODE];
    struct tm inicio;      // Hora de inicio de aluguer 
    struct tm fim;         // Hora de fim de aluguer
    struct xhistorico *next;     // Next node
} Historico;



void inserirHistorico(Historico** inicio, int idc, int idm, int ide, double custof, float custo, char localinicial[], char localfinal[], struct tm start, struct tm end);
void inserirHistoricoInicio(Historico** inicio, int idc, int idm, float custo, char localinicial[]);
int inserirHistoricoFinal(Historico* inicio, int ide, char localfinal[]);
Historico *removerHistorico(Historico **inicio, int id, int i);
int existeHistorico(Historico* inicio, int id);
double calculoCustoTotal(Historico *entrada, int ide);
float calculoDist(Historico *entrada, VerticeList *v, int ide);
int idEntrada(Historico *entrada, int idm);
int generateidHistorico(Historico *inicio);
int imprimirHistorico(Historico *inicio,VerticeList *v);
int imprimirHistoricoCliente(Historico *inicio,VerticeList *v, int id);
int numEntradasCliente(Historico *inicio, int id);
void readHistorico(Historico **inicio);
void guardarHistorico(Historico* inicio);
void lerHistoricoBin(Historico **inicio);
void guardarHistoricoBin(Historico *inicio);







#endif //final da guarda de ficheiro