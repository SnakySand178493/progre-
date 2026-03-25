#include <stdio.h>

/*
INSTRUCCIONES:
Completa el switch usando "opcion"
*/

int main() {
    int opcion;
    printf("1. Sumar\n2. Restar\n");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1: printf("Elegiste sumar\n"); break;
        case 2: printf("Elegiste restar\n"); break;
        default: printf("Opcion invalida\n");
    }

    return 0;
}
