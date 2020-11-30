/*	tsp.c

	Heuristics for solving TSP

	by:Steven Skiena
	begun: August 2, 2006
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


#include <string.h>
#include "bool.h"
#include "tsp.h"

extern int solution_count;

/**********************************************************************/

read_tsp(tsp_instance *t)
{
	int i,j;			/* counters */

	scanf("%d\n",&(t->n));

	for (i=1; i<=(t->n); i++)
		scanf("%d %d %d\n",&j,&(t->p[i].x),&(t->p[i].y));
}

print_tsp(tsp_instance *t)
{
	int i;				/* counter */

	for (i=1; i<=(t->n); i++)
		printf("%d %d %d\n",i,(t->p[i].x),(t->p[i].y));
}

int sq(int x)
{
	return(x*x);
}

double distance(tsp_solution *s, int x, int y, tsp_instance *t)
{
	int i, j;

	i = x;
	j = y;

	if (i==((t->n)+1)) i=1;
	if (j==((t->n)+1)) j=1;

	if (i==0) i=(t->n);
	if (j==0) j=(t->n);

	return ( sqrt( (double) (sq(t->p[(s->p[i])].x - t->p[(s->p[j])].x) +
			         sq(t->p[(s->p[i])].y - t->p[(s->p[j])].y) ) ) );
}


/**********************************************************************/

double solution_cost(tsp_solution *s, tsp_instance *t)
{
	int i;				/* counter */
	double cost;			/* cost of solution */
	double distance();

	cost = distance(s,t->n,1,t);
	for (i=1; i<(t->n); i++)
		cost = cost + distance(s,i,i+1,t);

	return(cost);
}

initialize_solution(int n, tsp_solution *s)
{
	int i;				/* counter */

	s->n = n;
	for (i=1; i<=n; i++)
		s->p[i] = i;
}

copy_solution(tsp_solution *s, tsp_solution *t)
{
	int i;				/* counter */
	t->n = s->n;
	for (i=1; i<=(s->n); i++)
		t->p[i] = s->p[i];
}
		

print_solution(tsp_solution *s)
{
        int i;                          /* counter */

        for (i=1; i<=(s->n); i++)
                printf(" %d",s->p[i]);
	printf("\n------------------------------------------------------\n");
}

read_solution(tsp_solution *s)
{
	int i;				/* counter */

	scanf("%d\n",&(s->n));

	for (i=1; i<=(s->n); i++)
		scanf("%d",&(s->p[i]));
}

random_solution(tsp_solution *s)
{
	random_permutation(&(s->p[1]),(s->n)-1);
}

double transition(tsp_solution *s, tsp_instance *t, int i, int j)
{
	double was, willbe;		/* before and after costs */
	double distance();
	bool neighbors;			/* i,j neighboring tour positions? */

	neighbors = FALSE; 

	if (i == j) {
		/*printf("Warning: null transition i=%d j=%d\n",i,j);*/
		return(0.0);
	}

	if (i > j) return( transition(s,t,j,i) );

	if (i==(j-1)) neighbors = TRUE;

	if ((i==1) && (j==(s->n))) {
		swap(&i,&j);
		neighbors = TRUE;
	}

	if (neighbors) {
		was = distance(s,i-1,i,t) + distance(s,j,j+1,t);
	} else {
	was = distance(s,i-1,i,t) + distance(s,i,i+1,t)
		+ distance(s,j-1,j,t) + distance(s,j,j+1,t);
	}

	swap(&(s->p[i]),&(s->p[j]));

	if (neighbors) {
		willbe = distance(s,i-1,i,t) + distance(s,j,j+1,t);
	} else {
	willbe = distance(s,i-1,i,t) + distance(s,i,i+1,t)
		+ distance(s,j-1,j,t) + distance(s,j,j+1,t);
	}

	return(willbe - was);
}



/**********************************************************************/






main()
{
	tsp_instance t;			/* tsp points */
	tsp_solution s;			/* tsp solution */
	int i;				/* counter*/
	double solution_cost();

	read_tsp(&t);
	/*print_tsp(&t);*/

	read_solution(&s);
	printf("OPTIMAL SOLUTION COST = %7.1f\n",solution_cost(&s,&t));
        print_solution(&s);


	initialize_solution(t.n, &s);
	printf("solution_cost = %7.1f\n",solution_cost(&s,&t));
	print_solution(&s);

	
/*
	solution_count=0;
	random_sampling(&t,1500000,&s);
        printf("random sampling %d iterations, cost = %7.1f\n",
			solution_count,solution_cost(&s,&t));
       	print_solution(&s);

	solution_count=0;
        repeated_hill_climbing(&t,195,&s);
        printf("repeated hill climbing %d iterations, cost = %7.1f\n",
                        solution_count,solution_cost(&s,&t));
        print_solution(&s);
*/

	solution_count=0;
	repeated_annealing(&t,3,&s);
	printf("repeated annealing %d iterations, cost = %7.1f\n",
                        solution_count,solution_cost(&s,&t));
	print_solution(&s);

}


