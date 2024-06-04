//copie y peque el queue del eje a y implem la func disscard
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

struct s_queue {
    /*COMPLETAR*/
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q=NULL; //puntero que se inicia en null
    /* COMPLETAR */
    q = malloc(sizeof(struct s_queue));//asigna mem para la estruc y q apunta a esta estruc de mem
    //incializa de los campos de la estruc queue
    q->size = 0;//incia el tam de la cola en 0
    q->first = NULL; //incia el puntero al 1 elem de la cola a null
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e); //se crea un nvo nodo q contiene al elem e 
    if (q->first==NULL) { //indica q la cola esta vacia 
        q->first = new_node;//el nuevo nodo newnode se convierte en el primer nodo de la lista
    } else {
        /* COMPLETAR */
        struct s_node *p = q->first;//si la cola no esta vacia se recorre desde el primer nodo 
        while(p->next != NULL){//hsta encontrar el ultimo ndoo 
            p = p->next;
        }
        p->next = new_node;//se enlaza el nuevo ndoo newnode al final d la cola
    }
    q->size++; //increm el tamaño de la cola
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0; //almacena el tamaño de la cola
    /*COMPLETAR*/
    size = q->size;//se asigna a size el valor del tamaño de la cola
    return size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}

queue queue_disscard(queue q, unsigned int n){
    assert(invrep(q) && n < queue_size(q));

    if(n == 0){//se elimina el primer elem de la cola 
        queue_dequeue(q);
    }else{
        struct s_node *p = q->first;//se inicia un punt p al primer nodo de la cola 
        for(unsigned int i = 0; i < n-1; i++){//desplazam de p hasta el anterior nodo a eliminar 
            p = p->next;
        }

        struct s_node *s = p->next;//se inicia un punt s al nodo q sea desea eliminar 
        p->next = p->next->next;//el puntero next del nodo p se reasigna para apuntar al nodo sig s, elimando s de la lista
        free(s);
    }
    return q;
}


void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}