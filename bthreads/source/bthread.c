//
// Created by samuele on 10/7/20.
//

#include <stdlib.h>
#include <stdint.h>
#include "bthread.h"
#include "bthread_private.h"

static __bthread_scheduler_private *__bthread_scheduler_private_pointer=NULL;

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
    __bthread_private *tmp=malloc(sizeof(__bthread_private));
    tmp->tid=*bthread; // cosa identifica e come funziona
    tmp->body=(*start_routine);
    tmp->attr=attr;
    tmp->arg=arg;
    tmp->state=__BTHREAD_READY;
    tmp->stack=NULL;
    //tmp->context=???
    tmp->retval=NULL;
    tqueue_enqueue(bthread_get_scheduler()->queue,tmp);

}

int bthread_join(bthread_t bthread, void **retval)
{
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    scheduler->current_item = scheduler->queue->front;
    save_context((struct __jmp_buf_tag *) scheduler->context); // è giusta sta roba?!
    if (bthread_check_if_zombie(bthread, retval))
        return 0;
    __bthread_private* tp;
    do {
        scheduler->current_item = tqueueNode_at_offset(scheduler->current_item, 1);
        tp = (__bthread_private*) tqueueNode_get_data(scheduler->current_item);
    } while (tp->state != __BTHREAD_READY);
    if (tp->stack) {
        restore_context(tp->context);
    } else {
        tp->stack = (char*) malloc(sizeof(char) * STACK_SIZE); // cosa prendo come STACK_SIZE?
        unsigned long target = tp->stack + STACK_SIZE - 1;
        #if __APPLE__
        // OSX requires 16 bytes aligned stack
            target -= (target % 16);
        #endif
        #if __x86_64__
            asm __volatile__("movq %0, %%rsp" :: "r"((intptr_t) target));
        #else
            asm __volatile__("movl %0, %%esp" :: "r"((intptr_t) target));
        #endif
        bthread_exit(tp->body(tp->arg));
    }
}

void bthread_yield() {
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private* tp = (__bthread_private*) tqueueNode_get_data(scheduler->current_item);
    if (!save_context(tp->context)) {
        __bthread_private* next = (__bthread_private*) tqueueNode_get_data(scheduler->current_item->next);
        restore_context(next->context);
    }
}

void bthread_exit(void *retval) {
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    __bthread_private* tp = (__bthread_private*) tqueueNode_get_data(scheduler->current_item);
    if(retval!=NULL)
        tp->retval=retval;
    tp->state=__BTHREAD_ZOMBIE;
    bthread_yield();
}

__bthread_scheduler_private* bthread_get_scheduler() {
    if(__bthread_scheduler_private_pointer==NULL) {
        __bthread_scheduler_private_pointer=malloc(sizeof(__bthread_scheduler_private));
        __bthread_scheduler_private_pointer->queue=malloc(sizeof(TQueue));
        tqueue_initialize(__bthread_scheduler_private_pointer->queue);
        __bthread_scheduler_private_pointer->current_item=NULL;
        __bthread_scheduler_private_pointer->context=NULL;
        __bthread_scheduler_private_pointer->current_tid=-1;
    }
    return __bthread_scheduler_private_pointer;
}

void bthread_cleanup() {

}

static int bthread_check_if_zombie(bthread_t bthread, void **retval) {
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    struct TQueueNode* tmp = tqueueNode_at_offset(scheduler->current_item, bthread);
    __bthread_private* tp = (__bthread_private*) tqueueNode_get_data(tmp);
    if(tp->state!=__BTHREAD_ZOMBIE)
        return 0;
    else {
        if(retval!=NULL)
            tp->retval=retval;
        free(tp->stack);
        tqueue_pop(tqueue_at_offset(scheduler->queue,bthread));
        return 1;
    }
}

static TQueue *bthread_get_queue_at(bthread_t bthread) { // verificare la correttezza
    volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    TQueue *tmpQueue=tqueue_at_offset(scheduler->queue,bthread);
    if(tqueue_is_empty(tmpQueue)||tmpQueue->front->data==NULL)
        return NULL;
    else return tmpQueue;
}