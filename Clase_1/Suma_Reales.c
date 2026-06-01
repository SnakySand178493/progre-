//Programa para sumar dos números reales
#include <stdio.h>

int main(){
    float a, b, c;
    printf("Ingresa el primer número\n");
    scanf("%f", &a);
    printf("Ingresa el segundo número\n");
    scanf("%f", &b);
    c=a+b;
    printf("El resultado de sumar %.2f + %.2f = %.2f", a, b, c);
    return 0;
}