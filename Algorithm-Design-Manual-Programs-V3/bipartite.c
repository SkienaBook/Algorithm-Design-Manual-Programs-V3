/*	bipartite.c
	Two color a bipartite graph
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

extern int entry_time[MAXV+1];  /* time of vertex entry */
extern int exit_time[MAXV+1];   /* time of vertex exit */

#define UNCOLORED   0   /* vertex not yet colored */
#define WHITE       1   /* white vertex */
#define BLACK       2   /* black vertex */

int color[MAXV+1];      /* assigned color of v */
bool bipartite;         /* is the graph bipartite? */

void process_vertex_early(int v) {

}

void process_vertex_late(int v) {

}

/* [[[ complement_cut */
int complement(int color) {
    if (color == WHITE) {
        return(BLACK);
    }

    if (color == BLACK) {
        return(WHITE);
    }
	
    return(UNCOLORED);
}
/* ]]] */

/* [[[ pecolor_cut */
void process_edge(int x, int y) {
    if (color[x] == color[y]) {
        bipartite = false;
        printf("Warning: not bipartite, due to (%d,%d)\n", x, y);
    }

    color[y] = complement(color[x]);
}
/* ]]] */

/* [[[ twocolor_cut */
void twocolor(graph *g) {
    int i;    /* counter */

    for (i = 1; i <= (g->nvertices); i++) { 
        color[i] = UNCOLORED;
    }

    bipartite = true;
 
    initialize_search(g);

    for (i = 1; i <= (g->nvertices); i++) {
        if (!discovered[i]) {
            color[i] = WHITE;
            bfs(g, i);
        }
    }
}
/* ]]] */

int main(void) {
    graph g;
    int i;

    read_graph(&g, false);
    print_graph(&g);

    twocolor(&g);

    for (i = 1; i <= (g.nvertices); i++) {
        printf(" %d", color[i]);
    }
    printf("\n");

    return 0;
}
