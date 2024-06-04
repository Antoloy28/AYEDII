#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    /*COMPLETAR*/
    struct s_node *top; //puntero al primer elem de la pila
    unsigned int size; // tamaño de la pila
};

struct s_node {
    /* COMPLETAR */
    pstack_elem elem; // el elemento de la pila
    priority_t priority; //prioridad del elemento
    struct s_node *next; //puntero al sig nodo de la pila
};

//crea un nuevo nodo con el elem y la prioridad dados
static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node)); //asignar mem para el nuevo nodo
    // Completar
    assert(new_node != NULL);//verif que la asig fue exitosa
    new_node->elem = e; //asignar el elem
    new_node->priority = priority;// asignar la prioridad
    new_node->next = NULL; //inciar el puntero al sig nodo como null
    return new_node;
}
//libera la mem asignada a un nodo
static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    /*COMPLETAR*/
    free(node); //liberar la mem del nodo
    node = NULL; // ajustar el puntero a null
    assert(node == NULL);
    return node;
}

//deber ver que no haya nodos nulos en la pila y que la pila este ordenada por prioridad no decreciente 
static bool invrep(pstack s) {
    /*COMPLETAR*/
    if (s == NULL){//si la pila es falsa retornamos null
        return false;
    }
    struct s_node *current = s->top;//inciamos null que apunta al tope de la pila
    while(current != NULL && current->next != NULL){//iteramos en la pila mientras no sea null
        if(current->priority < current->next->priority){ //si encontramos un nodo cuya prior es menor q la prio
        //del sig nodo retorna flase. xq viola la invariante
            return false;
        }
        current = current->next;//movemos el puntero al sig nodo
    }
    return true;
}

//crea una pila de prioridades vacia
pstack pstack_empty(void) {
    pstack s = malloc(sizeof(struct s_pstack)); //reservamos mem para la pila
    assert(s != NULL);//verif q la asig fue exitosa
    s->top = NULL; //inciar el tope como null
    s->size = 0; //inicia el tamaño en 0
    /*COMPLETAR*/
    return s;
}

//inserta un elem en la pila con su prioridad correspondiente
pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));//verif q la pila cumple con la invrep
    struct s_node *new_node = create_node(e, priority);//crea un nuevo nodo
    /*COMPLETAR*/
    //insertar el nuevo nodo en la pos correcta
    if(s->top == NULL || priority >= s->top->priority){
        new_node->next = s->top;
        s->top = new_node;
    }else{
        struct s_node *current = s->top;
        while(current->next != NULL && current->next->priority > priority){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    s->size++;//incrementar el tamaño d la pila
    assert(invrep(s));
    return s;
}

//indica si la pila de prioridades esta vacia
bool pstack_is_empty(pstack s) {
    /*COMPLETAR*/
    //verif si la pila de prio esta vacia
    assert(s != NULL);//asegura q la pila no es null
    return (s->top == NULL);
}

//obtiene el elem con mayor prioridad
pstack_elem pstack_top(pstack s) {
    assert(s != NULL);//verif q la pila no sea null
    assert(s->top != NULL); //verif que la pila no este vacia
    return s->top->elem;//devuelve el elem del tope de la pila
}

//obtiene el valor de la prior del elem con mayor prior
priority_t pstack_top_priority(pstack s) {
    /*COMPLETAR*/
    assert(s != NULL); //verif q la pila no sea null
    assert(s->top != NULL); //verif que la pila no este vacia
    return s->top->priority;//devuelve el valor del elem con mayor priori
}

//obtiene el tam de la pila de prio (no hace falta que sea constante)
unsigned int pstack_size(pstack s) {
    assert(invrep(s));//verif q se cumpla la invrep
    unsigned int size=0;//cuenta los elem de la pila
    /*COMPLETAR*/
    struct s_node *current = s->top;//current recorre la pila desde el tope s->top
    while(current != NULL){//continua mientras current no sea null
        size++;//incrementamos size para cada nodo encontrado
        current = current->next;//current avanza al sig nodo 
    }
    return size;
}

//quita un elem con mayor prior mas recientemente apilado
pstack pstack_pop(pstack s) {
    /*COMPLETAR*/
    assert(invrep(s));
    if(s->top != NULL){
        struct s_node *node_to_remove = s->top; //alamcena el nodo a eliminar
        s->top = s->top->next; //actualiza el tope de la pila al sig nodo
        s->size--;//decrem el tam de la pila
        destroy_node(node_to_remove);//libera la mem del nodo eliminado
    }
    assert(invrep(s));
    return s;
}

//destruye una instancia del tad pstack
pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    /*COMPLETAR*/
    while(s->top != NULL){
        struct s_node *node_to_remove = s->top; // almacena el nodo a elim
        s->top = s->top->next; //actualiza el tope de la pila al sig nodo
        destroy_node(node_to_remove);//libe la mem del nodo eliminado
    }
    free(s);//libe la mem de la estruc principal de la pila
    s = NULL;//asegura q el puntero de la pila sea null

    assert(s == NULL);//verif q el puntero d la pila sea null
    return s;
}