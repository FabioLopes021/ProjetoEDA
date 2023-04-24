#ifndef PROJECT_MEIO_H      //Guarda de Ficheiro
#define PROJECT_MEIO_H      //Guarda de Ficheiro

#include "clientes.h"


typedef struct xMeio{       //Declaraçao da estrutura de Meios de Transporte
    int codigo;             //Codigo unico para identificar cada meio
    char tipo[MAX_CODE];    //Nome do tipo de transporte
    int bateria;            //Percentagem de Bateria do meio
    float autonomia;        //Autonomia do meio
    float custo;            //custo por km do meio
    int idaluger;           //id do cliente que tem o meio alugado
    struct xMeio *next;     //Next node
} Meio;                     


// Inserção de um novo registo
void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut, float custo,int idaluguer); 

// Funçao para ler os dados do cliente e de seguida envia-los a funçao "inserirMeio"
void lerDadosMeio(Meio** inicio);

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(Meio* inicio, int codigo); 

// Retorna o Numerode leios livres
int NumMeiosLivres(Meio* inicio);

// Verifica se um meio esta livre ou alugado
int meioLivre(Meio* inicio, int codigo);

// Verifica se um meio esta alugado a um determinado Cliente
int meioAlugado(Meio* inicio, int codigo, int idCliente);

// listar na consola o conteúdo da lista ligada
int listarMeios(Meio* inicio, int i);

// Listar na consola os meios livres
int listarMeiosLivres(Meio* inicio, int i);

// listar na consola os meios alugados por um determinado utilizador, retorna ainda o numero de meios alugados pelo mesmo
int listarMeiosAlugados(Meio* inicio, int idCliente, int i);

// Remover um meio a partir do seu código
Meio *removerMeio(Meio **inicio, int adr, int i);

// Funçao para alugar um meio a um determinado cliente
void alugarMeio(Meio *inicio, int idCliente, int id);

// Terminar aluguer de meio um meio
void terminarAluguer(Meio *inicio, int id);

// Altera o tipo de um meio
void alterarTipoMeio(Meio *inicio, char tipo[], int id);

// Altera a bateria de um meio
void alterarBateria(Meio *inicio, int bat, int id);

// Altera a autonomia de um meio
void alterarAutonomia(Meio *inicio, float aut, int id);

// Altera o custo de um meio
void alterarCusto(Meio *inicio, float custo, int id);

// Gera um codigo unico para a inserção de um novo meio
int genereateCodigo(Meio *inico);

// Carrega para memoria os dados dos meios guardados num ficheiro 
void readMeios(Meio **inicio);

// Guarda num ficheiro os dados dos meios em memoria
void guardarMeios(Meio *inicio);

// Guarda num ficheiro binario os dados dos meios em memoria
void guardarMeioBin(Meio *inicio);

// Carrega para memoria os dados dos meios guardados num ficheiro binario
void lerMeioBin(Meio **inicio);

// Ordena os meios da lista por ordem decrescente de autonomia
int ordenarMeios(Meio **inicio);

#endif //final da guarda de ficheiro