#include <stdio.h>

/*
INSTRUCCIONES:
Determina cuál número es el mayor
*/

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (a > b && a > c) {
        printf("A es el mayor\n");
    } else if (b > a && b > c) {
        printf("B es el mayor\n");
    } else {
        printf("C es el mayor\n");
    }

    return 0;
}