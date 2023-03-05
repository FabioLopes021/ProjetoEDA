#ifndef PROJECT_MEIO_H      //Guarda de Ficheiro
#define PROJECT_MEIO_H      //Guarda de Ficheiro

#define MAX_CODE 50         //Definir o limite para o nome do tipo de transporte

typedef struct xMeio{
    int codigo;             //Codigo unico para identificar cada meio
    char tipo[MAX_CODE];    //Nome do tipo de transporte
    int bateria;            //Percentagem de Bateria do meio
    float autonomia;        //Autonomia do meio
    struct xMeio *next;     //Next node
} Meio;


// Inserção de um novo registo
void inserirMeio(Meio** inicio, int cod, char tipo[], float bat, float aut); 

// listar na consola o conteúdo da lista ligada
int listarMeios(Meio* inicio); 

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(Meio* inicio, int codigo); 

// Remover um meio a partir do seu código
Meio *removerMeio(Meio **inicio, int adr, int i);


#endif //final da guarda de ficheiro