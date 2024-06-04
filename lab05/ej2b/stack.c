//AHORA EL STACK DEBE SER DE ORDEN CONSTANTE el stack_size
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

//estructura
struct _s_stack{
    stack_elem peak;
    unsigned int height;
    struct _s_stack *next;
};


stack stack_empty(){
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack k = malloc(sizeof(struct _s_stack));//se reserva mem para un nvo nodo en la pila
    k->peak = e; // se asigna el valor del nuevo elem a la cima dr la pila
    k->next = s;//el nvo nodo apunta al anterior nodo superor de la pila 
    k->height = stack_size(s)+1; //se actualiza la altura d la pila con la nueva altura
    return k;
}

stack stack_pop(stack s){
    stack k = s;
    stack p = k->next;
    free(k);
    return p;
}

unsigned int stack_size(stack s){
    if (stack_is_empty(s)){
        return 0;//si la pila esta vacia su tamaño es 0
        }
    return s->height;//si la pila no esta vacia, devuelve la altura de la pila
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->peak;    
}

bool stack_is_empty(stack s){
    return (s == NULL);    
}

stack_elem *stack_to_array(stack s){
    if (stack_is_empty(s)){return NULL;}
    stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));
    stack p = s;
    for (unsigned int i = stack_size(s); i>0u; --i){
        a[i-1] = p->peak;
        p = p->next;
        }
    return a;
}

stack stack_destroy(stack s){
    stack p = s;
    while (!stack_is_empty(p)){
        p = stack_pop(p);
        }
    return p;
}

stack load_stack(stack_elem a[], unsigned int length){
    stack ret = stack_empty();
    for(unsigned int i = length; i>0u; --i){
        ret = stack_push(ret, a[i-1]);
    }    
    return ret;
}