#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    /* COMPLETAR */
    struct s_node **array;
    unsigned int size; 
    unsigned int min_priority;
};

struct s_node {
    /* COMPLETAR */
    unsigned int elem;
    struct s_node *next;

};

//crea un nuevo nodo para la cola de prioridades.
static struct s_node * create_node(pqueue_elem e) {
    // Reservar memoria para el nuevo nodo
    struct s_node* new_node = malloc(sizeof(struct s_node));
    // Verificar que la reserva de memoria fue exitosa
    assert(new_node != NULL);

    // Inicializar el contenido del nodo
    new_node->elem = e;
    new_node->next = NULL;

    // Devolver el puntero al nuevo nodo
    return new_node;
}

//libera la mem para un nodo cuando ya no es necesario.
static struct s_node * destroy_node(struct s_node *node) {
    /* COMPLETAR */
    if(node != NULL){//verif q el nodo no sea null
        free(node);//si el nodo no es null, liberamos la mem del nodo
    }
    return NULL;
}

//la cola de prio no es null
//cada nodo en la estruc tiene la prio correcta.
static bool invrep(pqueue q) {
    /*COMPLETAR*/
    //el array de prio es nulo entonces el tamaño debe ser 0 
    if(q->array == NULL && q->size != 0){
        return false;
        //si el array de prio no es nulo, el tamaño de la cola no de debe ser 0
    }else if(q->array != NULL && q->size == 0){
        return false;
    }
    return true;
}

//crea una cola de prio vacia para almacenar prior <= min_priority
pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = NULL; //declara un puntero q y lo incia en null
    /*COMPLETAR*/
    q = malloc(sizeof(struct s_pqueue));//asigna mem
    //incian los campos de la estruc s_pqueue
    q->array = NULL;//la cola de prio no tiene elem
    q->min_priority = min_priority;//prio min permitida en la cola
    q->size = 0;//la cola de prio no contiene elem

    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

//inserta un elem a la cola con su corresp prio
pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    /*COMPLETAR*/
    struct s_node *new_node = create_node(e);//crea un nuevo nodo con elem e 

    assert(priority <= q->min_priority);//asegura q la prio del nuevo elem no sea may minprio
    //si el array es null(la cola esta vacia) se asign mem para el array q inicia todas las psos en null
    if(q->array == NULL) {
        q->array = calloc(q->min_priority, sizeof(struct s_node));
        q->array[priority] = new_node;//se asigna el nvo nodo a la pos corresp a la prio del nvo elem
    }
    /*Si el array ya está inicializado: Si la posición correspondiente a la prioridad está vacía (NULL), 
    se asigna el nuevo nodo a esa posición.
    Si ya hay nodos en esa posición (hay una cola existente para esa prioridad), 
    se recorre la lista enlazada hasta el final y se agrega el nuevo nodo al final de la cola.*/
    else {
        if(q->array[priority] == NULL) {
            q->array[priority] = new_node;
        }
        else {
            struct s_node *p = q->array[priority];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new_node;
        }
    }
    q->size++;

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;

}

//indica si la cola de prio esta vacia
bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0); 
}

//obtiene el elem con mayor prio
pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    unsigned int i = 0;
    struct s_node *p = q->array[i];
    while(p == NULL){
        i++;
        p = q->array[i];
    }
    return q->array[i]->elem;
}

//obtiene el valor de la prioridad del elem con may prio
priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    unsigned int i = 0;//recorre el array de prio
    struct s_node *p = q->array[i];//p se inicializa el primer elem del array q->array
    //encuentra la primera cola no vaica del array
    //incremta a i hasta encontrar la prime pos en el array q->array q no este vacia p !=null
    while(p == NULL){
        i++;
        p = q->array[i];
    }
    return i;
}

//obtiene el tam de la cola de prio
size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

//quita el elem con may prio mas antiguo de la cola 
pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    /* COMPLETAR */
    //busca el elem con prio mas antigua 
    unsigned int i = 0;
    struct s_node *p = q->array[i];
    while(p == NULL){
        i++;
        p = q->array[i];
    }
    //eliminacion del nodo encontrado(tiene un solo nodo)
    if(q->array[i]->next == NULL){
        (free(q->array[i]));
        q->array[i] = NULL;
        //tiene mas de un nodo
    }else{
        q->array[i] = q->array[i]->next;
        p->next = NULL;
        free(p);
    }
    //actualizacion de la cola de prio 
    q->size--;
    if(q->size == 0)q->array = NULL;
    assert(invrep(q));
    return q;
}

//destruye una instancia del tad cola de prioridades.
pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    /* COMPLETAR*/
    struct s_node *p = NULL; 
    //no hay nodos que destruir
    if(q->array == NULL){
        free(q);
        q = NULL;
    }else{//hay nodos q destruir
        for(unsigned int i = 0; i < q->min_priority; i++){//se recorre cada pos del array y se lib los nodos
        //presentes en cada cola de prio
            if(q->array[i] != NULL){
                while(q->array[i] != NULL){//se usa while para asegurar q todos los nodos de una cola de prio
                //se liberen
                    p = q->array[i];
                    q->array[i] = q->array[i]->next;
                    destroy_node(p);
                }
            }
        }
    }

    return q;
}