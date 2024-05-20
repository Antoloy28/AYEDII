#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    // Completar aquí
    if(x >= 0){
        *y = x;
    }else{
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---
    // Completar aquí
    absolute(a, &res);
    printf("El valor es %d\n", res);
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/* Para pensar:
● ¿El parámetro int *y de absolute() es de tipo in, de tipo out o de tipo in/out? 
RTA: es de tipo out, se usa para devolver el valor calculado dentro de la funcion
● ¿Qué tipo de parámetros tiene disponibles C para sus funciones?
○ Parámetros in
○ Parámetros out
○ Parámetros in/out
RTA: C tiene los parametros de in y in/out*/




