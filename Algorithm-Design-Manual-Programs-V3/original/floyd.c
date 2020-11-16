
/*	floyd.c

	Compute all-pairs shortest paths in weighted graphs.

	by: Steven Skiena
	begun: March 26, 2002
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


#include <stdlib.h>
#include "bool.h"


/************************************************************/



#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

#define MAXINT	100007

typedef struct {
	int v;				/* neighboring vertex */
	int weight;			/* edge weight */
	bool in;			/* is the edge "in" the solution? */
} edge;

typedef struct {
	edge edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

typedef struct {
        int weight[MAXV+1][MAXV+1];    	/* adjacency/weight info */
        int nvertices;                  /* number of vertices in the graph */
} adjacency_matrix;


initialize_adjacency_matrix(adjacency_matrix *g)
{
	int i,j;			/* counters */

	g -> nvertices = 0;

	for (i=1; i<=MAXV; i++)
		for (j=1; j<=MAXV; j++)
			g->weight[i][j] = MAXINT;
}

read_adjacency_matrix(adjacency_matrix *g, bool directed)
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x,y,w;			/* placeholder for edge and weight */

	initialize_adjacency_matrix(g);

	scanf("%d %d\n",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d\n",&x,&y,&w);
		g->weight[x][y] = w;
		if (directed==FALSE) g->weight[y][x] = w;
	}
}


print_graph(adjacency_matrix *g)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=1; j<=g->nvertices; j++)
			if (g->weight[i][j] < MAXINT)
				printf(" %d",j);
		printf("\n");
	}
}

print_adjacency_matrix(adjacency_matrix *g)
{
        int i,j;                        /* counters */

        for (i=1; i<=g->nvertices; i++) {
                printf("%3d: ",i);
                for (j=1; j<=g->nvertices; j++)
                                printf(" %3d",g->weight[i][j]);
                printf("\n");
        }
}



floyd(adjacency_matrix *g)
{
	int i,j;			/* dimension counters */
	int k;				/* intermediate vertex counter */
	int through_k;			/* distance through vertex k */

	for (k=1; k<=g->nvertices; k++)
		for (i=1; i<=g->nvertices; i++)
			for (j=1; j<=g->nvertices; j++) {
				through_k = g->weight[i][k]+g->weight[k][j];
				if (through_k < g->weight[i][j])
					g->weight[i][j] = through_k;
			}
}


main()
{
	adjacency_matrix g;


	read_adjacency_matrix(&g,FALSE);
	print_graph(&g);

	floyd(&g);

	print_adjacency_matrix(&g);

}


