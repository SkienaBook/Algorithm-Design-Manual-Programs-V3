/*	kruskal.c

	Compute minimum spanning trees of graphs via Kruskal's algorithm.
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
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "set_union.h"

#define MAXINT  100007

typedef struct {
    int x, y;       /* adjacency info */
    int weight;     /* edge weight, if any */
} edge_pair;

/************************************************************/

void to_edge_array(graph *g, edge_pair e[]) {
    int i, m;       /* counters */
    edgenode *p;    /* temporary pointer */

    m = 0;
    for (i = 1; i <= g->nvertices; i++) {
        p = g->edges[i];
        while (p != NULL) {
            if (p->y > i) {
                e[m].x = i;
                e[m].y = p->y;
                e[m].weight = p->weight;
                m = m + 1;
            }
            p = p->next;
        }
    }
}

int weight_compare(const void *x, const void *y) {
    edge_pair *_x = (edge_pair*)x;
    edge_pair *_y = (edge_pair*)y;

    if (_x->weight < _y->weight) {
        return(-1);
    }

    if (_x->weight > _y->weight) {
        return(1);
    }

    return(0);
}

/* [[[ kruskal_cut */
int kruskal(graph *g) {
    int i;                  /* counter */
    union_find s;           /* union-find data structure */
    edge_pair e[MAXV+1];    /* array of edges data structure */
    int weight=0;           /* cost of the minimum spanning tree */

    union_find_init(&s, g->nvertices);

    to_edge_array(g, e);
    qsort(&e,g->nedges, sizeof(edge_pair), &weight_compare);

    for (i = 0; i < (g->nedges); i++) {
        if (!same_component(&s, e[i].x, e[i].y)) {
            printf("edge (%d,%d) in MST\n", e[i].x, e[i].y);
            weight = weight + e[i].weight;
            union_sets(&s, e[i].x, e[i].y);
        }
    }

    return(weight);
}
/* ]]] */

int main(void) {
    graph g;
    int weight;

    read_graph(&g, false);

/*
    print_graph(&g);
*/

    weight = kruskal(&g);

    printf("Out of Kruskal: weight=%d \n",weight);

    return 0;
}
