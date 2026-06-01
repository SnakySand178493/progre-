#include <stdio.h>
#include <stdbool.h>

void main(){
    int num, cuad, suma = 0;

    do{
        printf("Ingresa un número: \n");
        scanf("%i", &num); 
        cuad = num * num;
        suma += cuad; 
        printf("El cuadrado de %i es %i\n", num, cuad);
    }while(num != 0);

    printf("La suma total es: %d\n", suma);
}