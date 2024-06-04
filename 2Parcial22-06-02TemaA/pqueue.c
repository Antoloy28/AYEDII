#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

//struct s_pqueue {
    /* COMPLETAR */
    //struct s_node front; // puntero al primer nodo de la cola 
    //unsigned int size; // tamaño de la cola
//};

//struct s_node {
    /*COMPLETAR*/
  //  pqueue_elem elem; // el elemento de la cola 
   // unsigned int priority; //la prioridad del elemento
   // struct s_node *next; //puntero al siguiente nodo de la lista
//};

//Crea un nuevo nodo para la cola de prioridades, cada nodo tiene un elem y una prior y apunta al sig nodo
static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node)); //declara un puntero newnode y asigna mem
    // completar 
    assert(new_node!=NULL);
    /* COMPLETAR*/
    //asignamos el elem y la prioridad al nuevo nodo
    new_node->elem = e;
    new_node->priority = priority;
    //incio el puntero al sig nodo como null
    new_node->next = NULL;
    return new_node;
}

//libera mem asignada a un nodo cuando ya no la necesita 
static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL); //verif que el nodo no sea null
    /*COMPLETAR*/
    free(node); //libera la mem del nodo 
    node = NULL; //austamos el puntero del nodo a null
    assert(node == NULL);//verif q el nodo sea null
    return node;
}


static bool invrep(pqueue q) {
    /*COMPLETAR*/
    //verificar que la cola no es nula
    if(q == NULL){
        return false;
    }
    //verif q los nodos estan en cola de prioridad no decreciente
    struct s_node *current = q->front;
    while (current != NULL && current->next != NULL) { //para cada par de nodo consecutivo
    if (current->priority > current->next->priority) { //verif que la prior del nodo actual nosea mayor q la sel dig nodo
        return false;
    }
    current = current->next;
}
    return true;
}

// crea una cola de prioridades vacia
pqueue pqueue_empty(void) {
    /*COMPLETAR*/
    // Asignamos memoria para la nueva cola de prioridades
    pqueue q = malloc(sizeof(struct s_pqueue));
    // Verificamos que la asignación de memoria fue exitosa
    assert(q != NULL);

    // Inicializamos los campos de la estructura
    q->front = NULL; // La cola está vacía, por lo tanto el primer nodo es NULL
    q->size = 0;     // El tamaño de la cola es 0

    // Retornamos la nueva cola de prioridades
    return q;
}

//inserta un elem a la cola con su correspondiente prioridad
pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q)); // Verificar la invariante de la cola de prioridades

    // Crear un nuevo nodo con el elemento y la prioridad proporcionados
    struct s_node *new_node = create_node(e, priority);

    // Si la cola está vacía o la prioridad del nuevo nodo es menor que la del primer nodo
    if (q->front == NULL || priority < q->front->priority) {
        new_node->next = q->front; // El nuevo nodo se convierte en el primer nodo
        q->front = new_node;
    } else {
        // Buscar la posición correcta para insertar el nuevo nodo
        struct s_node *current = q->front;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        // Insertar el nuevo nodo después del nodo actual
        new_node->next = current->next;
        current->next = new_node;
    }

    q->size++; // Incrementar el tamaño de la cola
    assert(invrep(q)); // Verificar nuevamente la invariante después de la inserción

    return q; // Devolver la cola de prioridades actualizada
}

//indica si la cola de prioridades esta vacia
bool pqueue_is_empty(pqueue q) {
    /*COMPLETAR*/
    //verif si q->front es null
    if(q->front == NULL){
        return true;//la cola esta vacia
    }else{
        return false;//la cola no esta vacia
    }

    return true;
}

//obtiene el elemento con mayor prioridad
pqueue_elem pqueue_peek(pqueue q) {
    /*COMPLETAR*/
    //verif si la cola esta vacia
    if(q->front == NULL){
        return 0;//la cola esta vacia no hay elem para devolver
    }else{
        return q->front->elem; //devolver el elem del primer nodo de la cola 
    }
}

//obtiene el valor de la prioridad del elem con mayor prioridad
unsigned int pqueue_peek_priority(pqueue q) {
    /*COMPLETAR*/
    //vrif si la cola esta vacia
    if(q->front == NULL){
        return 0;
    }else{
        return q->front->priority;
    }
}

//obtiene el tamaño de la cola de prioridades
unsigned int pqueue_size(pqueue q) {
   // assert(invrep(q));
    /*COMPLETAR*/
    return q->size;
}

//quita el elem con mayor prior mas antiguo de la cola
pqueue pqueue_dequeue(pqueue q) {
    /*COMPLETAR*/
    // Verificar si la cola está vacía
    if (q->front == NULL) {
        return q; // La cola está vacía, devolver la cola sin cambios
    }
    // Guardar el nodo del primer elemento
    struct s_node *remove_node = q->front;
    // Actualizar el puntero al primer nodo para que apunte al siguiente nodo
    q->front = q->front->next;
    // Decrementar el tamaño de la cola
    q->size--;
    // Liberar la memoria del nodo eliminado utilizando destroy_node
    destroy_node(remove_node);
    return q;
}

//destruye una instancia del TAD cola de prior
pqueue pqueue_destroy(pqueue q) {
   assert(invrep(q));
    /*COMPLETAR*/
    if(q->front == NULL){
        //si la cola esta vacia liber la mem de la estruct y devolver null
        free(q); 
        return NULL;
        }
        //recorrer todos los nodos de la cola y liberar la mem asociada a cada uno de ellos
        struct s_node *current = q->front;
        while(current != NULL){
            struct s_node *next = current->next; //guardar el puntero al sig nodo
            free(current);//liberar la mem del nodo actual
            current = next;
        }
        free(q); //liberar la mem de la estruct principal de la cola
    return NULL;
}