#include <stdio.h>

/*
INSTRUCCIONES:
Completa:
- switch
- operaciones
- validación de división por cero
*/

int main() {
    int a, b, op;
    scanf("%d %d", &a, &b);

    printf("1.Suma 2.Resta 3.Multiplicacion 4.Division\n");
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("%d\n",a +b);
            break;
        case 2:
            printf("%d\n", a - b);
            break;
        case 3:
            printf("%d\n", a * b);
            break;
        case 4:
            if (a==0 && b==0) {
                printf("Error: division por cero\n");
            } else {
                printf("%d\n", a/b);
            }
            break;
    }

    return 0;
}
