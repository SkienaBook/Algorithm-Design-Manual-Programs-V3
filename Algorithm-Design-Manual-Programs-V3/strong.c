/*    strong.c

    Identify strongly connected components in a graph
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
#include "stack.h"

extern bool processed[];    /* which vertices have been processed */
extern bool discovered[];   /* which vertices have been found */
extern int parent[];        /* discovery relation */

extern int entry_time[];    /* time of vertex entry */
extern int exit_time[];     /* time of vertex exit */

/* [[[ sc_arrays_cut */
int low[MAXV+1];    /* oldest vertex surely in component of v */
int scc[MAXV+1];    /* strong component number for each vertex */
/* ]]] */

stack active;            /* active vertices of unassigned component */
int components_found;    /* number of strong components identified */

/* [[[ pvearly_strong_cut */
void process_vertex_early(int v) {
    push(&active, v);
}
/* ]]] */

/* [[[ pop_comp_strong_cut */
void pop_component(int v) {
    int t;    /* vertex placeholder */

    components_found = components_found + 1;
    printf("%d is in component %d \n", v, components_found);

    scc[v] = components_found;
    while ((t = pop(&active)) != v) {
        scc[t] = components_found;
        printf("%d is in component %d \n", t, components_found);
    }
}
/* ]]] */

/* [[[ pvlate_strong_cut */
void process_vertex_late(int v) {
    if (low[v] == v) {
        pop_component(v);
    }

    if (entry_time[low[v]] < entry_time[low[parent[v]]]) {
        low[parent[v]] = low[v];
    }
}
/* ]]] */

/* [[[ pedge_strong_cut */
void process_edge(int x, int y) {
    int class;    /* edge class */

    class = edge_classification(x, y);

    if (class == BACK) {
        if (entry_time[y] < entry_time[low[x]]) {
            low[x] = y;
        }
    }

    if (class == CROSS) {
        if (scc[y] == -1) {   /* component not yet assigned */
            if (entry_time[y] < entry_time[ low[x]]) {
                low[x] = y;
            }
        }
    }
}
/* ]]] */

/* [[[ strong_comp_cut */
void strong_components(graph *g) {
    int i;    /* counter */

    for (i = 1; i <= (g->nvertices); i++) {
        low[i] = i;
        scc[i] = -1;
    }

    components_found = 0;

    init_stack(&active);
    initialize_search(g);

    for (i = 1; i <= (g->nvertices); i++) {
        if (!discovered[i]) {
            dfs(g, i);
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

