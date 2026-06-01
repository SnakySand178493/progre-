//Imprime piramide de lado
#include <stdio.h>

void main(){
    int n, i=0, j=0;
    printf("Ingresa un número\n");
    scanf("%d", &n);

    for (i=1; i<=n; i++){
        for(j=1; j<=i ; j++)
            printf("%d ", j);
        printf("\n");
    }

    for (i=n-1; i>=1; i--){
        for(j=1; j<=i; j++)
            printf("%d ", j);
        printf("\n");
    }
}