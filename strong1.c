/*    strong1.c

    Identify strongly connected components in a graph (via Kosaraju-Sharir)
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
#include <stdlib.h>
#include "bfs-dfs.h"
#include "stack.h"

extern bool processed[];    /* which vertices have been processed */
extern bool discovered[];   /* which vertices have been found */
extern int parent[];        /* discovery relation */

extern int entry_time[];    /* time of vertex entry */
extern int exit_time[];     /* time of vertex exit */

int time;                   /* current event time */
extern bool finished;       /* if true, cut off search immediately */


/* [[[ sc_arrays2_cut */
int low[MAXV+1];    /* oldest vertex surely in component of v */
int scc[MAXV+1];    /* strong component number for each vertex */
/* ]]] */

stack dfs1order;         /* stack for reverse finishing order */

stack active;            /* active vertices of unassigned component */
int components_found;    /* number of strong components identified */

void process_vertex_early2(int v);
void process_vertex_late2(int v);
void process_edge2(int x, int y);

/* replicate dfs call so it can use different process vertex functions */

void dfs2(graph *g, int v) {
    edgenode *p;        /* temporary pointer */
    int y;              /* successor vertex */

    if (finished) {
        return;         /* allow for search termination */
    }

    discovered[v] = true;
    time = time + 1;
    entry_time[v] = time;

    process_vertex_early2(v);

    p = g->edges[v];
    while (p != NULL) {
        y = p->y;
        if (!discovered[y]) {
            parent[y] = v;
            process_edge2(v, y);
            dfs2(g, y);
        } else if (((!processed[y]) && (parent[v] != y)) || (g->directed)) {
            process_edge2(v, y);
        }

        if (finished) {
            return;
        }

        p = p->next;
    }

    process_vertex_late2(v);

    time = time + 1;
    exit_time[v] = time;

    processed[v] = true;
}



/* [[[ strong_dfs1_cut */
/* [[[ pvearly_strong12_cut */
void process_vertex_early(int v) {
    
}
/* ]]] */

/* [[[ pvlate_strong12_cut */
void process_vertex_late(int v) {
    push(&dfs1order,v);
}
/* ]]] */

/* [[[ pedge_strong12_cut */
void process_edge(int x, int y) {

}
/* ]]] */
/* ]]] */


/* [[[ strong_dfs2_cut */
/* [[[ pvearly_strong22_cut */
void process_vertex_early2(int v) {
    printf(" %d", v);
}
/* ]]] */

/* [[[ pvlate_strong22_cut */
void process_vertex_late2(int v) {

}
/* ]]] */

/* [[[ pedge_strong22_cut */
void process_edge2(int x, int y) {

}
/* ]]] */
/* ]]] */


/* [[[ strong_comp2_cut */
void strong_components(graph *g) {
    graph *gt;           /* transpose of graph g */
    int i;               /* counter */
    int v;               /* vertex in component */

    init_stack(&dfs1order);
    initialize_search(g);
    for (i = 1; i <= (g->nvertices); i++) {
        if (!discovered[i]) {
            dfs(g, i);
        }
    }

    gt = transpose(g);
    initialize_search(gt);

    components_found = 0;
    while (!empty_stack(&dfs1order)) {
        v = pop(&dfs1order);
        if (!discovered[v]) {
            components_found ++;
            printf("Component %d:", components_found);
            dfs2(gt, v);
            printf("\n");
        }
    }
}
/* ]]] */

int main(void) 
{
    graph g;

    read_graph(&g, true);
    print_graph(&g);

    strong_components(&g);

    return 0;
}

