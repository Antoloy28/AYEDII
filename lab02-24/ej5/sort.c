/*copie las implementaciones del ejercicio 3 por enunciado*/
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
       unsigned int i, j, ppiv; 
   ppiv = izq;
   i = izq + 1; 
   j = der; 
   while (i <= j){
    if(goes_before (a[i], a[ppiv])){
        i +=1;
    }else if(goes_before (a[ppiv], a[j])){
        j -=1;
    }else if (goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv])){
        swap (a, i, j);
        i +=1;
        j -=1;
    }
   }
   swap (a,ppiv, j);
   ppiv = j;
   return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 3 */
           unsigned int ppiv; //var ppiv que almacena el indice del pivote despues de realizar la partition 
   if (der > izq){ //verf que el segm tenga al menos dos elementos para comparar
     ppiv = partition(a, izq, der); //llama al func partition para hacer la particion del segmento 
     if (ppiv != 0){ // verif q el indice del pivote no sea 0
        quick_sort_rec(a, izq, ppiv-1); //llamada rec para ordenar la parte izq del pivote
     }
     quick_sort_rec(a, ppiv+1, der); //lamada rec para ordenar la parte der del pivote
   }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


