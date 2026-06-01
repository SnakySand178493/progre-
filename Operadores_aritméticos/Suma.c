#include <stdio.h>
//Programa para suma
// Al iniciar un programa la memoria tiene siembre un numero "basura"

int main(){
    int x, y;
    printf("x = %d\n", x);
    x = 6;
    printf("x = %d\n", x);
    y = 4;
    printf("y = %d\n", y);
    x += 3;
    printf("x = %d\n", x);
    x += y;
    printf("x = %d\n", x);
    return 0;
}