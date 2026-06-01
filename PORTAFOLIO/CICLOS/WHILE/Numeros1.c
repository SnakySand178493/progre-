#include <stdio.h>
#include <stdbool.h>

int main(){
    int num, cuad, suma = 0;
    printf("Ingresa un número: \n");
    scanf("%i", &num);

    while(num != 0){
        cuad = num * num;
        suma += cuad;
        printf("El cuadrado de %i es %i\n", num, cuad);
        printf("Ingresa un número: \n");
        scanf("%i", &num);

    }
    printf("La suma total es: %d\n", suma);
    return 0;
}