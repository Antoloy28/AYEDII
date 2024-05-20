#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
/* Needs implementation.*/
counter c = malloc(sizeof(struct _counter));
c->count = 0;
return c;
}

void counter_inc(counter c) {
/*  Needs implementation.*/
    c->count += 1;
}

bool counter_is_init(counter c) {
/*  Needs implementation*/
    return c->count == 0;
}

void counter_dec(counter c) {
/*Needs implementation.*/
    assert(!counter_is_init(c));
    c->count -=1;
}

counter counter_copy(counter c) {
/*Needs implementation.*/
    counter c2 = malloc(sizeof(struct _counter));
    c2->count = c->count;
    return c2;
}

void counter_destroy(counter c) {
/*Needs implementation.*/
free(c);
}
