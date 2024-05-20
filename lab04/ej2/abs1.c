#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    // Completar aqui
    if(x >= 0){
        y = x;
    }else{
        y = -x;
    }
}

int main(void) {
    int a = -10;
    int res = 0;
    // Completar aquí
    absolute(a, res);
    printf("El valor es %d\n", res);
 
    return EXIT_SUCCESS;
}

