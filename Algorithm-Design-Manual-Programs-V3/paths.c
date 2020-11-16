/*    paths.c

      Enumerate the paths in a graph via backtracking
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



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

#define MAXCANDIDATES   100    /* max possible next extensions */
#define NMAX            100    /* maximum solution size */

bool finished = false;
int solution_count;            /* how many solutions are there? */

/* [[[ paths_data_cut */
typedef struct {
    int s;                     /* source vertex */
    int t;                     /* destination vertex */
    graph g;                   /* graph to find paths in */
} paths_data;
/* ]]] */

/* [[[ process_solution_paths_cut */
void process_solution(int a[], int k, paths_data *input) {
    int i;    /* counter */

    solution_count ++;

    printf("{");
    for (i = 1; i <= k; i++) {
        printf(" %d",a[i]);
    }
    printf(" }\n");
}
/* ]]] */

/* [[[ is_a_solution_paths_cut */
int is_a_solution(int a[], int k, paths_data *g) {
    return (a[k] == g->t);
}
/* ]]] */

void make_move(int a[], int k, paths_data *input) {

}

void unmake_move(int a[], int k, paths_data *input) {

}

/*    
    What are possible elements of the next slot in the path
*/
/* [[[ construct_candidates_paths_cut */
void construct_candidates(int a[], int k, paths_data *g, int c[], int *nc) {
    int i;                /* counters */
    bool in_sol[NMAX+1];  /* what's already in the solution? */
    edgenode *p;          /* temporary pointer */
    int last;             /* last vertex on current path */

    for (i = 1; i <= g->g.nvertices; i++) {
        in_sol[i] = false;
    }

    for (i = 0; i < k; i++) {
        in_sol[a[i]] = true;
    }

    if (k == 1) {
        c[0] = g->s;      /* always start from vertex s */
        *nc = 1;
    } else {
        *nc = 0;
        last = a[k-1];
        p = g->g.edges[last];
        while (p != NULL) {
            if (!in_sol[ p->y ]) {
                c[*nc] = p->y;
                *nc= *nc + 1;
            }
            p = p->next;
        }
    }
}
/* ]]] */

void backtrack(int a[], int k, paths_data *input) {
    int c[MAXCANDIDATES];           /* candidates for next position */
    int ncandidates;                /* next position candidate count */
    int i;                          /* counter */

    if (is_a_solution(a, k, input)) {
            process_solution(a, k, input);
    } else {
        k = k + 1;
        construct_candidates(a, k, input, c, &ncandidates);
        for (i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            make_move(a, k, input);
            backtrack(a, k, input);
            unmake_move(a, k, input);

            if (finished) {
                return;    /* terminate early */
            }
        }
    }
}

int main(void) {
    int a[NMAX];    /* solution vector */
    int i;          /* counter */
    paths_data *g;

    g = malloc(sizeof(paths_data));

    read_graph(&(g->g), false);
    print_graph(&(g->g));


    for (i = 1; i <= g->g.nvertices; i++) {
        g->s = 1;
        g->t = i;
        printf("\nPaths from 1 to %d:\n", i);
        backtrack(a, 0, g);
    }

    for (i = 1; i <= g->g.nvertices; i++) {
        g->s = i;
        g->t = 1;
        printf("\nPaths from %d to 1:\n", i);
        backtrack(a, 0, g);
    }

    return 0;
}
