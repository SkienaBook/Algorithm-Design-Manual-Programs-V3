/*	dfs-demo.c

	Driver program demonstrating DFS numbering and edge labeling.
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
#include "queue.h"

extern bool processed[];    /* which vertices have been processed */
extern bool discovered[];   /* which vertices have been found */
extern int parent[];        /* discovery relation */

int entry_time[MAXV+1];     /* time of vertex entry */
int exit_time[MAXV+1];      /* time of vertex exit */
int time;                   /* current event time */

void process_vertex_early(int v) {
    time = time + 1;
    entry_time[v] = time;
    printf("entered vertex %d at time %d\n",v, entry_time[v]);
}

void process_vertex_late(int v) {
    time = time + 1;
    exit_time[v] = time;
    printf("exit vertex %d at time %d\n",v, exit_time[v]);
}

void process_edge(int x, int y) {
    int class;    /* edge class */

    class = edge_classification(x, y);

    if (class == BACK) {
        printf("back edge (%d,%d)\n", x, y);
    } else if (class == TREE) {
        printf("tree edge (%d,%d)\n", x, y);
    } else if (class == FORWARD) {
        printf("forward edge (%d,%d)\n", x, y);
    } else if (class == CROSS) {
        printf("cross edge (%d,%d)\n", x, y);
    } else {
        printf("edge (%d,%d)\n not in valid class=%d", x, y, class);
    }
}

int main(void) {
    graph g;
    int i;

    read_graph(&g, false);
    print_graph(&g);

    initialize_search(&g);
    dfs(&g, 1);

    for (i = 1; i <= g.nvertices; i++) {
        find_path(1, i, parent);
    }
    printf("\n");

    return 0;
}
