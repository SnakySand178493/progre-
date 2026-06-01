//Imprime piramide vacia *tarea
#include <stdio.h>

void main(){
    int n, i = 0, j = 0, k = 0;
    printf("Ingresa un número\n");
    scanf("%d", &n);

    for (i = n; i >= 1; i--){
        for (j = 1; j <= i; j++)
            printf("%d ", j);
        
        for (k=1; k<=(n-i)*4; k++)
                printf(" ");

        for (j = i; j >= 1; j--)
            printf("%d ", j);
        
        printf("\n");    
    }
}