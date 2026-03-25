#include <stdio.h>

/*
INSTRUCCIONES:
- Niño: < 12
- Adolescente: 12 a 17
- Adulto: 18+
*/

int main() {
    int edad;
    scanf("%d", &edad);

    if (edad < 12) {
        printf("Niño\n");
    } else if (edad = 12 && edad<18) {
        printf("Adolescente\n");
    } else {
        printf("Adulto\n");
    }

    return 0;
}
