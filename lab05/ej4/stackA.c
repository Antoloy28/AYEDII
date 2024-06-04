//STACK CON ARREGLOS
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

//crea una pila vacia
stack stack_empty(){
    return NULL;
}

//inserta un elem al tope de la pila
stack stack_push(stack s, stack_elem e){
    stack p;
    if(stack_is_empty(s)){ //la pila esta vacia
        p = malloc(sizeof(struct _s_stack));//se reserva mem para la pila 
        p->size = 1; //la pila ahora contiene 1 elem 
        p->elems = calloc(1, sizeof(stack_elem)); //se reserva mem para un elem
        p->capacity = 1;//la capacidad del arreglo es 1
        p->elems[0] = e; // el primer elem de arr es el nvo elem
        //la pila esta llena
    }else if((s->size) == (s->capacity)){ 
        p = s; 
        p->capacity = p->capacity * 2; //se duplica la capac del arr
        p->elems = realloc((p->elems), (p->capacity)* sizeof(stack_elem)); // se redimensiona el arr
        p->size += 1; //se incrementa el tam de la pila 
        p->elems[(p->size)-1] = e; //se agrega un elem al final del arr
    }else{
        //pila tiene espacio disponible 
        p = s;
        p->size += 1; //se incremetna el tam de la pila
        p->elems[p->size-1] = e;//se agrega un elem al final del arr
    }
    return p;
}


//remueve el tope de la pila
stack stack_pop(stack s){
    if(stack_size(s) <= 1){
        free(s->elems); //libera la mem del arreglo de elem
        free(s); //libera la mem de la estructura de la pila
        return NULL;
    }
    s->size -= 1; //decrementa el tamaño de la pila
    return s;
}

//obtiene el tamaño de la pila
unsigned int stack_size(stack s){
    return stack_is_empty(s) ? 0 : s->size;
}

//obtiene el tope de la pila sin remover, solo app a una pila no vacia 
stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elems[s->size-1];//retorna el tope de la pila (el ultimo elem de la pila)
}


//verifica si la pila esta vacia
bool stack_is_empty(stack s){
    return (s == NULL);
}


//crea un arr con todos los elem de la pila, el tope de la pila debe quedar en el ultimo
//elem del arr 
stack_elem *stack_to_array(stack s){
    stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));//asigna mem para un arr q tentra el mismo tamaño q pila
    for(unsigned i = 0; i < stack_size(s); i++){// 
        a[i] = s->elems[i];//copia el elem de la pila en el arr en el mismo orden
    }
    return a;
}

stack stack_destroy(stack s){
    if(stack_is_empty(s)){
        return NULL;
    }
    free(s->elems);
    free(s);
    return NULL;
}
