#ifndef PROJECT_MEIO_H      //Guarda de Ficheiro
#define PROJECT_MEIO_H      //Guarda de Ficheiro

#define MAX_CODE 50         //Definir o limite para o nome do tipo de transporte
#include "clientes.h"

typedef struct xMeio{
    int codigo;             //Codigo unico para identificar cada meio
    char tipo[MAX_CODE];    //Nome do tipo de transporte
    int bateria;            //Percentagem de Bateria do meio
    float autonomia;        //Autonomia do meio
    float custo;            //custo por km do meio
    Clientes *aluguer;
    struct xMeio *next;     //Next node
} Meio;


// Inserção de um novo registo
void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float custo); 

void lerDadosMeio(Meio** inicio);

// listar na consola o conteúdo da lista ligada
int listarMeios(Meio* inicio);

// Listar meios livres
int listarMeiosLivres(Meio* inicio);

// listar na consola os meios alugados por um determinado utilizador e tambem retornar o numero
int listarMeiosAlugados(Meio* inicio, Clientes *c, int i);

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(Meio* inicio, int codigo); 

// Remover um meio a partir do seu código
Meio *removerMeio(Meio **inicio, int adr, int i);

// Funçao para alugar um meio
void alugarMeio(Meio *inicio, Clientes *alugar, int id);

// Terminar aluguer de meio
void terminarAluguer(Meio *inicio, Clientes *alugar, int id);

// Funçao para alterar o tipo de um meio
void alterarTipoMeio(Meio *inicio, char tipo[], int id);

void alterarBateria(Meio *inicio, int bat, int id);

void alterarAutonomia(Meio *inicio, float aut, int id);

void alterarCusto(Meio *inicio, float custo, int id);

void readMeios(Meio **inicio);

void guardarMeios(Meio *inicio);


#endif //final da guarda de ficheiro