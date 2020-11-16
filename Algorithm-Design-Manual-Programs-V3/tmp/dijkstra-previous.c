
/*	dijkstra.c

	Compute shortest paths in weighted graphs using Dijkstra's algorithm

	by: Steven Skiena
	date: March 6, 2002
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved. 

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/

#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "bfs-dfs.h"

#define MAXINT  100007

int parent[MAXV+1];    /* discovery relation */

/* WAS prim(g,start) */

int totalweight=0;

void dijkstra(graph *g, int start) {
    int i;                  /* counter */
    edgenode *p;            /* temporary pointer */
    bool intree[MAXV+1];    /* is the vertex in the tree yet? */
    int distance[MAXV+1];   /* distance vertex is from start */
    int v;                  /* current vertex to process */
    int w;                  /* candidate next vertex */
    int weight;	            /* edge weight */
    int dist;               /* best current distance from start */

    for (i = 1; i <= g->nvertices; i++) {
        intree[i] = FALSE;
        distance[i] = MAXINT;
        parent[i] = -1;
    }

    dist = distance[start] = 0;
    v = start;

    while (intree[v] == FALSE) {
        intree[v] = TRUE;
totalweight = totalweight + dist;
        p = g->edges[v];
        while (p != NULL) {
            w = p->y;
            weight = p->weight;
            if (distance[w] > (distance[v]+weight)) { /* CHANGED */
                distance[w] = distance[v]+weight;     /* CHANGED */
                parent[w] = v;                        /* CHANGED */
            }
            p = p->next;
        }

        v = 1;
        dist = MAXINT;
        for (i = 1; i <= g->nvertices; i++) {
            if ((intree[i] == FALSE) && (dist > distance[i])) {
                dist = distance[i];
                v = i;
            }
        }
    }
}

int main(void) {
    graph g;
    int i;

    read_graph(&g, FALSE);
    dijkstra(&g, 1);

printf("total DST edge weight = %d\n",totalweight);

    for (i = 1; i <= g.nvertices; i++) {
        find_path(1, i, parent);
    }
    printf("\n");

    return 0;
}

