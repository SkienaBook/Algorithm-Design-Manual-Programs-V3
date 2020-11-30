
/*	graph.c         

	A generic adjacency list-in-array graph data type.

	by: Steven Skiena
	begun: March 6, 2002

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


#include "bool.h"
#include "queue.h"
#include "graph.h"

initialize_graph(graph *g)
{
	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
}

read_graph(graph *g, bool directed)
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x, y;			/* vertices in edge (x,y) */

	initialize_graph(g);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d",&x,&y);
		insert_edge(g,x,y,directed);
	}
}

insert_edge(graph *g, int x, int y, bool directed)
{
	if (g->degree[x] > MAXDEGREE)
	    printf("Warning: insertion(%d,%d) exceeds max degree\n",x,y);

	g->edges[x][g->degree[x]] = y;
	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE);
	else
		g->nedges ++;
}


delete_edge(graph *g, int x, int y, bool directed)
{
	int i;				/* counter */

	for (i=0; i<g->degree[x]; i++) 
		if (g->edges[x][i] == y) {
			g->degree[x] --;
			g->edges[x][i] = g->edges[x][g->degree[x]];

			if (directed == FALSE)
				delete_edge(g,y,x,TRUE);

			return;
		}

	printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

print_graph(graph *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=0; j<g->degree[i]; j++)
			printf(" %d",g->edges[i][j]);
		printf("\n");
	}
}

