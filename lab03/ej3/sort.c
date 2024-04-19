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
    return x.rank <= y.rank; //mofifique esta linea
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

//HAGO FUNCION SWAP
void swap(player_t a[], int x, int y){
    player_t z = a[x];
    a[x] = a[y];
    a[y] = z;
}

//hago func partition
static unsigned int partition(player_t a[], unsigned int izq, unsigned int der){

        unsigned int i, j, ppiv;
        ppiv = izq;
        i = izq +1;
        j = der;
        while(i <= j){
            if(goes_before(a[i], a[ppiv])){
                i +=1;
            }else if(goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv])){
                swap(a,i,j);
                i+=1;
                j-=1;
            }
        }
        swap(a,ppiv,j);
        ppiv=j;
        return ppiv;

}

//funcion qe agregue yo 
static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    
    unsigned int ppiv;
    if (der > izq){
        ppiv = partition(a, izq, der);
        if(ppiv!=0){
            quick_sort_rec(a, izq, ppiv-1);
        }
        quick_sort_rec(a, ppiv+1, der);
    }
}

//funcion que hice tmb yo
void quick_sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}

void sort(player_t a[], unsigned int length){
    //completar aqui 
    quick_sort(a, length);
}

