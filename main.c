#include <stdlib.h>
#include <stdio.h>
#include "meio.h"
#include "meio.c"


int main(){
    Meio *h = NULL;

    int code, bateria;
    float autonomia;
    char tip[MAX_CODE];

    for (int i = 0; i < 3; i++){
        printf("codigo, bateria, autonomia, tipo\n");
        scanf("%d", &code);
        scanf("%d", &bateria);
        scanf("%f", &autonomia);
        scanf("%s", tip);
        inserirMeio(&h, code, tip, bateria, autonomia);
    }
    printf("existe: %d",existeMeio(h,10));
    printf("-----------Listagem---------------\n");
    listarMeios(h);



    return 1;
}


    //int codigo;
    //char tipo[MAX_CODE];
    //int bateria;
    //float autonomia;