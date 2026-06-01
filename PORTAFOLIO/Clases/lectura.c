/* Este programa muestra como leer datos del teclado para llenar de información un arreglo */

#include <stdio.h>

int main(){
    float cal[30];

    for(int i=0; i<30; ++i){
        printf("Ingresa la calificación del alumno: ");
        scanf("%f", &cal[i]);
    }
    printf("[")
    for(int i=0; i<5; ++i){
        printf("%.2f ", cal[i]);
    }
    printf("]\n");
}