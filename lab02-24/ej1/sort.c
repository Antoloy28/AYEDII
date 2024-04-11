#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void insert(int a[], unsigned int i) {
    /* needs implementation */
    unsigned int j = i; //indice para recorrer el arr
    while (j > 0 && goes_before(a[j], a[j-1])){ //se ej mientras j sea may q 0 y el elem en la pos a[j] sea menr al elem en la pos a[j-1]
        swap(a,j-1,j); //intercambia los elem en la pos j-1 y j en el arr a
        j--; //decrementa el valor de j en 1 para cont la compar e intercambio de pos del arr
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) { //bucle q itera desde i-1 hasta length -i
        /* needs implementation */
        assert(array_is_sorted(a, i-1)); //verif que el subarr desde el principio hasta la pos i-1 este ord
        insert(a, i);//llama la func insert para insertar el elem en la pos i en su lugar correcto en el subarr desde el principio hasta la pos i-1
    }
    assert(array_is_sorted(a, length)); //verif q el arr este ordenado.
}



/*La palabra clave static en este contexto indica que la función insert solo es visible dentro del 
archivo fuente actual y no se puede acceder desde otros archivos.

void insert(int a[], unsigned int i): Declara una función llamada insert que toma un arreglo a y un 
índice i como argumentos y no devuelve ningún valor (void).*/