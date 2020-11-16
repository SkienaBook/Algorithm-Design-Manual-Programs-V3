/*    prim.c

    Compute minimum spanning trees of graphs via Dijkstra/Prim's algorithm.
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

#include "bfs-dfs.h"

#define MAXINT 1000007

int parent[MAXV+1];    /* discovery relation */

/************************************************************/
/* [[[ prim_cut */
int prim(graph *g, int start) {
    int i;                 /* counter */
    edgenode *p;           /* temporary pointer */
    bool intree[MAXV+1];   /* is the vertex in the tree yet? */
    int distance[MAXV+1];  /* cost of adding to tree */
    int v;                 /* current vertex to process */
    int w;                 /* candidate next vertex */
    int dist;              /* cheapest cost to enlarge tree */
    int weight = 0;        /* tree weight */

    for (i = 1; i <= g->nvertices; i++) {
        intree[i] = false;
        distance[i] = MAXINT;
        parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    while (!intree[v]) {
        intree[v] = true;
        if (v != start) {
            printf("edge (%d,%d) in tree \n",parent[v],v);
            weight = weight + dist;
        }
        p = g->edges[v];
        while (p != NULL) {
            w = p->y;
            if ((distance[w] > p->weight) && (!intree[w])) {
                distance[w] = p->weight;
                parent[w] = v;
            }
            p = p->next;
        }

        dist = MAXINT;
        for (i = 1; i <= g->nvertices; i++) {
            if ((!intree[i]) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
        }
    }

    return(weight);
}
/* ]]] */

int main(void) {
    graph g;
    int weight;

    read_graph(&g, false);

    weight = prim(&g, 1);

    printf("Out of Prim: weight = %d \n",weight);

    return 0;
}
