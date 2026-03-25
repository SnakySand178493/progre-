#include <stdio.h>

/*
INSTRUCCIONES:
Aprobado si la calificación es >= 60
*/

int main() {
    int calificacion;
    scanf("%d", &calificacion);

    if (calificacion >=60) {
        printf("Aprobado\n");
    } else {
        printf("Reprobado\n");
    }

    return 0;
}
