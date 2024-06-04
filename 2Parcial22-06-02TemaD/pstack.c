#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    /* COMPLETAR */
    struct s_node **array;
    unsigned int size;
    unsigned int max_priority;
};

struct s_node {
    /* COMPLETAR */
    struct s_node *next;
    unsigned int elem;
};

//crea un nuevo nodo para la pila de prioridades.
static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = malloc(sizeof(struct s_node));//reserva mem para el nuevo nodo
    assert(new_node!=NULL);//verifi que se hizo la reserva
    /* COMPLETAR */
    //inciar el contenido del nodo
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

//libera la mem para un nodo cuando ya no es necesario.
static struct s_node * destroy_node(struct s_node *node) {
    /* COMPLETAR */
    if(node != NULL){//verifica que nodo no sea null
        free(node);//si no es null, liberamos la mem del nodo
    }
    return node;
}

//la pila de prio no es null
//cada nodo en la estruc tiene la prio correcta.
static bool invrep(pstack s) {
    /*COMPLETAR*/
    //el array de prio es null entonces el tamaño debe ser 0
    if(s->array == NULL && s->size != 0){
        return false;
    }else
        //el array de prio no es null, entonces el tamaño no debe ser 0 
        if(s->array != NULL && s->size == 0){
            return false;
        }
    return true;
}

//crea una pila de prio vacia para almacenar hasta maxprio inclusive
pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL; //declara un puntero s y lo incia en null
    /* COMPLETAR */
    s = malloc(sizeof(struct s_pstack)); //reserva mem 
    //inicia los campos de s_pstack
    s->array = NULL; //la pila de prio no tiene elem
    s->max_priority = max_priority; //max prio permitida en la pila
    s->size = 0;//la pila de prio no contiene elem

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

//inserta un elem a la pila con su corresp prio
pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    /* COMPLETAR */
    struct s_node *new_node = create_node(e);//crea un nuevo nodo con elem e

    assert(priority <= s->max_priority);// asegura que la prio del nuevo elem no sea may a maxprio
    //si el array es null(la cola esta vacia) se asigna mem para el array q inica todas las pos en null
    if(s->array == NULL){
        s->array = calloc(s->max_priority, sizeof(struct s_node));
        s->array[priority] = new_node;//se asigna el nvo nodo a la pos corresp a la prio del nuevo elem
    }
    /*Si el array ya está inicializado: Si la posición correspondiente a la prioridad está vacía (NULL), 
    se asigna el nuevo nodo a esa posición.
    Si ya hay nodos en esa posición (hay una cola existente para esa prioridad), 
    se recorre la lista enlazada hasta el final y se agrega el nuevo nodo al final de la cola.*/
    else{
        if(s->array[priority] == NULL){
            s->array[priority] = new_node;
        }
        else{
            struct s_node *p = s->array[priority];
            while(p->next != NULL){
                p = p->next;
            }
            p->next = new_node;
        }
    }
    s->size++;

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

//indica si la pila de prio esta vacia
bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    /* COMPLETAR */
    return (s->size == 0);
}

//obtiene el elem con may prio
pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    /* COMPLETAR */
    unsigned int i = 0;
    struct s_node *p = s->array[i];
    while(p == NULL){
        i++;
        p = s->array[i];
    }
    return s->array[i]->elem;
}

//obtiene el valor de la prio del elem con may prio
priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    /* COMPLETAR */
    unsigned int i = 0;
    struct s_node *p = s->array[i];
    while(p == NULL){
        i++;
        p = s->array[i];
    }
    return i;
}

//obtiene el tamaño de la pila de prio
size_t pstack_size(pstack s) {
    assert(invrep(s));
    /* COMPLETAR */
    return s->size;
}

//quita el elem con mayor prio mas recientemente apilado
pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    /* COMPLETAR */
    //busca el elem con prio mas antigua
    unsigned int i = 0;
    struct s_node *p = s->array[i];
    while(p == NULL){
        i++;
        p = s->array[i];
    }
    //eliminacion del nodo encontrado (tiene un solo nodo)
    if(s->array[i]->next == NULL){
        free(s->array[i]);
        s->array[i] = NULL;
    }else{//tiene mas de un nodo
        s->array[i] = s->array[i]->next;
        p->next = NULL;
        free(p);
    }
    //actualizamos la pila de prio
    s->size--;
    if(s->size == 0)s->array = NULL;
    assert(invrep(s));
    return s;
}

//destruye una instancia del tad stack
pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    /* COMPLETAR */
    struct s_node *p = NULL;
    //no hay nodos que destruir
    if(s->array == NULL){
        free(s);
        s = NULL;
    }else{//hay nodos q destruir
        for(unsigned int i = 0; i < s->max_priority; i++){//se recorre cada pos del array y se lib los nodos
        //presentes en cada pila de prio
        if(s->array[i] != NULL){
            while(s->array[i] != NULL){//se usa while par asegurar q todos los nodos de una pila de prio se libe
                p = s->array[i];
                s->array[i] = s->array[i]->next;
                destroy_node(p);

                }
            }
        }
    }
    return s;
}