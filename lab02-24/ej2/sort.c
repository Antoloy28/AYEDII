/*impl top-down del algoritmo de ordenacion rapida*/ 
/*hacer la funcion quick_sort_rec pero sin la imple del partition que ya esta en array_helpers.h*/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
 /* needs implementation */

    /* no implementes partition, ya está implementado en sort_helpers.o
       (no se puede leer, pero en sort_helpers.h vas a encontrar información
        para saber cómo usarlo)
    */
   unsigned int ppiv; //var ppiv que almacena el indice del pivote despues de realizar la partition 
   if (der > izq){ //verf que el segm tenga al menos dos elementos para comparar
     ppiv = partition(a, izq, der); //llama al func partition para hacer la particion del segmento 
     if (ppiv != 0){ // verif q el indice del pivote no sea 0
        quick_sort_rec(a, izq, ppiv-1); //llamada rec para ordenar la parte izq del pivote
     }
     quick_sort_rec(a, ppiv+1, der); //lamada rec para ordenar la parte der del pivote
   }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

