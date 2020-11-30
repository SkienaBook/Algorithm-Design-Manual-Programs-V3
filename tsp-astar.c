/*    tsp-astar.c

    Solve TSP to optimality via backtracking and later A* search.
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




#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "tsp-pq.h"


#define MAXCANDIDATES   100    /* max possible next extensions */
#define MAXD	     100000.0  /* largest possible distance */

tsp_solution best_solution;	/* store the current best solution */
double best_cost;		/* cost of current best solution */

double lb[NMAX];   		/* vertex lower bounds */
double minlb;      		/* global edge lower bound */

long evaluations;		/* how many of (n-1!) evaluations were done? */
long constructions;		/* how many intermediate nodes were calculated */
long maxqueuesize;		/* largest size of queue realized */

priority_queue q;           	/* priority queue for branch & bound search */

bool lb_flag = true;		/* use  lower bound to speed branch & bound */
bool finished = false;

	/* declarations to clean up branch_and_bound for the book */

void initialize_solution(tsp_solution *, tsp_instance *);
void first_solution(tsp_solution *, tsp_instance *);
void print_solution(tsp_solution *);
void extend_solution(tsp_solution *, tsp_instance *, int);
void contract_solution(tsp_solution *, tsp_instance *);
double solution_cost(tsp_solution *, tsp_instance *);

double partial_solution_lb(tsp_solution *, tsp_instance *);

/* [[[ astar_process_solution_tsp_cut */
void process_solution(tsp_solution *s, int k, tsp_instance *input) {
    s->cost = solution_cost(s,input);
    if (s->cost < best_cost) {
	best_cost = s->cost;
        copy_solution(s,&best_solution);
    }

   evaluations ++;
}
/* ]]] */

/* [[[ astar_is_a_solution_tsp_cut */
int is_a_solution(tsp_solution *s, int k, tsp_instance *t) {
    return (k == t->n);
}
/* ]]] */

void make_move(tsp_solution *s, int k, tsp_instance *t) {

}

void unmake_move(tsp_solution *s, int k, tsp_instance *t){

}

/*    What are possible elements of the next slot in the permutation?  */
/* [[[ astar_construct_candidates_tsp_cut */
void construct_candidates(tsp_solution *s, int k, tsp_instance *t, int c[], int *ncandidates) {
    int i;                 /* counter */
    bool in_perm[NMAX];    /* what is now in the permutation? */

    constructions ++;

    if (partial_solution_lb(s,t) > best_cost) {
	*ncandidates = 0;
	return;
    }

    if (k == 1) {
	c[0] = 1;
	*ncandidates = 1;
	return;
    }

    for (i = 1; i < NMAX; i++) {
        in_perm[i] = false;
    }

    for (i = 1; i < k; i++) {
        in_perm[s->p[i]] = true;
    }

    *ncandidates = 0;
    for (i = 1; i <= t->n; i++) { 
        if (!in_perm[i]) {
            c[ *ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
}
/* ]]] */

/* customize backtrack to TSP solutions */

void backtrack(tsp_solution *s, int k, tsp_instance *input) {
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */

    if (is_a_solution(s, k, input)) {
        process_solution(s, k, input);
    } else {
        k = k + 1;
        construct_candidates(s, k, input, c, &ncandidates);
        for (i = 0; i < ncandidates; i++) {
            s->p[k] = c[i];
	    s->n = k;
            make_move(s, k, input);
            backtrack(s, k, input);
            unmake_move(s, k, input);

            if (finished) {
                return;    /* terminate early */
            }
        }
    }
}

/* [[[ astar_generate_tsp_cut */
void solve_tsp(tsp_instance *t, tsp_solution *s) {
    backtrack(s, 0, t);
}
/* ]]] */



/* customize branch and bound  to TSP solutions */

/* [[[ astar_branch_and_bound_cut */
void branch_and_bound (tsp_solution *s, tsp_instance *t) {
    int c[MAXCANDIDATES];      /* candidates for next position */
    int nc;                    /* next position candidate count */
    int i;                     /* counter */

    first_solution(&best_solution,t);
    best_cost = solution_cost(&best_solution, t);
    initialize_solution(s,t);
    extend_solution(s,t,1);
    pq_init(&q);
    pq_insert(&q,s);

    while (top_pq(&q).cost < best_cost) {
         *s = extract_min(&q);
         if (is_a_solution(s, s->n, t)) {
              process_solution(s, s->n, t);
         }
         else {
              construct_candidates(s, (s->n)+1, t, c, &nc);
              for (i=0; i<nc; i++) {
                    extend_solution(s,t,c[i]);
                    pq_insert(&q,s);
                    contract_solution(s,t);
              }
         }
    }
}
/* ]]] */

/*************************************************************/
/*************************************************************/


void read_tsp(tsp_instance *t) {
    int i, j;    /* counters */

    scanf("%d\n", &(t->n));

    for (i = 1; i <= (t->n); i++) {
        scanf("%d %d %d\n", &j, &(t->p[i].x), &(t->p[i].y));
    }
}


void print_tsp(tsp_instance *t) {
    int i;    /* counter */

    for (i = 1; i <= (t->n); i++) {
        printf("%d %d %d\n", i, (t->p[i].x), (t->p[i].y));
    }
}



int sq(int x) {
    return(x * x);
}

double d(int x1, int y1, int x2, int y2) {
	return (sqrt((double) (sq(x1 - x2) + sq(y1 - y2)) ) );
}

double d1(int i, int j, tsp_instance *t) {
	return ( d( t->p[i].x, t->p[i].y, t->p[j].x, t->p[j].y) );
}

double distance(tsp_solution *s, int x, int y, tsp_instance *t) {
    int i, j;

    i = x;
    j = y;

    if (i == ((t->n) + 1)) {
        i = 1;
    }

    if (j == ((t->n) + 1)) {
        j = 1;
    }

    if (i == 0) {
        i = (t->n);
    }

    if (j == 0) {
        j = (t->n);
    }

    return ( d1(s->p[i],s->p[j],t) );
}

/**********************************************************************/

double solution_cost(tsp_solution *s, tsp_instance *t) {
    int i;           /* counter */
    double cost;     /* cost of solution */

    cost = distance(s, t->n, 1, t);
    for (i = 1; i < (t->n); i++) {
        cost = cost + distance(s, i, i + 1, t);
    }

    s->cost = cost;
    return(cost);
}

/* [[[ astar_partial_solution_lb_cut */
double partial_solution_cost(tsp_solution *s, tsp_instance *t) {
    int i;               /* counter */
    double cost = 0.0;   /* cost of solution */

    for (i = 1; i < (s->n); i++) {
        cost = cost + distance(s, i, i + 1, t);
    }

    return(cost);
}

double partial_solution_lb(tsp_solution *s, tsp_instance *t) {
     return(partial_solution_cost(s,t) + (t->n - s->n + 1) * minlb);
}
/* ]]] */

/* BELOW IS THE RIGHT ONE FOR THE EXPERIMENTS, BUT THE WRONG ONE FOR THE BOOK */
/*
double partial_solution_lb(tsp_solution *s, tsp_instance *t) {
    if (lb_flag) {
         return(partial_solution_cost(s,t) + (t->n - s->n + 1) * minlb );
    } else {
         return(partial_solution_cost(s,t));
    }
}
*/

void initialize_solution(tsp_solution *s, tsp_instance *t) {
    s->n = 0;
    s->cost = 0;
}

/* [[[ astar_extend_contract-cut */
void extend_solution(tsp_solution *s, tsp_instance *t, int v) {
    s->n++;
    s->p[s->n] = v;
    s->cost = partial_solution_lb(s,t);
}

void contract_solution(tsp_solution *s, tsp_instance *t) {
    s->n--;
    s->cost = partial_solution_lb(s,t);
}
/* ]]] */

void first_solution(tsp_solution *s, tsp_instance *t) {
    int i;    /* counter */

    s->n = t->n;
    for (i = 1; i <= t->n; i++) {
        s->p[i] = i;
    }
    s->cost = solution_cost(s, t);
}

void copy_solution(tsp_solution *s, tsp_solution *t) {
    int i;    /* counter */
    t->n = s->n;
    for (i = 1; i <= (s->n); i++) {
        t->p[i] = s->p[i];
    }
}
    

void print_solution(tsp_solution *s) {
    int i;    /* counter */

    printf(" n = %d   ",s->n);
    for (i = 1; i <= (s->n); i++) {
            printf(" %d", s->p[i]);
    }
    printf("\n------------------------------------------------------\n");
}

void read_solution(tsp_solution *s) {
    int i;    /* counter */

    scanf("%d\n", &(s->n));

    for (i = 1; i <= (s->n); i++) {
        scanf("%d", &(s->p[i]));
    }
}



/*************************************************************/

/* Compute lower bounds on edge costs for all vertices */

double find_vertex_lower_bounds(tsp_instance *t, double lb[]) {
    int i, j;    		/* counters */
    double minweight;		/* min weight edge in graph */

    minweight = MAXD;
    for (i=1; i<=t->n; i++) {
	lb[i] = MAXD;
	for (j=1; j<=t->n; j++) {
		if ((i != j) && (lb[i] > d1(i,j,t))) {
			lb[i] = d1(i,j,t);
		}
	}
	if (minweight > lb[i]) {
		minweight = lb[i];
	}
    }

    return (minweight);
}

/*************************************************************/


int main(void) {
    tsp_solution s;    /* solution vector */
    tsp_instance t;    /* tsp points */
    int i;             /* counter */

    read_tsp(&t);
    print_tsp(&t);

/*
    first_solution(&s,&t);
    best_cost = solution_cost(&s, &t);

    print_solution(&s);
    printf("INITIAL SOLUTION COST = %7.1f\n",best_cost);
*/

    minlb = find_vertex_lower_bounds(&t, lb);

/*
    printf("minlb = %7.1f\n",minlb);

    for (i=1; i<=t.n; i++) {
	printf(" lb[%d] = %7.1f\n", i, lb[i]);
    }
*/

for (i=false; i<=true; i++) {

    first_solution(&s,&t);
    best_cost = solution_cost(&s, &t);

/*
    print_solution(&s);
    printf("INITIAL SOLUTION COST = %7.1f\n",best_cost);
*/

    lb_flag = i;
    constructions = evaluations = 0;
    solve_tsp(&t, &s);
    printf(" evaluations = %ld backtracking lb_flag=%d \n",evaluations,lb_flag);
    printf(" constructions = %ld \n",constructions);

    print_solution(&best_solution);
    printf("OPTIMAL SOLUTION COST = %7.1f\n",best_cost);

    /********* Branch and Bound Search **************/

    first_solution(&s,&t);
    best_cost = solution_cost(&s, &t);

/*
    print_solution(&s);
    printf("INITIAL SOLUTION COST = %7.1f\n",best_cost);
*/

    maxqueuesize = constructions = evaluations = 0;
    branch_and_bound(&s, &t);
    printf(" evaluations = %ld  branch-and-bound lb_flag=%d \n",evaluations,lb_flag);
    printf(" constructions = %ld  maxqueuesize = %ld \n",constructions,maxqueuesize);

    print_solution(&best_solution);
    printf("OPTIMAL B-AND-B SOLUTION COST = %7.1f\n",best_cost);
}

    return 0;
}
