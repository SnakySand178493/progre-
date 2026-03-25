#include <stdio.h>

/*
INSTRUCCIONES:
Completa la condición del if para que imprima "Es positivo"
cuando el número sea mayor que cero.
*/

int main() {
    int num;
    printf("Ingresa un numero: ");
    scanf("%d", &num);

    if (num>0) {
        printf("Es positivo\n");
    }

    return 0;
}
