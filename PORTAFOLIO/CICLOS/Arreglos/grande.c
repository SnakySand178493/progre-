//Programa que busque en un arreglo el elemento más grande

#include <stdio.h>
#define MAX 1000

int main(){
    int n;
    int array[MAX];
    int max=0;

    printf("Ingresa el número de datos:\n");
    scanf("%d", &n);

    for (int i=1; i<=n; i++){
        printf("Ingresa el dato [%i]: ", i);
        scanf("%d", &array[i]);
    }
    for (int i=1; i<=n; i++){
        if (max<array[i]);
        max=array[i];
    }

    printf("El número más grande es: %d\n", max);
    return 0;
}