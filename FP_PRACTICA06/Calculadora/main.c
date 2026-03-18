#include <stdio.h>
int main() {
    
    int a,b,c;
    float f,g,h;
    char op,op2;

    printf("Seleccione una opción:\n");
    printf("1. operaciones con enteros\n");
    printf("2. operaciones con reales\n");
    scanf("%c",&op);

    printf("Seleccione una opcion de operacion:\n");
    printf("1. suma\n");
    printf("2. resta\n");
    printf("3. multiplicacion\n");
    printf("4. division\n");
    printf("5. pmodulo\n");

    scanf(" %c",&op2);
    if(op=='1'){
        printf("Ingrese el primer numero entero: ");
        scanf("%d",&a);
        printf("Ingrese el segundo numero entero: ");
        scanf("%d",&b);

        switch(op2){
            case '1':
                c=a+b;
                printf("La suma es: %d",c);
                break;
            case '2':
                c=a-b;
                printf("La resta es: %d",c);
                break;
            case '3':
                c=a*b;
                printf("La multiplicacion es: %d",c);
                break;
            case '4':
                if(b!=0){
                    c=a/b;
                    printf("La division es: %d",c);
                }else{
                    printf("Error: division por cero");
                }
                break;
            case '5':
                if(b!=0){
                    c=a%b;
                    printf("El modulo es: %d",c);
                }else{
                    printf("Error: division por cero");
                }
                break;
            default:
                printf("Opcion no valida");
     }   }
}
