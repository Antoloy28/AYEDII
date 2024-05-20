#include "pair.h"
#include <stdlib.h>
#include <assert.h>

pair_t pair_new(int x, int y){
    pair_t p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
assert(p != NULL);
return p->fst;

}

int pair_second(pair_t p){
    assert(p != NULL);

    return p->snd;
}

pair_t pair_swapped(pair_t p){
/*
 * DESC: Return a NEW pair with the components of p reversed
 * PRE: {p --> (x, y)}
 *  q = pair_swapped(p)
 * POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
 */
assert(p != NULL);
pair_t q = pair_new(p->snd, p->fst);
return q;
}


pair_t pair_destroy(pair_t p){
/*
 * DESC: Free memory if its necesary
 */
free(p);
return NULL;
}