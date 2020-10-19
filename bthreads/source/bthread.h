//
// Created by samuele on 10/5/20.
//

#ifndef BTHREADS_BTHREAD_H
#define BTHREADS_BTHREAD_H



typedef unsigned long int bthread_t;

typedef struct {
} bthread_attr_t;

typedef void *(*bthread_routine) (void *);

int bthread_create(bthread_t *bthread, const bthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

int bthread_join(bthread_t bthread, void **retval);

void bthread_yield();

void bthread_exit(void *retval);



#endif //BTHREADS_BTHREAD_H
