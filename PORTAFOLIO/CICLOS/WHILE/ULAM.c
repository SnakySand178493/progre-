#include <stdio.h>

void main()
{
    int n, s;
    do
    {
        printf("Ingesa un número entero positivo\n");
        scanf("%d", &n);

    } while (n <= 0);
        s = n;
    while (s > 1)
    {
        if (s % 2 == 0)
            s /= 2;
        else
            s = s * 3 + 1;
        printf("%d, ", s);
    }
    printf("\n");
}