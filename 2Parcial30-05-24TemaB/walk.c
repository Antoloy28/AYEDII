#include <stdio.h>
#include <stdlib.h>
#include "walk.h"
#include <assert.h>


#define STEP_NORTH 0
#define STEP_EAST 1
#define STEP_NORTHEAST 2
#define STEP_UNDEF 3

typedef unsigned int step_t;
typedef unsigned int uint_t;

struct _node_t {
    step_t step;
    struct _node_t *next;
};

typedef struct _node_t *node_t;

struct _walk_t {
    node_t init;
    node_t last;
    uint_t length;
    uint_t width;
    uint_t height;
};

//crea una nueva caminata vacia
walk_t walk_empty(void) {
    // Crear una nueva instancia de caminata
    walk_t new_walk = malloc(sizeof(struct _walk_t));
    if (new_walk == NULL) {
        // Manejar el error de asignación de memoria
        fprintf(stderr, "Error: no se pudo asignar memoria para la caminata\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar los campos de la estructura
    new_walk->init = NULL; // Inicialmente no hay ningún nodo
    new_walk->last = NULL; // Inicialmente no hay ningún nodo
    new_walk->length = 0; // Inicialmente la caminata está vacía 
    new_walk->width = 0; // El ancho de una caminata vacía es 0
    new_walk->height = 0; // La altura de una caminata vacía es 0

    return new_walk;
}

//crea un nuevo nodo
static node_t create_node(void) {
    // Reservar memoria para el nuevo nodo
    node_t new_node = malloc(sizeof(struct _node_t));
    // Verificar si malloc falló
    if (new_node == NULL) {
        // Manejar el error adecuadamente, como mostrar un mensaje de error y finalizar el programa
        fprintf(stderr, "Error: no se pudo asignar memoria para el nuevo nodo\n");
        exit(EXIT_FAILURE);
    }
    // Inicializar el nuevo nodo
    new_node->step = STEP_UNDEF; // Inicializar el paso como indefinido
    new_node->next = NULL; // El nuevo nodo apunta a NULL, ya que será el último nodo
    return new_node;
}

//agrega un nuevo nodo al final de la lista enlazada
static walk_t walk_add(walk_t walk , node_t new_node) {
    // Si la caminata está vacía
    if(walk->init == NULL){
        walk->init = new_node; // El nuevo nodo será el primero
    } else {
        // Conectar el nuevo nodo al final de la caminata
        walk->last->next = new_node;
    }
    walk->last = new_node; // Actualizar el último nodo de la caminata
    walk->length++; // Incrementar la longitud de la caminata
    return walk; // Devolver la caminata actualizada
}

//agrega un paso al norte de la caminata c
walk_t walk_north(walk_t walk) {
    //COMPLETE
    // Crear un nuevo nodo para representar el paso hacia el norte
    node_t new_node = create_node();
    new_node->step = STEP_NORTH; // Especificar que el paso es hacia el norte
    // Utilizar walk_add para agregar el nuevo nodo al final de la caminata
    walk = walk_add(walk, new_node);
    // Incrementar la altura de la caminata
    walk->height++;
    return walk;
}

//CREA UN NUEVO PASO AL ESTE DE LA CAMINATA
walk_t walk_east(walk_t walk) {
    //COMPLETE
    // Crear un nuevo nodo para representar el paso hacia el ESTE
    node_t new_node = create_node();
    new_node->step = STEP_EAST; // Especificar que el paso es hacia el norte
    // Utilizar walk_add para agregar el nuevo nodo al final de la caminata
    walk = walk_add(walk, new_node);
    // Incrementar la altura de la caminata
    walk->height++;
    return walk;
}

//AGREGA UN PASO AL NOROESTE
walk_t walk_northeast(walk_t walk) {
    //COMPLETE
    // Crear un nuevo nodo para representar el paso hacia el noroeste
    node_t new_node = create_node();
    new_node->step = STEP_NORTHEAST; // Especificar que el paso es hacia el norte
    // Utilizar walk_add para agregar el nuevo nodo al final de la caminata
    walk = walk_add(walk, new_node);
    // Incrementar la altura de la caminata
    walk->height++;
    return walk;
}

//calcula la long de una caminata
unsigned int walk_length(walk_t walk) {
    //COMPLETE
    unsigned int length = 0; //inicar la long en 0
    node_t current = walk->init; // inicar desde el primer nodo en la caminata
    //iterar a traves de la caminata mientras haya nodos
    while(current != NULL){
        length++; //incremetnar la long por cada nodo encontrado
        current = current->next;//avanzar al sig nodo
    }
    return length;
}

//calcula la altura de una caminata(son los pasos hacia el norte)
unsigned int walk_height(walk_t walk) {
    //COMPLETE
    unsigned int height = 0; //inciar la altura en 0
    node_t current = walk->init; // iniciar desde el primer nodo en la caminata
    //iterar en la caminata mientras haya nodos
    while(current != NULL){
        if(current->step == STEP_NORTH){
            height++; //incrementar solo si esun paso al norte
        }
        current = current->next; //avanzar al sig nodo
    }
    return height;
}

//calcula el ancho de una caminata(pasos hacia el este o noroeste)
unsigned int walk_width(walk_t walk) {
    //COMPLETE
    unsigned int width = 0; //inciar la altura en 0
    node_t current = walk->init; // iniciar desde el primer nodo en la caminata
    //iterar en la caminata mientras haya nodos
    while(current != NULL){
        if(current->step == STEP_EAST || current->step == STEP_NORTHEAST){
            width++; //incrementar solo si esun paso al este o noroeste
        }
        current = current->next; //avanzar al sig nodo
    }
    return width;
}

//extiende la caminata un cierto num de pasos al este y un cierto num de pasos al norte
walk_t walk_extend(walk_t walk, unsigned int east, unsigned int north) {
    //COMPLETE
    //iterar para agregar un paso al este
    for(unsigned int i = 0; i < east; i++){
        walk = walk_east(walk); //extender un paso al este 
    }
    //iterar para agregar un paso al norte
    for(unsigned int i = 0; i < north; i++){
        walk = walk_north(walk); //extender un paso al norte
    }
    return walk;
}

static char step_to_char (step_t step) {
    char c = '\0';
    switch (step) {
        case STEP_NORTH : c = 'N'; break;
        case STEP_EAST  : c = 'E' ; break;
        case STEP_NORTHEAST : c = 'X' ; break;
        default : c = 'U' ; break;
    }
    return c;
}

void walk_dump(walk_t walk) {
    assert(walk != NULL);
    node_t current = NULL;
    current = walk -> init;
    printf("[");
    while (current != NULL) {
        printf("%c",step_to_char(current->step));
        if(current->next != NULL) {
            printf(" -> ");
        }
        current = current -> next;
    }
    printf("] (L=%u,W=%u,H=%u)\n",walk->length,walk->width,walk->height);
}

//libera la mem asociada a una caminata y sus nodos
walk_t walk_destroy(walk_t walk) {
    //COMPLETE IT!!
    node_t current = walk->init; //inicar desde el primer nodo en la caminata
    //iterar en la caminata mientras haya nodo
    while(current != NULL){
        node_t temp = current; //mantener una referencia al nodo actual
        current = current->next; //avanzar al sig nodo
        free(temp); //liberar la mem del nodo actual
    }
    //reiniciar los atributos de la caminata
    walk->init = NULL;
    walk->last = NULL; 
    walk->length = 0;
    walk->height = 0;
    walk->width = 0;

    return walk;
}

