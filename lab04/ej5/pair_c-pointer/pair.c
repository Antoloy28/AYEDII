#include "pair.h"
#include <stdlib.h>
#include <assert.h>

struct s_pair_t { //el struct de pair.h lo puse aca ahora
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
    assert(p!= NULL);
    return p->fst;
}

int pair_second(pair_t p){
    assert(p!= NULL);
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    assert(p!= NULL);
    pair_t q = pair_new(p->snd, p->fst);
    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return NULL;
}