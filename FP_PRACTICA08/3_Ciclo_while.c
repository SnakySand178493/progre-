#include <stdio.h>

int main() {
    int num, positivos = 0, negativos = 0;
    printf("Ingresa números (0 para terminar):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) break;
        if (num > 0) positivos++;
        else if (num < 0) negativos++;
    }
    printf("Positivos: %d\nNegativos: %d\n", positivos, negativos);
    return 0;
}
