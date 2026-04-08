#include <stdio.h>
#include <string.h>

int main() {

    char password[15] = "1234";
    char input[15];
    
    do {
        printf("Ingrese la contrasenia: ");
        scanf("%s", input);
        
        if (strcmp(input, password) == 0) {
            printf("Contrasenia correcta. Acceso concedido.\n");
        } else {
            printf("Contrasenia incorrecta. Intente de nuevo.\n");
        }
    } while (strcmp(input, password) != 0);
    
    return 0;
}

