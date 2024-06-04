#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <stdbool.h>

typedef unsigned int pqueue_elem;

// Definición completa de la estructura del nodo
struct s_node {
    pqueue_elem elem;          // el elemento de la cola 
    unsigned int priority;     // la prioridad del elemento
    struct s_node *next;       // puntero al siguiente nodo de la lista
};

// Declaración del tipo de datos para la cola de prioridades
typedef struct s_pqueue * pqueue;

// Definición completa de la estructura de la cola de prioridades
struct s_pqueue {
    struct s_node *front;       // puntero al primer nodo de la cola 
    unsigned int size;         // tamaño de la cola
};
pqueue pqueue_empty(void);
/*
 * DESC: Creates a new instance of pqueue
 *
 * PRE: {true}
 *  q = pqueue_empty();
 * POS: {q --> pqueue && pqueue_is_empty(q)}
 *
 */

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority);
/*
 * DESC: Adds element 'e' into the pqueue 'q' with the given 'priority'
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_enqueue(q, e, priority);
 * POS: {q --> pqueue && !pqueue_is_empty(q)}
 *
 */

bool pqueue_is_empty(pqueue q);
/*
 * DESC: Indicates whether the pqueue 'q' is empty or not
 *
 */

unsigned int pqueue_size(pqueue q);
/*
 * DESC: Return the number of elements inside the pqueue 'q'
 *
 */

pqueue_elem pqueue_peek(pqueue q);
/*
 * DESC: Return the element with the most urgent prioritiy of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  e = pqueue_peek(q);
 * POS: {q --> pqueue}
 */

unsigned int pqueue_peek_priority(pqueue q);
/*
 * DESC: Return the priority that is most urgent from the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  priority = pqueue_peek_priority(q);
 * POS: {q --> pqueue}
 */

pqueue pqueue_dequeue(pqueue q);
/*
 * DESC: Remove the element with the most urgent priority of the pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  q = pqueue_dequeue(q);
 * POS: {q --> pqueue}
 *
 */

pqueue pqueue_destroy(pqueue q);
/*
 * DESC: Destroy instance of pqueue, freeing all memory used by 'q'.
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_destroy(q);
 * POS: {q == NULL}
 *
 */

#endif