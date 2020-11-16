/*	
	paths.c
	Enumerate the paths in a graph via backtracking

	begun: August 1, 2006
	by: Steven Skiena
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

#include "graph.h"
#include "backtrack.h"
#include "bool.h"

int solution_count;			/* how many solutions are there? */

graph g;				/* graph to traverse */

process_solution(int a[], int k)
{
	int i;				/* counter */

	solution_count ++;

        printf("{");
        for (i=1; i<=k; i++)
                printf(" %d",a[i]);
        printf(" }\n");

}

is_a_solution(int a[], int k, int t)
{
	return (a[k] == t);
}

make_move(int a[], int k, int n)
{
}

unmake_move(int a[], int k, int n)
{
}


/*	What are possible elements of the next slot in the path
*/

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
	int i,j;			/* counters */
	bool in_sol[NMAX];		/* what's already in the solution? */
	int last;			/* last vertex on current path */

        for (i=1; i<NMAX; i++) in_sol[i] = FALSE;
	for (i=1; i<k; i++) in_sol[ a[i] ] = TRUE;

	if (k==1) {			/* always start from vertex 1 */
		c[0] = 1;
		*ncandidates = 1;
	}
	else	{
		*ncandidates = 0;
		last = a[k-1];
		for (i=0; i<g.degree[last]; i++)
			if (!in_sol[ g.edges[last][i] ]) {
				c[*ncandidates] = g.edges[last][i];
                        	*ncandidates = *ncandidates + 1;
			}
	}
}



main()
{
	int a[NMAX];			/* solution vector */
	int i;				/* counter */

        read_graph(&g,FALSE);
        print_graph(&g);

	for (i=1; i<=g.nvertices; i++) {
		printf("\nPaths from 1 to %d:\n",i);
		backtrack(a,0,i);
	}

}

