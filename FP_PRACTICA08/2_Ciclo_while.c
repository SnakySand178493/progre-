#include <stdio.h>

int main() {
    int num, suma = 0;
    printf("Ingresa números (0 para terminar):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) break;
        suma += num;
    }
    printf("La suma es: %d\n", suma);
    return 0;
}
