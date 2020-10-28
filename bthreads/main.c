#include <stdio.h>
#include <malloc.h>
#include "source/bthread_private.h"
#include "source/bthread.h"
#include "source/tqueue.h"

void testCoda();

int main() {
    testCoda();
    return 0;
}

void testCoda() {
    TQueue* t;
    t=malloc(sizeof(TQueue));
    tqueue_initialize(t);
    tqueue_print(t);
    printf("Inserito elemento in posizione %d\n",tqueue_enqueue(t,"1"));
    printf("Inserito elemento in posizione %d\n",tqueue_enqueue(t,"2"));
    printf("Inserito elemento in posizione %d\n",tqueue_enqueue(t,"3"));
    printf("Inserito elemento in posizione %d\n",tqueue_enqueue(t,"4"));
    printf("Inserito elemento in posizione %d\n",tqueue_enqueue(t,"5"));
    tqueue_print(t);
    printf("Dimensione della coda: %d\n",tqueue_size(t));
    printf("Rimuovo dalla coda l'elemento con valore: ");
    printf(tqueue_pop(t));
    printf("\n");
    tqueue_print(t);
    printf("Dimensione della coda: %d\n",tqueue_size(t));
    printf("Contenuto del primo elemento della coda: ");
    printf(tqueue_get_data(t));
    printf("\n");
    printf("Contenuto del primo elemento della coda (2): ");
    printf(tqueueNode_get_data(t->front));
    printf("\n");
    TQueue* t2;
    t2=malloc(sizeof(TQueue));
    tqueue_initialize(t2);
    TQueueNode* t3;
    t3=malloc(sizeof(TQueueNode));
    t2=tqueue_at_offset(t,5);
    t3=tqueueNode_at_offset(t->front,5);
    printf("Lista con offest 5: \n");
    tqueue_print(t2);
    printf("Nodo con offest 5: \n");
    tqueue_print_node(t3);
    tqueue_pop(t2);
    printf("Inserimento in coda nulla: \n");
    printf("%d\n",tqueue_enqueue(t2,"1"));
    printf("Contenuto del primo elemento della coda nulla: ");
    printf(tqueue_get_data(t2));
    printf("\n");
    printf("Dimensione della coda nulla: %d\n",tqueue_size(t2));
    t2=tqueue_at_offset(t,2);
    t3=tqueueNode_at_offset(t->front,2);
    printf("Lista con offest 2: \n");
    tqueue_print(t2);
    printf("Nodo con offest 2: \n");
    tqueue_print_node(t3);
    printf("Svuoto seconda lista\n");
    tqueue_pop(t2);
    tqueue_pop(t2);
    tqueue_print(t2);
    tqueue_size(t2);
}
