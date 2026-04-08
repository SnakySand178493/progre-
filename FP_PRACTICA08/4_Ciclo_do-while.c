#include <stdio.h>

int main() {
    int num, suma = 0;

    do {
        printf("Ingrese un numero (0 para terminar): ");
        scanf("%d", &num);
        suma += num;
    } while (num != 0);

    printf("La suma total es: %d\n", suma);

    return 0;
}