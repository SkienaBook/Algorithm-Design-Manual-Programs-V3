
/*	connected.c

	Compute the connected components of a graph.

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
#include "graph.h"

extern bool processed[];	/* which vertices have been processed */
extern bool discovered[];	/* which vertices have been found */
extern int parent[];		/* discovery relation */


process_vertex_early(int v)
{
	printf(" %d",v);
}

process_vertex_late(int v)
{
}

process_edge(int x, int y)
{
}

bool valid_edge(int e)
{
        return (TRUE);
}



connected_components(graph *g)
{
	int c;				/* component number */
	int i;				/* counter */

	initialize_search(g);

	c = 0;
	for (i=1; i<=g->nvertices; i++)
		if (discovered[i] == FALSE) {
			c = c+1;
			printf("Component %d:",c);
			dfs(g,i);
			printf("\n");
		}
}

main()
{
	graph g;

	read_graph(&g,FALSE);
	print_graph(&g);

	connected_components(&g);
}

