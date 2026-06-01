//Imprime tablas de multiplicar
#include <stdio.h>

void main(){
    int n,i = 0;
    printf("Ingresa un número\n");
    scanf("%d", &n);

    for (i=1; i<=10; ++i)
        printf("%d x %d = %d\n", n, i, n*i);

    //for (i=1; i<=10; i++)
        //printf("%d x %d = %d\n", n, i, n*i);
     
}
//++i preincremento ejecuta la suma primero y luego usa el resultado
//i++ postincremento primero usa el resultado y luego ejecuta la suma primero