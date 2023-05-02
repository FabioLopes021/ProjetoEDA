#ifndef PROJECT_HISTORICO_H      //Guarda de Ficheiro
#define PROJECT_HISTORICO_H      //Guarda de Ficheiro

#include "helper.h"
#include <time.h>

typedef struct xhistorico{       // Declaraçao da estrutura de Clientes 
    int idCliente, idMeio, id ;  // ID do Cliente, do meio que o mesmo alugou e id da entrada no historico
    double custoFinal;           // Custo total da viagem (Apenas é calculado quando é terminado o aluguer)
    float Custo;                 // Custo por minuto do meio   
    struct tm inicio;      // Hora de inicio de aluguer 
    struct tm fim;         // Hora de fim de aluguer
    struct xhistorico *next;     // Next node
} Historico;


void inserirHistorico(Historico** inicio, int idc, int idm, int ide, double custof, float custo, struct tm start, struct tm end);

// Inserção inicio de aluguer
void inserirHistoricoInicio(Historico** inicio, int idc, int idm, float custo);

// Inserção final de aluguer
int inserirHistoricoFinal(Historico* inicio, int ide);

// Remover uma entrada a partir do seu ID
Historico *removerHistorico(Historico **inicio, int id, int i);

// Gera um codigo unico para uma nova entrada no historico
int generateidHistorico(Historico *inicio);

int existeHistorico(Historico* inicio, int id);

double calculoCustoTotal(Historico *entrada, int ide);

int idEntrada(Historico *entrada, int idm);

int imprimirHistorico(Historico *inicio);


int imprimirHistoricoCliente(Historico *inicio, int id);


int numEntradasCliente(Historico *inicio, int id);

// Carrega para memoria os dados do Historico guardados num ficheiro 
void readHistorico(Historico **inicio);

// Guarda num ficheiro os dados dos Historico em memoria
void guardarHistorico(Historico* inicio);

// Guarda num ficheiro binario os dados do Historico em memoria
void lerHistoricoBin(Historico **inicio);

// Carrega para memoria os dados do Historico guardados num ficheiro binario
void guardarHistoricoBin(Historico *inicio);

#endif //final da guarda de ficheiro