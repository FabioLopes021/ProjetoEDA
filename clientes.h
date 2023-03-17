#ifndef PROJECT_CLIENTES_H      //Guarda de Ficheiro
#define PROJECT_CLIENTES_H      //Guarda de Ficheiro

#include "helper.h"

typedef struct xclientes{       //Declaraçao da estrutura de Clientes 
    int id;                     // ID unico de cada Cliente
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];    //Dados pessoais de Clientes
    float saldo;                //Saldo de Clientes
    struct xclientes *next;     //Next node
} Clientes;                 


// Inserção de um novo registo
void inserirCliente(Clientes** inicio, char nome[], char morada[], char NIF[], float saldo, char password[], char email[], int id); 

// Funçao para ler os dados do cliente e de seguida envia-los a funçao "inserirCliente"
void lerDados(Clientes** inicio);

// listar na consola o conteúdo da lista ligada
int listarCliente(Clientes* inicio, int i); 

// Listar na Consola os dados de um cliente
int printCliente(Clientes *inicio);

// Determinar existência do 'ID' na lista ligada 'inicio'
int existeCliente(Clientes* inicio, int id);

// Determinar existência do email na lista ligada 'inicio'
int existeClienteEmail(Clientes* inicio, char email[]);

// Remover um meio a partir do seu ID
Clientes *removerCliente(Clientes **inicio, int id, int i);

// Verificar informaçoes de Login
Clientes *loginClientes(Clientes **inicio,char password[], char email[]);

// Alterar o nome de um Cliente
void alterarNomeCliente(Clientes *cliente, char novonome[]);

// Funçao para alterar a morada de um utilizador
void alterarMoradaCliente(Clientes *cliente, char novamorada[]);

// Alterar o NIF de um Cliente
void alterarNIFCliente(Clientes *cliente, char novoNIF[]);

// Alterar o Email de um Cliente
void alterarEmailCliente(Clientes *cliente, char novoemail[]);

// Alterar a Password de um Cliente
void alterarPasswordCliente(Clientes *cliente, char novapassword[]);

// Carregar saldo a um Cliente
void carregarSaldo(Clientes *cliente, float quantia);

// Gera um codigo unico para um novo Cliente
int generateidCliente(Clientes *inicio);

// Carrega para memoria os dados dos Clientes guardados num ficheiro 
void readClientes(Clientes **inicio);

// Guarda num ficheiro os dados dos Clientes em memoria
void guardarClientes(Clientes* inicio);

// Guarda num ficheiro binario os dados dos Clientes em memoria
void lerCLientesBin(Clientes **inicio);

// Carrega para memoria os dados dos Clientes guardados num ficheiro binario
void guardarClientesBin(Clientes *inicio);

#endif //final da guarda de ficheiro