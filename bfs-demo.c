/*	bfs-demo.c
	Driver program demonstrating breadth-first search 
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
or http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/


#include <stdio.h>
#include <stdbool.h>

#include "bfs-dfs.h"

extern bool processed[];    /* which vertices have been processed */
extern bool discovered[];   /* which vertices have been found */
extern int parent[];        /* discovery relation */

/* [[[ pvearly_cut */
void process_vertex_early(int v) {
    printf("processed vertex %d\n", v);
}
/* ]]] */

/* [[[ pvlate_cut */
void process_vertex_late(int v) {

}
/* ]]] */

/* [[[ pedge_cut */
void process_edge(int x, int y) {
    printf("processed edge (%d,%d)\n", x, y);
}
/* ]]] */

int main(void) {
    graph g;
    int i;

    read_graph(&g, false);
    print_graph(&g);
    initialize_search(&g);
    bfs(&g, 1);

    for (i = 1; i <= g.nvertices; i++) {
        printf(" %d", parent[i]);
    }
    printf("\n");

    for (i = 1; i <= g.nvertices; i++) { 
        find_path(1, i, parent);
    }
    printf("\n");

    return 0;
}
