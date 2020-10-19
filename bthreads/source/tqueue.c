//
// Created by samuele on 10/5/20.
//

#include <stdio.h>
#include <malloc.h>
#include "tqueue.h"
#include "bthread_private.h"

struct TQueueNode;
void tqueue_initialize(TQueue *q) {
    q->count=0;
    q->front=NULL;
    q->rear=NULL;
}

int tqueue_is_empty(TQueue *q) {
    if(q==NULL)
        return 1;
    return (q->front==NULL);
}

unsigned long int tqueue_enqueue(TQueue* q, void* data) {
    if(q==NULL)
        return -1;
    TQueueNode *tmp;
    tmp=malloc(sizeof(TQueueNode));
    tmp->data=data;
    tmp->next=NULL;
    if(!tqueue_is_empty(q)) {
        q->rear->next=tmp;
        q->rear=tmp;
    } else {
        q->front=tmp;
        q->rear=tmp;
    }
    q->count++;
    return q->count;
}

void* tqueue_pop(TQueue* q) {
    if(tqueue_is_empty(q))
        return NULL;
    TQueueNode *tmp;
    void *data=q->front->data;
    tmp=q->front;
    q->front=q->front->next;
    q->count--;
    free(tmp);
    return data;
}

unsigned long int tqueue_size(TQueue *q) {
    if(q==NULL)
        return -1;
    return q->count;
}

TQueue* tqueue_at_offset(TQueue *q, unsigned long int offset) {
    if(tqueue_is_empty(q))
        return NULL;
    if(offset>q->count) // if the offset is bigger than the queue dimension return NULL
        return NULL;
    TQueueNode *tmp;
    tmp=q->front;
    for(int i=0; i<offset; i++) {
        tmp=tmp->next;
    }
    TQueue *tmpqueue;
    tmpqueue=malloc(sizeof(TQueue));
    tqueue_initialize(tmpqueue);
    int cont=0;
    while(tmp!=NULL) {
        tqueue_enqueue(tmpqueue, tmp->data);
        tmp=tmp->next;
        cont++;
    }
    tmpqueue->count=cont;
    return tmpqueue;
}

void* tqueue_get_data(TQueue *q) {
    if(q==NULL)
        return NULL;
    return q->front->data;
}

void tqueue_print(TQueue *q) {
    if(tqueue_is_empty(q)) {
        printf("Lista vuota\n");
    } else {
        TQueueNode *tmp;
        tmp=q->front;
        while(tmp!=NULL) {
            printf(tmp->data);
            printf("\n");
            tmp=tmp->next;
        }
    }
}