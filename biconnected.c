/*	biconnected.c
	Identify articulation vertices in a graph
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

/* [[[ ratod_cut */
int reachable_ancestor[MAXV+1]; /* earliest reachable ancestor of v */
int tree_out_degree[MAXV+1];    /* DFS tree outdegree of v */
/* ]]] */

/* [[[ pvearlydfs_cut */
void process_vertex_early(int v) {
    reachable_ancestor[v] = v;
}
/* ]]] */

/* [[[ pvlatedfs2_cut */
void process_vertex_late(int v) {
    bool root;              /* is parent[v] the root of the DFS tree? */
    int time_v;             /* earliest reachable time for v */
    int time_parent;        /* earliest reachable time for parent[v] */

    if (parent[v] == -1) {  /* test if v is the root */
        if (tree_out_degree[v] > 1) {
            printf("root articulation vertex: %d \n",v);
        }
        return;
    }

    root = (parent[parent[v]] == -1);       /* is parent[v] the root? */

    if (!root) {
        if (reachable_ancestor[v] == parent[v]) {
            printf("parent articulation vertex: %d \n", parent[v]);
        }
  
        if (reachable_ancestor[v] == v) {
            printf("bridge articulation vertex: %d \n",parent[v]);

            if (tree_out_degree[v] > 0) {    /* is v is not a leaf? */
                printf("bridge articulation vertex: %d \n", v);
            }
        }
    }

    time_v = entry_time[reachable_ancestor[v]];
    time_parent = entry_time[reachable_ancestor[parent[v]]];

    if (time_v < time_parent) {
        reachable_ancestor[parent[v]] = reachable_ancestor[v];
    }
}
/* ]]] */

/* [[[ pedgedfs_cut */
void process_edge(int x, int y) {
    int class;    /* edge class */

    class = edge_classification(x, y);

    if (class == TREE) {
        tree_out_degree[x] = tree_out_degree[x] + 1;
    }

    if ((class == BACK) && (parent[x] != y)) {
        if (entry_time[y] < entry_time[reachable_ancestor[x]]) {
            reachable_ancestor[x] = y;
        }
    }
}
/* ]]] */

/* [[[ articulation_vertices_cut */
void articulation_vertices(graph *g) {
    int i;    /* counter */

    for (i = 1; i <= (g->nvertices); i++) { 
        tree_out_degree[i] = 0;
    }

    initialize_search(g);

    for (i = 1; i <= (g->nvertices); i++) {
        if (!discovered[i]) {
            dfs(g, i);
        }
    }
}
/* ]]] */

int main(void) {
    graph g;

    read_graph(&g, false);
    print_graph(&g);

    articulation_vertices(&g);

    return 0;
}
