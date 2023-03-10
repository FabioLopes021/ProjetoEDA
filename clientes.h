#ifndef PROJECT_CLIENTES_H      //Guarda de Ficheiro
#define PROJECT_CLIENTES_H      //Guarda de Ficheiro

#include "helper.h"


typedef struct xclientes{
    char name[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL];
    float saldo;
    struct xclientes *next;
} Clientes;


// Inserção de um novo registo
void inserirCliente(Clientes** inicio, char nome[], char morada[], char NIF[], float saldo, char password[], char email[]); 

// Funçao para ler os dados do cliente para serem envidos a funçao "inserirCliente"
void lerDados(Clientes** inicio);

// listar na consola o conteúdo da lista ligada
int listarCliente(Clientes* inicio); 

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeCliente(Clientes* inicio, char NIF[]);

// Determinar existência do email na lista ligada 'inicio'
int existeClienteEmail(Clientes* inicio, char email[]);

// Remover um meio a partir do seu código
Clientes *removerCliente(Clientes **inicio, char NIF[], int i);

// Funçoes para verificar informaçoes de Login
Clientes *loginClientes(Clientes **inicio,char password[], char email[]);

// Funçao para alterar o nome de um utilizador
void alterarNomeCliente(Clientes *cliente, char novonome[]);

// Funçao para alterar a morada de um utilizador
void alterarMoradaCliente(Clientes *cliente, char novamorada[]);

// Funçao para alterar o NIF de um utilizador
void alterarNIFCliente(Clientes *cliente, char novoNIF[]);

// Funçao para alterar o email de um utilizador
void alterarEmailCliente(Clientes *cliente, char novoemail[]);

// Funçao para alterar a password de um utilizador
void alterarPasswordCliente(Clientes *cliente, char novapassword[]);




#endif //final da guarda de ficheiro