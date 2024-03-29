/*	findcycle.c

	Identify a cycle in a graph, if one exists.
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

extern bool processed[];    /* which vertices have been processed */
extern bool discovered[];   /* which vertices have been found */
extern int parent[];        /* discovery relation */

extern bool finished;       /* flag for early search cutoff */

void process_vertex_early(int v) {

}

void process_vertex_late(int v) {

}

/* [[[ cyclepedge_cut */
void process_edge(int x, int y) {
    if (parent[y] != x) {    /* found back edge! */
        printf("Cycle from %d to %d:", y, x);
        find_path(y, x, parent);
        finished = true;
    }
}
/* ]]] */

int main(void) {
    graph g;

    read_graph(&g, false);
    print_graph(&g);

    initialize_search(&g);
    dfs(&g, 1);
    printf("\n");

    return 0;
}
