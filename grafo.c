#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"



int adicionarVertice(VerticeList **v, int idvertice, char geocode[]){

    if (existeVertice(*v, idvertice) == 1)
        return 0;

    VerticeList *new = (VerticeList*)malloc(sizeof(VerticeList));
    VerticeList *aux = *v;

    new->vertice = idvertice;
    strcpy(new->geocode, geocode);
    new->adj = NULL;
    new->next = NULL;

    if (*v == NULL){
        *v = new;
    }
    else{
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = new;
    }

    return 1;
}

int adicionarAresta(VerticeList *v, int inicio, int fim, float peso){

    if (v == NULL)
        return 0;

    if ((existeVertice(v, inicio) != 1) || (existeVertice(v, fim) != 1))
        return 0;

    while(v->vertice != inicio){
        v = v->next;
    }
    
    Adjacente *new = (Adjacente*)malloc(sizeof(Adjacente));
    new->peso = peso;
    new->vertice = fim;
    new->next = NULL;
    
    if(v->adj != NULL){
        Adjacente *aux = v->adj;    
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = new;
    }else
        v->adj = new;

    return 1;
}


int existeVertice(VerticeList *v, int idvertice){
    if (v == NULL)
        return 2;
    
    while(v != NULL){
        if (v->vertice == idvertice)
            return 1;
        v = v->next;
    }

    return 0;
}

int printGrafo(VerticeList *v){

    if(v == NULL)
        return 0;

    Adjacente *aux;

    printf("-----------Grafo-------------\n");
    while(v != NULL){
        printf("Vertice: %d", v->vertice);
        aux = v->adj;
        while(aux != NULL){
            printf("-> %d", aux->vertice);
            aux = aux->next;
        }
        printf(";\n");
        v = v->next;
    }

    return 1;
}


int printGrafoNomes(VerticeList *v){

    if(v == NULL)
        return 0;

    Adjacente *aux;

    printf("-----------Grafo-------------\n");
    while(v != NULL){
        printf("Vertice: %s", NOME_PONTOS[v->vertice]);
        aux = v->adj;
        while(aux != NULL){
            printf("-> %s", NOME_PONTOS[aux->vertice]);
            aux = aux->next;
        }
        printf(";\n");
        v = v->next;
    }

    return 1;
}


int printGeocodeVertice(VerticeList *v){
    if (v == NULL)
        return 0;
    
    printf("Localizaçoes\n");
    while (v != NULL)
    {
        printf("vertice: %d -> %s\n", v->vertice, NOME_PONTOS[v->vertice]);
        v = v->next;
    }
    
    return 1;
}


int numVertices(VerticeList  *v){
    int i = 0;

    if (v == NULL)
        return i;
    
    while(v != NULL){
        i++;
        v = v->next;
    }

    return i;
}

int geocodePorVertice(VerticeList  *v, int vertice, char *geocode){
    if(v == NULL)
        return 0;
    while(v != NULL){
        if (v->vertice == vertice){
            strcpy(geocode, v->geocode);
            return 1;
        }
        v = v->next;
    }

    return 0;
}

// Determinar se vértice 'id' já foi visitado
int visitado(int sequencia[],int pos, int id){
  int i;
  for(i=0;i<pos;i++) if (sequencia[i]==id) return(1);
  return(0);
}

// Listar os caminhos existentes entre dois vértices passados
// por parâmetro
void listarCaminhosAux(VerticeList *v, int origem, int destino, int sequencia[], int posicao, int pesoTotal){
    int i;
    VerticeList *head = v;
    Adjacente *aux;  \
    sequencia[posicao] = origem;
    if (origem==destino) {
        for(i=0;i<posicao;i++) printf("%d->",sequencia[i]); // escrita de um caminho
        printf("%d (%d)\n",destino,pesoTotal);
    }
    else {
        while(v->vertice != origem && v != NULL)
            v = v->next;
        aux = v->adj; 
        while (aux != NULL){
        if (!visitado(sequencia,posicao,aux->vertice)) 
            listarCaminhosAux(head,aux->vertice,destino,sequencia,posicao+1,
            pesoTotal+aux->peso);
        aux = aux->next;
    }
    }
}

void listarCaminhos(VerticeList *v, int origem, int destino){
  int sequencia[numVertices(v)];
  listarCaminhosAux(v,origem,destino,sequencia,0,0);
}


void readGrafo(VerticeList** v){
    FILE* fp;
    char line[1024], geocode[MAX_GEOCODE];
    int listVertice, i, aux,j,z;
    float aux1;
	char* campo1, * campo2;

    fp = fopen("grafos.txt","r");

    if (fp != NULL) {
        j = 0; 
		while (fgets(line, sizeof(line), fp)) {

            campo1 = strtok(line, ";");
            if (j == 0){
                z = 1;
                while(campo1 != NULL){
                    if(z % 2 == 1){
                        listVertice = atoi(campo1);
                    }else{
                        strcpy(geocode, campo1);
                        adicionarVertice(&(*v), listVertice, geocode);    
                    }   
                    z++;
                    campo1 = strtok(NULL, ";");
                }
            }else{
                listVertice = atoi(campo1);
                campo2 = strtok(NULL,";");
                i = 1;
                while(campo2 != NULL){
                        
                    if(i%2 == 0){
                        aux1 = atof(campo2);
                        adicionarAresta(*v, listVertice, aux, aux1);
                    }else{
                        aux = atoi(campo2);
                    }
                    i++;
                    campo2 = strtok(NULL, ";");
                }
            }
           j++;
		}
        printf("Grafo carregado com sucesso\n");
		fclose(fp);
	}
	else {
		printf("Erro ao abrir o ficheiro do Grafo");
	}
}


void guardarGrafo(VerticeList* v){
    FILE* fp;
    VerticeList *head = v;
    Adjacente *aux;
    fp = fopen("grafos.txt","w");

    if (fp!=NULL){      

        while(v != NULL){  
            fprintf(fp,"%d;%s;", v->vertice, v->geocode);
            v = v->next;
        }
        fprintf(fp,"\n");
        for(v = head; v != NULL ;v = v->next){
            fprintf(fp,"%d;",v->vertice);
            for(aux = v->adj; aux != NULL; aux = aux->next){
                fprintf(fp,"%d;%.2f;",aux->vertice, aux->peso);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);

        printf("Grafo guardado com sucesso\n");
    }else
        printf("Erro ao abrir ficheiro Grafo\n");
}

