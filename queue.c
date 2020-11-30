/*    queue.c

    Implementation of a FIFO queue abstract data type.
*/

/* Copyright 2003-2020 by Steven S. Skiena; all rights reserved.
Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

These programs appear in my books:

"The Algorithm Design Manual" by Steven Skiena, second edition, Springer,
London 2008.  See out website www.algorist.com for additional information
or https://www.amazon.com/exec/obidos/ASIN/1848000693/thealgorith01-20

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.
See our website www.programming-challenges.com for additional information,
or https://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/



#include <stdio.h>
#include <stdbool.h>

#include "queue.h"

void init_queue(queue *q) {
    q->first = 0;
    q->last = QUEUESIZE - 1;
    q->count = 0;
}

void enqueue(queue *q, item_type x) {
    if (q->count >= QUEUESIZE) {
        printf("Warning: queue overflow enqueue x=%d\n", x);
    } else {
        q->last = (q->last + 1) % QUEUESIZE;
        q->q[q->last] = x;    
        q->count = q->count + 1;
    }
}

item_type dequeue(queue *q) {
    item_type x;

    if (q->count <= 0) printf("Warning: empty queue dequeue.\n");

    x = q->q[q->first];
    q->first = (q->first + 1) % QUEUESIZE;
    q->count = q->count - 1;

    return(x);
}

item_type headq(queue *q) {
    return(q->q[q->first]);
}

int empty_queue(queue *q) {
    if (q->count <= 0) {
        return (true);
    }
    return (false);
}

void print_queue(queue *q) {
    int i;

    i = q->first; 
        
    while (i != q->last) {
        printf("%d ", q->q[i]);
        i = (i + 1) % QUEUESIZE;
    }

    printf("%2d ", q->q[i]);
    printf("\n");
}
