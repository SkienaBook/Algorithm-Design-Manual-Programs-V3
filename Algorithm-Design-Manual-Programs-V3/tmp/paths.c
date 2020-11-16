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
#include <stdio.h>

#include "bool.h"
#include "graph.h"

#define MAXCANDIDATES   100    /* max possible next extensions */
#define NMAX            100    /* maximum solution size */

bool finished = FALSE;
int solution_count;            /* how many solutions are there? */

graph g;                       /* graph to traverse */

/* [[[ process_solution_paths_cut */
void process_solution(int a[], int k, int input) {
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
int is_a_solution(int a[], int k, int t) {
    return (a[k] == t);
}
/* ]]] */

void make_move(int a[], int k, int n) {

}

void unmake_move(int a[], int k, int n) {

}

/*    
    What are possible elements of the next slot in the path
*/
/* [[[ construct_candidates_paths_cut */
void construct_candidates(int a[], int k, int n, int c[], int *nc) {
    int i;                /* counters */
    bool in_sol[NMAX];    /* what's already in the solution? */
    edgenode *p;          /* temporary pointer */
    int last;             /* last vertex on current path */

    for (i = 1; i < NMAX; i++) {
        in_sol[i] = FALSE;
    }

    for (i = 0; i < k; i++) {
        in_sol[a[i]] = TRUE;
    }

    if (k == 1) {    /* always start from vertex 1 */
        c[0] = 1;
        *nc = 1;
    } else {
        *nc = 0;
        last = a[k-1];
        p = g.edges[last];
        while (p != NULL) {
            if (!in_sol[ p->y ]) {
                c[*nc] = p->y;
                *nc= *nc+ 1;
            }
            p = p->next;
        }
    }
}
/* ]]] */

void backtrack(int a[], int k, int input) {
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

            if (finished == TRUE) {
                return;    /* terminate early */
            }
        }
    }
}

int main(void) {
    int a[NMAX];    /* solution vector */
    int i;          /* counter */

    read_graph(&g, FALSE);
    print_graph(&g);

    for (i = 1; i <= g.nvertices; i++) {
        printf("\nPaths from 1 to %d:\n", i);
        backtrack(a, 0, i);
    }

    return 0;
}
