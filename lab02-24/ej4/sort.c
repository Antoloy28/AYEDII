/*copie todos los algoritmos de ordenacion de los ejercicis anteriores por enunciado*/
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}


static void insert(int a[], unsigned int i) {
    /* copiá acá la implementación que hiciste en el ejercicio 1 */
        unsigned int j = i; //indice para recorrer el arr
    while (j > 0 && goes_before(a[j], a[j-1])){ //se ej mientras j sea may q 0 y el elem en la pos a[j] sea menr al elem en la pos a[j-1]
        swap(a,j-1,j); //intercambia los elem en la pos j-1 y j en el arr a
        j--; //decrementa el valor de j en 1 para cont la compar e intercambio de pos del arr
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        insert(a, i);
    }
}


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
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

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    /* copiá acá la implementación que hiciste en el ejercicio 2 */
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
