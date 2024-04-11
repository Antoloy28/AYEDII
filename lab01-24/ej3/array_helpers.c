//aca van las implementaciones de las func del ej1 y con los respectivos include
#include "array_helpers.h"              
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    //your code here!!!
    FILE *archivo = fopen(filepath, "r"); //abre un arch filepath en modo lectura 'r'
    unsigned int length;
    fscanf(archivo, "%u", &length); //lee un num sin sign y lo almacena en la var length
    assert(length <= max_size); //verif que el array legth no exceda el max permitido max_size
    for(unsigned int i = 0; i < length; i++){ //recorre cada elem del array
        fscanf(archivo, "%i", &array[i]);//lee un entero desde el arch y lo amacena en el elem correp del array
        if(feof(archivo)){ //verif si se alcanzo el final del arch
            printf("ERROR!!!\n");
            exit(EXIT_FAILURE);

        }
    }
    fclose(archivo);
    return length;
}

void array_dump(int a[], unsigned int length) { //imprime el array, con los corchetes y separado
    //your code here!!!
    if(!length == 0u){ //verif q length no sea igual a 0 
        printf("[");
        for(unsigned int i = 0; i < length-1u;i++){ //empieza la iteracion hasta el ultimo elem
        printf("%i, ", a[i]);// se imprime cada elem, seguido de una coma

    }
    printf("%i]\n", a[length-1u]);
    }

}