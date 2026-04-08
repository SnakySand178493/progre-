#include <stdio.h>

int main() {
    int numero;

    while (1) {
        printf("Ingrese un numero: ");
        scanf("%d", &numero);

        if (numero < 0) {
            break;
        }
    }

    printf("Programa terminado.\n");
    return 0;
}