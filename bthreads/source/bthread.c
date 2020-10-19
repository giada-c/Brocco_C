//
// Created by samuele on 10/7/20.
//

#include <stdlib.h>
#include <stdint.h>
#include "bthread.h"
#include "bthread_private.h"

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
    __bthread_private *tmp=malloc(sizeof(__bthread_private));
    tmp->tid=*bthread;
    tmp->body=(*start_routine);
    tmp->attr=attr;
    tmp->arg=arg;
    //tmp->state=???
    tmp->stack=NULL;
    //tmp->context=???
    tmp->retval=NULL;
    tqueue_enqueue(bthread_get_scheduler()->queue,tmp);

}

int bthread_join(bthread_t bthread, void **retval)
{
    /*volatile __bthread_scheduler_private* scheduler = bthread_get_scheduler();
    scheduler->current_item = scheduler→queue;
    save_context(scheduler→context);
    if (bthread_check_if_zombie(bthread, retval)) return 0;
    __bthread_private* tp;
    do {
        scheduler->current_item = tqueue_at_offset(scheduler->current_item, 1);
        tp = (__bthread_private*) tqueue_get_data(scheduler->current_item);
    } while (tp->state != __BTHREAD_READY);
    if (tp->stack) {
        restore_context(tp->context);
    } else {
        tp->stack = (char*) malloc(sizeof(char) * STACK_SIZE);
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
    }*/
}

void bthread_yield() {

}

void bthread_exit(void *retval) {

}

static __bthread_scheduler_private *__bthread_scheduler_private_pointer=NULL;

__bthread_scheduler_private* bthread_get_scheduler() {
    if(__bthread_scheduler_private_pointer==NULL) {
        __bthread_scheduler_private_pointer=malloc(sizeof(__bthread_scheduler_private));
        __bthread_scheduler_private_pointer->queue=malloc(sizeof(TQueue));
        tqueue_initialize(__bthread_scheduler_private_pointer->queue);
        //__bthread_scheduler_private_pointer->current_item=NULL;
        //__bthread_scheduler_private_pointer->context=NULL;
        //__bthread_scheduler_private_pointer->current_tid=NULL;
    }
    return __bthread_scheduler_private_pointer;
}

void bthread_cleanup() {

}

static int bthread_check_if_zombie(bthread_t bthread, void **retval) {

}

static TQueue bthread_get_queue_at(bthread_t bthread) {

}