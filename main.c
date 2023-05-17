#include <stdlib.h>
#include <stdio.h>
#include "helper.h"
#include "helper.c"
#include "meio.h"
#include "meio.c"
#include "clientes.h"
#include "clientes.c"
#include "gestores.h"
#include "gestores.c"
#include "historico.h"
#include "historico.c"
#include "grafo.h"
#include "grafo.c"


int main(){
    Historico *p = NULL;
    Meio *h = NULL;
    VerticeList *v = NULL; 
    Clientes *c = NULL, *loginc = NULL;
    Gestores *g = NULL, *loging = NULL;
    int logmenu = 0;
    int menu1, menuc, menug, menuconta, id, num = 0, menualtc, menualtm, menualtg, bateria, idmeio, count, i = 0, ident, aux;
    
    char nome[MAX_NAME], morada[MAX_MORADA], NIF[MAX_NIF], password[MAX_PASSWORD], email[MAX_EMAIL], tipo[MAX_CODE];
    char emaillog[MAX_EMAIL], passwordlog[MAX_PASSWORD], locfinal[MAX_GEOCODE], locinicializacao[MAX_GEOCODE];
    float saldo, autonomia, custo, custoh;


    //Carregar dados dos ficheiros txt
    readGrafo(&v);
    readMeios(&h);
    //readClientes(&c);
    //readGestores(&g);
    readHistorico(&p);
    

    //Carregar dados dos ficheiros bin
    //lerMeioBin(&h)
    lerGestoresBin(&g);
    lerCLientesBin(&c);
    //lerHistoricoBin(&p);

    ordenarMeios(&h); //Ordenar Meios por ordem decrescente de Autonomia
    printGrafo(v);
    EsperarQuePrimaEnter();
    //Estrutura do programa
    do{
        menu1 = menu();     //Receber opçao do utilizador
        switch(menu1){
            case 1:         //Realizar Login
                printf("indique o seu email: ");
                scanf("%s", emaillog);

                printf("Indique a sua password: ");
                scanf("%s", passwordlog);

                encriptPassword(passwordlog);

                logmenu = funcaoLogin(&c, &g, passwordlog, emaillog, &loginc, &loging);

                switch(logmenu){
                    case 1:     //login bem-sucedido de Clientes
                        if (loginc != NULL){
                            generico();
                            printf("\n\nLogin efetuado com sucesso. (cliente: %s)\n\n", loginc->name);
                            EsperarQuePrimaEnter();
                            do{
                                menuc = menuclientes(loginc->name, loginc->saldo);      //Receber opçao do utilizador
                                
                                switch(menuc){
                                    case 1:     //Alugar meio
                                        i = 0;
                                        ordenarMeios(&h);
                                        if(NumMeiosLivres(h) != 0){
                                            listarMeiosLivres(h, 0);
                                            do{
                                                if(i == 0)
                                                    printf("\nIndique um codigo para o meio:");
                                                if(i > 0)
                                                    printf("\nIndique um codigo valido:");
                                                scanf("%d", &id);
                                                i++;
                                            }while((existeMeio(h, id) == 0) || (meioLivre(h, id) == 0));
                                            if(custoMeio(h, id) < loginc->saldo){
                                                alugarMeio(h, loginc->id, id);
                                                custoh = custoMeio(h, id);
                                                inserirHistoricoInicio(&p, loginc->id, id, custoh, localatual(h, id));
                                                EsperarQuePrimaEnter();
                                            }else
                                                printf("Nao é possivel alugar o meio indicado pois nao tem dinheiro suficiente.");
                                            
                                            id = 0;
                                        }else{
                                            printf("Nao existem meios disponiveis\n");
                                            EsperarQuePrimaEnter();
                                        }
                                        break;
                                    case 2:     //Terminar aluguer 
                                        num = listarMeiosAlugados(h, loginc->id, 0);
                                        if (num == 0){
                                            printf("\nEste utilizador nao tem meios alugados\n");
                                        }else{
                                            i = 0;
                                            do{
                                                if (i == 0)
                                                    printf("\nIndique o id do meio que deseja terminar o aluger: ");
                                                if (i > 0)
                                                    printf("\nIndique o id de um meio que tenha alugado: ");
                                                scanf("%d", &id);
                                                i++;
                                            }while((meioAlugado(h, id, loginc->id) == 0));
                                            strcpy(locfinal, "");
                                            aux = lerVertice(v, locfinal);
                                            ident = idEntrada(p, id);
                                            inserirHistoricoFinal(p, ident, locfinal);
                                            terminarAluguer(h,id);
                                            pagamento(loginc, calculoCustoTotal(p, ident));
                                            AtualizarBateria(h, id, calculoDist( p, v, ident));
                                            AtualizarAutonomia(h, id,calculoDist( p, v, ident));
                                            if (aux == 1){
                                                atuallizarLocalizacao(h, v, id, locfinal);
                                                printf("Aluguer terminado com sucesso.\n");
                                            }else
                                                printf("Ocorreu um erro, aluguer terminado sem localizaçao final.\n");
                                            EsperarQuePrimaEnter();
                                        }
                                        aux = 0;
                                        num = 0;
                                        id = 0;                                        
                                        break;
                                    case 3:
                                        do{
                                            menualtc = menuAlterarDadosCliente();   //Receber opçao do utilizador
                                            switch(menualtc){
                                                case 1:     // Alterar nome
                                                    clearbuffer();
                                                    printf("\nIndique o seu nome: ");
                                                    fgets(nome, MAX_NAME, stdin);
                                                    nome[strlen(nome)-1] = '\0';
                                                    alterarNomeCliente(loginc, nome);
                                                    break;
                                                case 2:     // Alterar morada
                                                    clearbuffer();
                                                    printf("\nIndique a sua morada: ");
                                                    fgets(morada, MAX_MORADA, stdin);
                                                    morada[strlen(morada) - 1] = '\0';
                                                    alterarMoradaCliente(loginc, morada);
                                                    break;
                                                case 3:     // Alterar NIF
                                                    clearbuffer();
                                                    printf("\nIndique o seu NIF: ");
                                                    fgets(NIF, MAX_NIF, stdin);
                                                    NIF[MAX_NIF] = '\0';
                                                    alterarNIFCliente(loginc, NIF);
                                                    break;
                                                case 4:     // Alterar email
                                                    clearbuffer();
                                                    printf("\nIndique o seu email: ");
                                                    fgets(email, MAX_EMAIL, stdin);
                                                    email[strlen(email)-1] = '\0';
                                                    alterarEmailCliente(loginc, email);
                                                    break;
                                                case 5:     // Alterar  password
                                                    clearbuffer();    
                                                    printf("\nIndique a sua password: ");
                                                    fgets(password, MAX_PASSWORD, stdin);
                                                    password[strlen(password)-1] = '\0';
                                                    alterarPasswordCliente(loginc, password);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                        }while(menualtc != 0);
                                        break;
                                    case 4:     //Carregar Saldo
                                        printf("Indique o saldo que deseja carregar: ");
                                        scanf("%f", &saldo);
                                        carregarSaldo(loginc, saldo);
                                        break;
                                    case 5:     //Imprimir dados de Cliente na consola
                                        printCliente(loginc);
                                        break;
                                    case 6:     //Remover conta
                                        removerCliente(&c, loginc->id, 1);
                                        generico();
                                        printf("\nConta removida com sucesso, a voltar ao menu principal..\n\n");
                                        EsperarQuePrimaEnter();
                                        menuc = 0;
                                        break;
                                    case 7:
                                        imprimirHistoricoCliente(p, v, loginc->id);
                                        EsperarQuePrimaEnter();
                                        break;
                                    case 8:
                                        if(NumMeiosLivres(h) != 0){
                                            aux = lerVerticePessoa(v);
                                            if(aux != -1){
                                                float raio;
                                                printf("Indique o raio em que deseja procurar: ");
                                                scanf("%f", &raio);
                                                listarMeiosRaio(h,v,aux,raio);
                                            }
                                        }else{
                                            printf("Nao existem meios disponiveis");
                                        }
                                        aux = 0;
                                        EsperarQuePrimaEnter();
                                        break;
                                    case 0:
                                        generico();
                                        printf("\nA sair da conta...\n\n");
                                        EsperarQuePrimaEnter();
                                        break;
                                }
                            }while(menuc != 0);
                        }
                        loginc = NULL;
                        logmenu = 0;
                        break;
                    case 2:     //login bem-sucedido de Gestores
                        if (loging != NULL){
                            generico();
                            printf("\n\nLogin efetuado com sucesso. (Gestor: %s)\n\n", loging->name);
                            EsperarQuePrimaEnter();
                            do{
                                menug = menucGestores();    //Receber opçao do utilizador
                                
                                switch(menug){
                                    case 1:     //Adicionar meios
                                        lerDadosMeio(&h, v);
                                        break;
                                    case 2:     //Consultar historico
                                        imprimirHistorico(p, v);
                                        EsperarQuePrimaEnter();
                                        break;
                                    case 3:     //Estatisticas
                                        // Em desenvolvimento
                                        break;
                                    case 4:     //Validaçoes
                                        // Em desenvolvimento
                                        break;
                                    case 5:     //Alterar meios
                                        do{
                                            count = 0;
                                            generico();
                                            listarMeios(h, v, 0);
                                            do{
                                                if(count == 0)  
                                                    printf("\nIndique o meio que deseja alterar:");
                                                else   
                                                    printf("\nIndique um meio valido:"); 
                                                scanf("%d", &idmeio);
                                                count++;
                                            }while(!existeMeio(h,idmeio));
                                            menualtm = menuAlterarDadosMeio();
                                            switch(menualtm){
                                                case 1:     // Alterar tipo
                                                    clearbuffer();
                                                    printf("\nIndique o novo tipo do meio: ");
                                                    fgets(tipo, MAX_CODE, stdin);
                                                    tipo[strlen(tipo)-1] = '\0';
                                                    alterarTipoMeio(h, tipo, idmeio);
                                                    break;
                                                case 2:     // Alterar bateria
                                                    printf("\nIndique a nova bateria do meio:");
                                                    scanf("%d", &bateria);
                                                    alterarBateria(h, bateria, idmeio);
                                                    break;
                                                case 3:     // Alterar autonomia
                                                    printf("\nIndique a nova autonomia do meio");
                                                    scanf("%f", &autonomia);
                                                    alterarAutonomia(h, autonomia, idmeio);
                                                    break;
                                                case 4:     // Alterar custo
                                                    printf("\nIndique um novo custo para meio: ");
                                                    scanf("%f", &custo);
                                                    alterarCusto(h, custo, idmeio);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                            break;
                                        }while(menualtc != 0);
                                        break;
                                    case 6:     //Alterar dados
                                        do{
                                            menualtg = menuAlterarDadosGestor();    //Receber opçao do utilizador 
                                            switch(menualtg){
                                                case 1:     // Alterar nome
                                                    clearbuffer();
                                                    printf("\nIndique o seu nome: ");
                                                    fgets(nome, MAX_NAME, stdin);
                                                    nome[strlen(nome)-1] = '\0';
                                                    alterarNomeGestor(loging, nome);
                                                    break;
                                                case 2:     // Alterar morada
                                                    clearbuffer();
                                                    printf("\nIndique a sua morada: ");
                                                    fgets(morada, MAX_MORADA, stdin);
                                                    morada[strlen(morada) - 1] = '\0';
                                                    alterarMoradaGestor(loging, morada);
                                                    break;
                                                case 3:     // Alterar NIF
                                                    clearbuffer();
                                                    printf("\nIndique o seu NIF: ");
                                                    fgets(NIF, MAX_NIF, stdin);
                                                    NIF[MAX_NIF] = '\0';
                                                    alterarNIFGestor(loging, NIF);
                                                    break;
                                                case 4:     // Alterar email
                                                    clearbuffer();
                                                    printf("\nIndique o seu email: ");
                                                    fgets(email, MAX_EMAIL, stdin);
                                                    email[strlen(email)-1] = '\0';
                                                    alterarEmailGestor(loging, email);
                                                    break;
                                                case 5:     // Alterar  password
                                                    clearbuffer();    
                                                    printf("\nIndique a sua password: ");
                                                    fgets(password, MAX_PASSWORD, stdin);
                                                    password[strlen(password)-1] = '\0';
                                                    alterarPasswordGestor(loging, password);
                                                    break;
                                                case 0:
                                                    break;
                                            }
                                        }while(menualtg != 0);
                                        break;
                                    case 7:     // remover meio
                                        i = 0;
                                        listarMeios(h, v, 0);
                                        do{
                                            if(i == 0)
                                                printf("\nIndique um codigo para o meio:");
                                            if(i > 0)
                                                printf("\nIndique um codigo valido:");
                                            scanf("%d", &id);
                                            i++;
                                        }while(!existeMeio(h, id));
                                        removerMeio(&h, id, 1);
                                        break;
                                    case 8:     //remover conta
                                        removerGestor(&g, loging->id, 1);
                                        generico();
                                        printf("\nConta removida com sucesso, a voltar ao menu principal..\n\n");
                                        EsperarQuePrimaEnter();
                                        menug = 0;
                                        break;
                                    case 9:     //remover conta
                                        printGestor(loging);
                                        break;
                                    case 10:
                                        generico();
                                        listarCliente(c, 1);
                                        EsperarQuePrimaEnter();
                                        break;
                                    case 11:    //Listar Meios
                                        generico();
                                        listarMeios(h, v, 0);
                                        EsperarQuePrimaEnter();
                                        break;
                                    case 12:    //Inicializar meio sem localizaçao
                                        generico();
                                        i = 0;
                                        if(NumMeiosSemLocalizacao(h) != 0){
                                            listarMeiosSemLocalizacao(h, 0);
                                            do{
                                                if(i == 0)
                                                    printf("\nIndique um codigo para o meio:");
                                                if(i > 0)
                                                    printf("\nIndique um codigo valido:");
                                                scanf("%d", &id);
                                                i++;
                                            }while(meioSemLocalizacao(h, id) != 1);
                                            strcpy(locinicializacao, "");
                                            aux = lerVertice(v, locinicializacao);
                                            if (aux == 1){
                                                atuallizarLocalizacao(h, v, id, locinicializacao);
                                                printf("Localizaçao adcionada com sucesso.\n");
                                            }else
                                                printf("Ocorreu um erro, meio continua sem localizaçao.\n");
                                            EsperarQuePrimaEnter();
                                            id = 0;
                                        }else{
                                            printf("Nao existem meios disponiveis\n");
                                            EsperarQuePrimaEnter();
                                        }
                                        break;
                                    case 0:     //Logout
                                        generico();
                                        printf("\nA sair da conta...\n\n");
                                        EsperarQuePrimaEnter();
                                        break;
                                }
                            }while(menug != 0);
                        }
                        loging = NULL;
                        logmenu = 0;
                        break;
                    case 0:     //Dados de Login Incorretos
                        generico();
                        printf("\n\nPassword ou email incorretos...\n\n");
                        EsperarQuePrimaEnter();
                        break;
                }
                break;
            case 2:
                //Criaçao de contas
                do{
                    menuconta = menuCriarConta();   //Receber opçao do utilizador
                    switch(menuconta){
                    case 1:     //Criar Conta Cliente
                        printf("\nCriar conta cliente\n");
                        lerDados(&c);
                        break;
                    case 2:     //Criar conta Gestor
                        printf("\nCriar conta gestor\n");
                        lerDadosGestor(&g);
                        break;
                    case 0:
                        break;
                }
                }while(menuconta != 0);
                break;
            case 0:
                break;
        }
    }while(menu1 != 0);

    clearbuffer();   

    //Guardar dados em ficheiro
    //guardarGestores(g);
    //guardarClientes(c);
    guardarMeios(h);
    guardarHistorico(p);
    guardarGrafo(v);

    //Guardar dados em ficheiro binario
    //guardarMeioBin(h);
    guardarClientesBin(c);
    guardarGestoresBin(g);
    //guardarHistoricoBin(p);

    return 1;
}