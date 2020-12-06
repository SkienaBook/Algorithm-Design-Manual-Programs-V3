/*    TSP priority_queue.c

    Implementation of a heap / priority queue abstract data type,
    adjusted for complete records with key and data fields.
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

#include "tsp-pq.h"

/* [[[ tsp_pq_init_cut */
void pq_init(priority_queue *q) {
    q->n = 0;
}
/* ]]] */

/* [[[ tsp_pq_parent_cut */
int pq_parent(int n) {
    if (n == 1) {
        return(-1);
    }
    return((int) n/2);     /* implicitly take floor(n/2) */
}
/* ]]] */

/* [[[ tsp_pq_young_child */
int pq_young_child(int n) {
    return(2 * n);
}
/* ]]] */

void pq_swap(priority_queue *q, int i, int j) {
    tsp_solution temp;    /* placeholder */

    temp = q->q[i];
    q->q[i] = q->q[j];
    q->q[j] = temp;
}

/* [[[ tsp_bubble_up_cut */
void bubble_up(priority_queue *q, int p) {
    if (pq_parent(p) == -1) {
        return;    /* at root of heap, no parent */
    }

    if (q->q[pq_parent(p)].cost  > q->q[p].cost ) {
        pq_swap(q, p, pq_parent(p));
        bubble_up(q, pq_parent(p));
    }
}
/* ]]] */

/* [[[ tsp_bubble_down_cut */
void bubble_down(priority_queue *q, int p) {
    int c;          /* child index */
    int i;          /* counter */
    int min_index;  /* index of lightest child */

    c = pq_young_child(p);
    min_index = p;

    for (i = 0; i <= 1; i++) { 
        if ((c + i) <= q->n) {
            if (q->q[min_index].cost > q->q[c + i].cost) {
                min_index = c + i;
            }
        }
    }

    if (min_index != p) {
        pq_swap(q, p, min_index);
        bubble_down(q, min_index);
    }
}
/* ]]] */

/* [[[ tsp_pq_insert_cut */
void pq_insert(priority_queue *q, tsp_solution *x) {
    if (q->n >= PQ_SIZE) {
        printf("Warning: priority queue overflow insert x=%7.1f\n", x->cost);
    } else {
        q->n = (q->n) + 1;
        q->q[q->n] = *x;
        bubble_up(q, q->n);
    }
}
/* ]]] */

/* [[[ tsp_extract_min */
tsp_solution extract_min(priority_queue *q) {
    tsp_solution min;    /* minimum value */

    if (q->n <= 0) printf("Warning: empty priority queue.\n");

    min = q->q[1];

    q->q[1] = q->q[q->n];
    q->n = q->n - 1;
    bubble_down(q, 1);

    return(min);
}
/* ]]] */

tsp_solution top_pq(priority_queue *q) {
    if (q->n <= 0) {
        printf("Warning: empty priority queue.\n");
    }

    return(q->q[1]);
}


int empty_pq(priority_queue *q) {
    return (q->n <= 0);
}

void print_pq(priority_queue *q) {
    int i;    /* counter */

    for (i = 1; i <= q->n; i++) {
        printf("%7.1f ", q->q[i].cost);
    }

    printf("\n");
}

/* [[[ tsp_make_heap2_cut */
void make_heap_fast(priority_queue *q, tsp_solution s[], int n) {
    int i;    /* counter */

    q->n = n;
    for (i = 0; i < n; i++) {
        q->q[i + 1] = s[i];
    }

    for (i = q->n/2; i >= 1; i--) {
         bubble_down(q, i);
    }
}
/* ]]] */

/* [[[ tsp_make_heap_cut */
void make_heap(priority_queue *q, tsp_solution s[], int n) {
    int i;    /* counter */

    pq_init(q);
    for (i = 0; i < n; i++) {
        pq_insert(q, &s[i]);
    }
}
/* ]]] */

/* [[[ tsp_heap_compare_cut */
int heap_compare(priority_queue *q, int i, int count, int x) {
    if ((count <= 0) || (i > q->n)) {
        return(count);
    }

    if (q->q[i].cost < x) {
        count = heap_compare(q, pq_young_child(i), count-1, x);
        count = heap_compare(q, pq_young_child(i)+1, count, x);
    }

    return(count);
}
/* ]]] */
