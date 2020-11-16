/*	graph.c         

	A generic adjacency list graph data type.
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

#include "queue.h"
#include "graph.h"

/* [[[ init_graph_c */
void initialize_graph(graph *g, bool directed) {
    int i;    /* counter */

    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (i = 1; i <= MAXV; i++) {
        g->degree[i] = 0;
    }

    for (i = 1; i <= MAXV; i++) {
        g->edges[i] = NULL;
    }
}
/* ]]] */

/* [[[ insert_edge_cut */
void insert_edge(graph *g, int x, int y, bool directed) {
    edgenode *p;        /* temporary pointer */

    p = malloc(sizeof(edgenode));    /* allocate edgenode storage */

    p->weight = 0;
    p->y = y;
    p->next = g->edges[x];

    g->edges[x] = p;    /* insert at head of list */

    g->degree[x]++;

    if (!directed) {
        insert_edge(g, y, x, true);
    } else {
        g->nedges++;
    }
}
/* ]]] */

/* [[[ read_graph_cut */
void read_graph(graph *g, bool directed) {
    int i;              /* counter */
    int m;              /* number of edges */
    int x, y;           /* vertices in edge (x,y) */

    initialize_graph(g, directed);

    scanf("%d %d", &(g->nvertices), &m);

    for (i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        insert_edge(g, x, y, directed);
    }
}
/* ]]] */

void delete_edge(graph *g, int x, int y, bool directed) {
    edgenode *p, *p_back; /* temporary pointers */

    p = g->edges[x];
    p_back = NULL;

    while (p != NULL) {
        if (p->y == y) {
            g->degree[x]--;
            if (p_back != NULL) {
                p_back->next = p->next;
            } else {
                g->edges[x] = p->next;
            }
            free(p);
            if (!directed) {
                delete_edge(g, y, x, true);
            } else {
                g->nedges--;
            }
            return;
        } else {
            p = p->next;
        }
    }
    printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

/* [[[ print_graph_cut */
void print_graph(graph *g) {
    int i;        /* counter */
    edgenode *p;  /* temporary pointer */

    for (i = 1; i <= g->nvertices; i++) {
        printf("%d: ", i);
        p = g->edges[i];
        while (p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}
/* ]]] */

/* [[[ graph_transpose_cut */
graph *transpose(graph *g) {
    graph *gt;    /* transpose of graph g */
    int x;        /* counter */
    edgenode *p;  /* temporary pointer */

    gt = (graph *) malloc(sizeof(graph));
    initialize_graph(gt, true);       /* initialize directed graph */
    gt->nvertices = g->nvertices;

    for (x = 1; x <= g->nvertices; x++) {
        p = g->edges[x];
        while (p != NULL) {
            insert_edge(gt, p->y, x, true);
            p = p->next;
        }
    }

    return(gt);
}
/* ]]] */
