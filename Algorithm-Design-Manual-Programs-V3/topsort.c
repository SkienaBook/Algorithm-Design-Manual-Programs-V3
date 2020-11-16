/*    topsort.c

    Topologically sort a directed acyclic graph (DAG) by indegre-zero deletion.
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

#include "bfs-dfs.h"
#include "queue.h"

/* [[[ compute_indegree_cut */
void compute_indegrees(graph *g, int in[]) {
    int i;          /* counter */
    edgenode *p;    /* temporary pointer */

    for (i = 1; i <= g->nvertices; i++) {
        in[i] = 0;
    }

    for (i = 1; i <= g->nvertices; i++) {
        p = g->edges[i];
        while (p != NULL) {
            in[p->y]++;
            p = p->next;
        }
    }
}
/* ]]] */

/* [[[ topsort_swallow_cut */
void topsort(graph *g, int sorted[]) {
    int indegree[MAXV+1];    /* indegree of each vertex */
    queue zeroin;            /* vertices of indegree 0 */
    int x, y;                /* current and next vertex */
    int i, j;                /* counters */
    edgenode *p;             /* temporary pointer */

    compute_indegrees(g, indegree);
    init_queue(&zeroin);
    for (i = 1; i <= g->nvertices; i++) {
        if (indegree[i] == 0) {
            enqueue(&zeroin, i);
        }
    }

    j = 0;
    while (!empty_queue(&zeroin)) {
        j = j + 1;
        x = dequeue(&zeroin);
        sorted[j] = x;
        p = g->edges[x];
        while (p != NULL) {
            y = p->y;
            indegree[y]--;
            if (indegree[y] == 0) {
                enqueue(&zeroin, y);
            }
            p = p->next;
        }
    }

    if (j != g->nvertices) {
        printf("Not a DAG -- only %d vertices found\n", j);
    }
}
/* ]]] */

int main(void) {
    graph g;
    int out[MAXV+1];
    int i;

    read_graph(&g, true);
    print_graph(&g);

    topsort(&g, out);

    for (i = 1; i <= g.nvertices; i++) {
        printf(" %d", out[i]);
    }
    printf("\n");

    return 0;
}
