#include <stdio.h>

/*
INSTRUCCIONES:
Usa operador ternario para obtener el mayor
*/

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int mayor = (a>b) ? a : b;

    printf("Mayor: %d\n", mayor);

    return 0;
}
