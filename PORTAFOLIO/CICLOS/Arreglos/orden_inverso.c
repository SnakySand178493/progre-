/*Programa que invierta el orden de un arreglo
ej: [1, 2, 3, 4, 5]     [5, 4, 3, 2, 1]*/

#include <stdio.h>
#define MAX 1000

int main(){
    int array[MAX];
    int n=0, m=0, p=0;//n = variable auxiliar para intercambio

    printf("Ingresa la cantidad de datos: \n");
    scanf("%d", &n);

    //Leer datos
    for (int i = 0; i < n ;i++){
        printf("Ingresa el dato [%d]: ", i);
        scanf("%d", &array[i]);
    }

    //Cambio
    for (int i = 0; i < n/2; i++){
        p=array[i];
        array[i]=array[n-1-i];
        array[n-1-i]=p;
    }

    //Imprimir
    printf("El arreglo invertido es:\n[ "); 
    for (int i = 0; i < n; i++){
        printf("%d", array[i]);
        if (i==n-1)
            continue;
            printf(", ");
    }
    printf(" ]\n"); 
    
    return 0;
}