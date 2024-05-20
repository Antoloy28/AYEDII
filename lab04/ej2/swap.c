#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int main (){
    int x = 6;
    int y = 4;
    printf("El valor de x es %d y el de y es %d\n", x,y);
    swap(&x, &y);
    printf("El nuevo valor de x luego del swap es %d y el de y es %d\n",x,y);
    return 0;
}