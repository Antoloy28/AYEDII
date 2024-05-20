#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

/*se modifico para que muestre la dir de mem de cada campo de la estruct data_t 
para obtener la dir de mem de cada campo use & seguido del nombre del campo
y %p en printf para imprimir la dir de mem en hexa el cual espera un argumento de tipo void 
por lo que se usa (void*) para convertir la direccion de mem de cada campo a este tipo*/
void print_data(data_t d) {
    printf("NOMBRE: %s (Dirección: %p)\n"
           "EDAD  : %d años (Dirección: %p)\n"
           "ALTURA: %d cm (Dirección: %p)\n\n",
           d.name, (void*)&d.name, d.age, (void*)&d.age, d.height, (void*)&d.height);
}


int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name), sizeof(messi.age), sizeof(messi.height), sizeof(messi));

    /*COMPLETAR*/

    return EXIT_SUCCESS;
}

//la suma no coindice con el total por dos bits
//el tamaño de name depende del tamaño maaximo que se le de al arreglo de la estructura data_t.name que tenga en total





