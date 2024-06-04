//STACK CON NODOS
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
//estructura del stack al estilo de nodos del TAD LISTA
struct _s_stack{
    stack_elem peak;
    struct _s_stack *next;
};

//crea una pila vacia
stack stack_empty(){
    return NULL;
}

//inserta un elemento al tope de la pila
stack stack_push(stack s, stack_elem e){
    //k es el puntero al nuevo nodo de la pila 
    stack k = malloc (sizeof(struct _s_stack));//reserva mem para un nuevo nodo en la pila
    k->peak = e;//asigna el valor del nvo elem e al campo peak del nuevo nodo k
    k->next = s;//el campo next del nvo ndoo k al nodo alctual de la pila s
    return k;
}

//remueve el tope de la pila
stack stack_pop(stack s){
    stack k = s; //asigna el puntero de la pila original a k 
    stack p = k->next; //guarda el puntero al sig nodo (nva cima de la pila)
    free(k); // libera mem del nodo superior (tope)
    return p;//devuelve la pila sin el elem superior
}

//obtiene el tamaño de la pila
unsigned int stack_size(stack s){
    unsigned int size = 0u; //incia el tam de la pila en 0
    stack p = s; // puntero auxiliar q apunta a la pila 
    while(p != NULL){ // mientras el puntero no apunte a null
        p = p->next;// avanza al sig nodo de la pila
        ++size; //incremetna
    }
    return size; //devuelve el tam total de la pila
}


//obtiene el tope de la pila, sin remover, solo ap a una pila NO VACIA 
stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->peak;
}


//verifica si la pila esta vacia
bool stack_is_empty(stack s){
    return (s == NULL);
}


/*Crea un arreglo con todos los elementos de la pila. El tope de
la pila debe quedar en el último elemento del arreglo. Es decir,
leyendo el arreglo de derecha a izquierda se obtiene la pila
original. Si la pila está vacía, devuelve NULL. Para crear el
arreglo nuevo usar calloc().*/
stack_elem *stack_to_array(stack s){
    //crea un arr dinam para almacenar los elem de la pila 
    /*Utiliza calloc para asignar memoria para el arreglo dinámico. La cantidad de memoria reservada 
    es igual al tamaño de la pila 
    (obtenido mediante stack_size(s)) multiplicado por el tamaño de un elemento de la pila 
    (sizeof(stack_elem)).*/
    stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));
    stack p = s;//puntero aux para recorrer la pila
    //recorre la pila y llena el arr con los elem de la pila 
    for(unsigned int i = stack_size(s); i > 0u; --i){
        a[i - 1] = p->peak;//almacena el elem superior d la pila en la pos adecuada del arr
        p = p->next; //avanza al sig nodo de la pila
    }
    return a;
}

//libera los nodos de la pila
stack stack_destroy(stack s){
    stack p = s;//puntero auxiliar y lo incia en la pila original 
    while(!stack_is_empty(s)){//mientras la pila no este vacia
        p = stack_pop(p);//elimina el nodo supeoror de la pila y actualiza el puntero auxiliar
    }
    return p;//devuelve la pila vacia 
}


stack load_stack(stack_elem a[], unsigned int length){
    stack ret = stack_empty();
    for(unsigned int i = length; i>0u; --i){
        ret = stack_push(ret, a[i-1]);
    }    
    return ret;
}


