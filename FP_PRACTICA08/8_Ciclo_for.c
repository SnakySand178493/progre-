#include <stdio.h>

int main() {
    int num;
    for (scanf("%d", &num); 
    num >= 0; 
    scanf("%d", &num)) {
        printf("%d\n", num);
    }
    return 0;
}