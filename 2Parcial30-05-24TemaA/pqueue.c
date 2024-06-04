#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "character/character.h"
#include "pqueue.h"

/* ============================================================================
STRUCTS!
============================================================================ */

struct s_pqueue {
    unsigned int size; //tamaño de la cola
    struct s_node *front;//puntero q apunta al primer nodo de la cola de prioridad
};

struct s_node {
    Character character;//almacena el caractern del elem
    float priority; //alamecena la prioridad del elem  
    struct s_node *next;//puntero q apunta al sig nodo en la cola de prio
};

/* ============================================================================
INVREP
============================================================================ */

static bool invrep(pqueue q) {
    if (q == NULL) return false; //la cola de prio es null
    /*Verifica si hay inconsistencias entre el tamaño de la cola (size) y el puntero al frente de la cola 
    (front). Por ejemplo, si front es NULL pero size no es cero, o si front no es NULL pero size es cero,
     indica que hay un problema con la representación de la cola.*/
    if ((q->front == NULL && q->size != 0) || (q->front != NULL && q->size == 0)) return false;

    // Verificar que la lista está ordenada por prioridad descendente
    struct s_node *current = q->front;
    while (current != NULL && current->next != NULL) {
        if (current->priority < current->next->priority) return false;
        current = current->next;
    }
    return true;
}

/* ============================================================================
NEW
============================================================================ */

//crea una cola de prio/iniciativa vaci
pqueue pqueue_empty(void) {
    pqueue q = NULL;

    q = malloc(sizeof(struct s_pqueue));
    q->size = 0;
    q->front = NULL;
    assert(invrep(q));

    return q;
}


/* ============================================================================
ENQUEUE
============================================================================ */

//calcula de prio de un personaje
static float calculate_priority(Character character) {
    float priority = 0.0;//incia el valor en 0.0
    if(character_is_alive(character)) { //verif si el perso esta vivo con la funcion
    /*Si el personaje está vivo, se procede a calcular su prioridad basada en sus atributos.
Se comprueba el tipo de personaje utilizando la función character_ctype(character). Dependiendo del tipo de 
personaje, se calcula la prioridad de diferentes maneras:
Si el personaje es del tipo "ágil" (agile), se multiplica la agilidad del personaje por 1.5 y se asigna el 
resultado a la variable priority.
Si el personaje es del tipo "tanque" (tank), se multiplica la agilidad del personaje por 0.8 y se asigna el 
resultado a la variable priority.
Si el personaje no es ni "ágil" ni "tanque", simplemente se asigna la agilidad del personaje a la variable 
priority.*/
        if(character_ctype(character) == agile) priority = character_agility(character) * 1.5;
        else if(character_ctype(character) == tank) priority = character_agility(character) * .8;
        else priority = character_agility(character);
    }

    return priority;
}

static struct s_node *create_node(Character character) {
    struct s_node *new_node = NULL; 
    new_node = malloc(sizeof(struct s_node));//reserva mem
    assert(new_node != NULL);//verif q se asigno bien

    new_node->character = character;
    /*new_node->priority = calculate_priority(character): Se calcula y se asigna la prioridad del personaje 
    utilizando la función calculate_priority y se guarda en el campo priority del nuevo nodo.*/
    new_node->priority = calculate_priority(character);
    new_node->next = NULL; 

    return new_node;
}

//inserta un personaje a la cola calculando su prio
pqueue pqueue_enqueue(pqueue q, Character character) {
    assert(invrep(q));
    struct s_node *new_node = create_node(character); //crea un nuevo nodo para el personaje 

    if(q->front == NULL) {//si la cola esta vacia, el nvo nodo es el primer elem
        q->front = new_node;
    } else {
        //si la cola no esta vacia, se compara la prio del nuevo nodo con la prio del nodo en frente d la cola
        float new_priority = calculate_priority(character);
        if(q->front->priority < new_priority) {
            new_node->next = q->front;
            q->front = new_node;
        } else {
            /*Si la prioridad del nuevo nodo es menor o igual a la del nodo en el frente de la cola, se busca 
            la posición adecuada para insertar el nuevo nodo manteniendo el orden descendente de prioridad en 
            la cola. Se recorre la cola hasta encontrar el nodo cuya prioridad sea menor que la del nuevo nodo 
            o hasta llegar al final de la cola. Entonces, el nuevo nodo se inserta después de ese nodo.*/
            struct s_node *current = q->front;
            while (current->next != NULL && current->next->priority >= new_priority) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }
    q->size++;
    assert(invrep(q));
    return q;
}


/* ============================================================================
IS EMPTY?
============================================================================ */

//indica si la cola de prio esta vacia
bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return (q->size == 0);
}

/* ============================================================================
PEEKS
============================================================================ */

//obtiene el character con mayor prio
Character pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->character;
}

//obtiene el valor de la prio del elem con may prio
float pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->priority;
}

/* ============================================================================
SIZE
============================================================================ */

//obtiene el tam de la cola de prio
unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size = 0;
    size = q->size;

    return size;
}

/* ============================================================================
COPY
============================================================================ */

//crea una copia de la cola de prio q.
pqueue pqueue_copy(pqueue q) {
    assert(invrep(q));
    struct s_pqueue *copy = pqueue_empty();//crea una cola de prio vacia y se asigna a copy
    struct s_node *current = q->front;//se inicia un puntero current q apunta al primer elem de la cola de prio orig

    while (current != NULL) {//se itera sobre la cola de prio orig
    /*se copia el personaje (character) almacenado en el nodo actual utilizando la función character_copy
    (current->character). Esta función devuelve una copia del personaje.*/
        Character character_c = character_copy(current->character);
        /*Se utiliza pqueue_enqueue para agregar la copia del personaje a la cola de prioridad copy. 
        La función pqueue_enqueue se encarga de insertar el personaje en la posición adecuada según su 
        prioridad en la cola de prioridad.*/
        copy = pqueue_enqueue(copy, character_c);
        current = current->next;
    }
    return copy;
}

/* ============================================================================
DESTROY!
============================================================================ */
static struct s_node *destroy_node(struct s_node *node) {
    assert(node != NULL);
    // Assumes character_destroy frees any memory allocated within the character
    character_destroy(node->character);
    free(node);
    return NULL;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    struct s_node *p = q->front;
    q->front = q->front->next;
    destroy_node(p);
    q->size--;

    return q;
}

pqueue pqueue_destroy(pqueue q) {
    struct s_node *p = NULL;
    while(q->front != NULL) {
        p = q->front;
        q->front = q->front->next;
        destroy_node(p);
    }
    free(q);
    q = NULL;

    assert(q == NULL);
    return q;
}