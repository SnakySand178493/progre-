/*
Este programa muestra como leer datos del teclado para llenar de información un arreglo
*/
#include <stdio.h>

int main(){
    float cal[5];

    for (int i=0; i<5; ++i){
        printf("Ingresa una calificación: ");
        scanf("%f", &cal[i]);
    }

    printf("[ ");
    for (int i=0; i<5; ++i){
        printf("%.2f, ", cal[i]);
        
    }
    printf("]\n");
}