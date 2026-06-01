#include <stdio.h>
//Programa para resta
// Al iniciar un programa la memoria tiene siembre un numero "basura"

int main(){
    int x, y;
    printf("x = %d\n", x);
    x = 6;
    printf("x = %d\n", x);
    y = 2;
    printf("y = %d\n", y);
    x -= 1;
    printf("x = %d\n", x);
    x -= y;
    printf("x = %d\n", x);
    return 0;
}