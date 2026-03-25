#include <stdio.h>

/*
INSTRUCCIONES:
A >= 90
B >= 80
C >= 70
F < 70
*/

int main() {
    int cal;
    scanf("%d", &cal);

    if (cal >= 90) {
        printf("A\n");
    } else if (cal >= 80) {
        printf("B\n");
    } else if (cal >= 70) {
        printf("C\n");
    } else {
        printf("F\n");
    }

    return 0;
}
