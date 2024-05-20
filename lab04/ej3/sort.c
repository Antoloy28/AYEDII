/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    // completar aquí
    return x->rank <= y->rank; //x e y son punteros a la estructura player_t
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void sort(player_t a[], unsigned int length) {
    // completar aquí
    for (unsigned int i = 0; i < length; i++){ //itera sobre todos los elem del arr (i represe el num de pasadas que hemos hecho en el arr)
        for (unsigned int j = 0; j < length - i - 1; j++){//itera sobre los elem restantes del arr(porq el elem mas grande ya esta en su posicion y no debemos volver a cmpararlo)
            if(!goes_before(a[j], a[j+1])){ //compara el elem actual con el sig elem
            //si el elem actual no debe ir antes del siguiente, realizamos un intercambio   
                player_t temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}




