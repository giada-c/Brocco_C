//
// Created by samuele on 10/5/20.
//

#ifndef BTHREADS_TQUEUE_H
#define BTHREADS_TQUEUE_H



struct TQueueNode;
typedef struct {
    int count;
    struct TQueueNode *front;
    struct TQueueNode *rear;
} TQueue;

/* For the initialization of the queue */
void tqueue_initialize(TQueue *q);

/* Check if the queue is empty */
int tqueue_is_empty(TQueue *q);

/* Adds a new element at the end of the list, returns its position */
unsigned long int tqueue_enqueue(TQueue* q, void* data);

/* Removes and returns the element at the beginning of the list, NULL if the queue is empty */
void* tqueue_pop(TQueue* q);

/* Returns the number of elements in the list */
unsigned long int tqueue_size(TQueue *q);

/* Returns a 'view' on the list starting at (a positive) offset distance,
* NULL if the queue is empty */
TQueue* tqueue_at_offset(TQueue *q, unsigned long int offset);

struct TQueueNode* tqueueNode_at_offset(struct TQueueNode *q, unsigned long int offset);

/* Returns the data of the first node of the given list */
void* tqueue_get_data(TQueue *q);

/* Returns the data of the given node */
void* tqueueNode_get_data(struct TQueueNode *q);

/* Print the queue */
void tqueue_print(TQueue *q);

void tqueue_print_node(struct TQueueNode *q);

#endif //BTHREADS_TQUEUE_H
