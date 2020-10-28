//
// Created by samuele on 10/5/20.
//

#ifndef BTHREADS_BTHREAD_PRIVATE_H
#define BTHREADS_BTHREAD_PRIVATE_H

#define save_context(CONTEXT) sigsetjmp(CONTEXT, 1)
#define restore_context(CONTEXT) siglongjmp(CONTEXT, 1)

#include <setjmp.h>
#include <stddef.h>
#include <stdlib.h>
#include "bthread.h"
#include "tqueue.h"

#define STACK_SIZE 1000 // cosa prendo come stack size???

typedef enum { __BTHREAD_READY = 0, __BTHREAD_BLOCKED, __BTHREAD_SLEEPING, __BTHREAD_ZOMBIE} bthread_state;

typedef struct {
    bthread_t tid;
    bthread_routine body;
    void* arg;
    bthread_state state;
    bthread_attr_t *attr;
    char* stack;
    jmp_buf context;
    void* retval;
} __bthread_private;

typedef struct TQueueNode {
    struct TQueueNode* next;
    void* data;
} TQueueNode;

typedef struct {
    TQueue *queue;
    TQueueNode *current_item;
    jmp_buf *context;
    bthread_t current_tid;
} __bthread_scheduler_private;

__bthread_scheduler_private* bthread_get_scheduler();

void bthread_cleanup(); // verificare che alla chiusura del programma i thread siano stati chiusi e gesitit correttamente

static int bthread_check_if_zombie(bthread_t bthread, void **retval);

static TQueue *bthread_get_queue_at(bthread_t bthread);


#endif //BTHREADS_BTHREAD_PRIVATE_H
